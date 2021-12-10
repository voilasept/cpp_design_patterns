#include <iostream>
#include <sstream>
using namespace std;

// This is Static Decorator.
// Dynamic Decorator is problematic, don't use it.

/* Shape : Circle, Square */
class Shape{
public:
    virtual ~Shape() = default;
};

class Circle : public Shape{
public:
    explicit Circle(int radius) : radius(radius) {}
    int radius;
    [[nodiscard]] string str() const {
        ostringstream oss;
        oss << "Circle of " << radius << " ";
        return oss.str();
    }
};

class Square : public Shape{
public:
    explicit Square(double len) : len(len){}
    double len;
    [[nodiscard]] string str() const {
        ostringstream oss;
        oss << "Square of " << len << " ";
        return oss.str();
    }
};

/* Color Mixin */
template<typename T>
class ColoredShape : public T{
public:
    template<typename ...Args>
    explicit ColoredShape(string color, Args... args)
    : color(std::move(color)), T(std::forward<Args>(args)...) {}
    string color;
    [[nodiscard]] string str() const {
        ostringstream oss;
        oss << T::str() << "of " << color << " ";
        return oss.str();
    }
};

/* Material Mixin */
enum Material {STONE, WOOD};

template<typename T>
class MaterialShape : public T{
public:
    template<typename ...Args>
    explicit MaterialShape(Material material, Args... args)
    : material(material), T(std::forward<Args>(args)...){}
    Material material;
    [[nodiscard]] string str() const {
        ostringstream oss;
        oss << T::str() << " of material " << material << " ";
        return oss.str();
    }
};


int main() {
    ColoredShape<Circle> green_circle {"green", 3};
    cout << green_circle.str() << endl;
    ColoredShape<Square> red_square {"square", 1.6};
    cout << red_square.str() << endl;

    ColoredShape<MaterialShape<Circle>> green_wood_circle {"green", Material::WOOD, 3};
    cout << green_wood_circle.str() << endl;
    MaterialShape<ColoredShape<Square>> stone_red_square {Material::STONE, "red", 1.6};
    cout << stone_red_square.str() << endl;
    return 0;
}
