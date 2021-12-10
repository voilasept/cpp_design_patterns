#include <iostream>
#include <vector>
#include <map>
#include <boost/functional/hash.hpp>
using namespace std;


class Point{
public:
    int x, y;
    Point(int x, int y): x(x), y(y){}
    // hash_value is reserved keyword for boost::hash!
    friend size_t hash_value(const Point& point){
        size_t seed = 0x11111111;
        boost::hash_combine(seed, "Point");
        boost::hash_combine(seed, point.x);
        boost::hash_combine(seed, point.y);
        return seed;
    }
};

class Line{
public:
    Line(const Point& P0, const Point& P1): P0(P0), P1(P1){}
    Point P0, P1;
    friend size_t hash_value(const Line& line){
        size_t seed = 0x11111111;
        boost::hash_combine(seed, line.P0); // Nice property: hash_combine is recursive!
        boost::hash_combine(seed, line.P1);
        return seed;
    }
};

typedef vector<Point> Points;

void draw_points(const Points::iterator& begin, const Points::iterator& end){
    for (auto p = begin; p != end; p++) {
        cout << p->x << " " << p->y << endl;
    }
}

class LineToPointAdapter{
public:
    explicit LineToPointAdapter(const Line& line){
        line_hash = boost::hash<Line>()(line);
        if(cache.find(line_hash) == cache.end()){
            points.emplace_back(line.P0);
            points.emplace_back(line.P1);
            cache[line_hash] = points;
        }
    }
    virtual Points::iterator begin(){ return cache[line_hash].begin(); }
    virtual Points::iterator end(){ return cache[line_hash].end(); }
private:
    size_t line_hash;       // bind to instance
    Points points;
    static map<size_t, Points> cache;   // bind to class
};

map<size_t, Points> LineToPointAdapter::cache {};


int main() {
    Line line {Point(1,2), Point(3,4)};
    LineToPointAdapter adapter {line};
    draw_points(adapter.begin(), adapter.end());

    Point p0(1, 2);
    cout << hash_value(p0) << endl;
    Point p1(1, 2);
    cout << hash_value(p1) << endl;
    Point p2(2, 2);
    // below are equivalent, boost:hash<Point>() creates a "hasher"
    cout << hash_value(p2) << " " << boost::hash<Point>()(p2) << endl;

    cout << hash_value(line) << endl;
    return 0;
}
