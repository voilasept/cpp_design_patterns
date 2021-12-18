#include <pybind11/pybind11.h>
namespace py = pybind11;

int add(int i, int j) {
    return i + j;
}

PYBIND11_MODULE(hello_world, m) {   // arg1: module_name
m.doc() = "pybind11 example plugin"; // optional module docstring

m.def("add", &add, "A function which adds two numbers");
}

/*
 * NOTE:
 * install python-dev:  bin/brew install python3
 *
 * CMakeLists.txt
 * include_directories(/usr/local/Cellar/python@3.9/3.9.9/Frameworks/Python.framework/Versions/3.9/include/python3.9)
 *
 * compile (-undefined dynamic_lookup is required for macOS)
 * $$ c++ -O3 -Wall -shared -std=c++11 -fPIC $(python3 -m pybind11 --includes) hello_world.cpp -o hello_world$(python3-config --extension-suffix) -undefined dynamic_lookup
 *
 * $$ c++ -O3 -Wall -shared -std=c++11 -fPIC $(python3 -m pybind11 --includes) hello_world.cpp -o hello_world.so -undefined dynamic_lookup
 *
 * NOTE (12/17/2021)
 * Because I updated gcc, use the updated compiler instead:
 * /Library/Developer/CommandLineTools/usr/bin/c++ -O3 -Wall -shared -std=c++11 -fPIC $(python3 -m pybind11 --includes) hello_world.cpp -o hello_world.so -undefined dynamic_lookup
 *
 * NOTE:
 * To make Pycharm recognize hello_world.so:
 * python interpreter => [setting]show all => click on "tree" button => add dir path to .so
 *
 * NOTE (12/17/2021)
 * export PYTHONPATH=$PYTHONPATH:/usr/local/cpplib/pybind11/
 * to fix the error:
 * /Users/hanchen/CLionProjects/pybind_test/venv/bin/python3: No module named pybind11
 */