#include <iostream>

#include <string>
using namespace std;

struct Renderer{
    virtual string what_to_render_as() const = 0;
};

struct Shape
{
    string name;
    Renderer* rend_ptr;
    explicit Shape(Renderer&& renderer) : rend_ptr(&renderer){};
    explicit Shape(Renderer& renderer) : rend_ptr(&renderer){};
    virtual ~Shape() = default;
    string str() const {
        return "Drawing " + name + " as " + rend_ptr->what_to_render_as();
    };
};

struct Triangle : Shape
{
    explicit Triangle(Renderer&& renderer): Shape(move(renderer)) { name = "Triangle"; }
    explicit Triangle(Renderer& renderer): Shape(renderer) { name = "Triangle"; }
};

struct Square : Shape
{
    explicit Square(Renderer&& renderer) : Shape(move(renderer)) { name = "Square"; }
    explicit Square(Renderer& renderer) : Shape(renderer) { name = "Square"; }
};


struct VectorRenderer : Renderer{
    string what_to_render_as() const override{
        return "lines";
    }
};

struct RasterRenderer : Renderer{
    string what_to_render_as() const override{
        return "pixels";
    }
};


int main() {
    cout << Triangle(RasterRenderer()).str() << endl;    //drawing triangle as pixels
    RasterRenderer rr {};
    cout << Triangle(rr).str() << endl;
    return 0;
}
