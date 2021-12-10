#include <iostream>
#include <cmath>
using namespace std;

class Point{
private:
    Point(float x, float y) : x(x), y(y){}
public:
    float x, y;
    static Point NewCartesian(float x, float y);
    static Point NewPolar(float r, float theta);
    friend ostream& operator<<(ostream& os, const Point& p);
};

Point Point::NewCartesian(float x, float y) {
    return {x, y};
}

Point Point::NewPolar(float r, float theta){
    return {r * cos(theta), r * sin(theta)};
}

ostream& operator<<(ostream& os, const Point& p){
    os << p.x << " " << p.y;
    return os;
}

int main() {
    auto p = Point::NewPolar(1, 0.5);
    cout << p << endl;
    return 0;
}
