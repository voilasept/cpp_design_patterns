#include <move_semantics//holder.h>
#include <iostream>
enum Color {red, green, blue};

int main(){
    Color color = Color::blue;
    std::cout << color << std::endl;

    Holder h1(100);
    Holder h2(300);

    // assignment constructor is called for replacement
    h2 = h1;    // operator=

    // copy constructor is called for initialization
    Holder h3 = h1;     // copy constructor
    std::cout << "A " << h1.m_size << std::endl;
    Holder h4(h1);      // copy constructor
    std::cout << "B " << h1.m_size << std::endl;
    Holder h5(std::move(h1));   // move lvalue to rvalue, thus move constructor
    std::cout << "C " << h1.m_size << std::endl;    // h1 becomes a hollow object

    // move constructor: construct new objects
    // move assignent operator: replace existing object
    std::cout << "Milestone" << std::endl;
    Holder h6 = Holder(150);
    // rvalue ref (&&obj) can't bind to lvalue (h4)
    // Holder tmp = h5.rref_modify(h4);  // error
    Holder tmp = h5.rref_modify(Holder(300));
    std::cout << h5.m_size << std::endl;


    return 0;
}