#include<iostream>
using namespace std;

struct Point
{
    int x{ 0 }, y{ 0 };
    Point(){}
    Point(const int x, const int y) : x{x}, y{y} {}
    Point(const Point& other){
        x = other.x;
        y = other.y;
    }
};

struct Line
{
    Point *start, *end;
    Line(Point* const start, Point* const end)
            : start(start), end(end)
    {
    }
    ~Line()
    {
        delete start;
        delete end;
    }
    Line deep_copy() const
    {
        auto new_start_ptr = new Point(*start);
        auto new_end_ptr = new Point(*end);
        return {new_start_ptr, new_end_ptr};
    }
};

int main(){
    auto line = Line(new Point(1,2), new Point(3,4));
    auto line2 = line.deep_copy();
}