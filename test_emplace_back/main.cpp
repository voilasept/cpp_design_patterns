#include <cstdio>
#include <vector>
using namespace std;
class S {
public:
    S(){ puts("S()"); }         // constructor
    S(int){ puts("S(int)"); }      // custom constructor
    S(const S&){ puts("S(const & S)"); }    // copy constructor
    S(S&&) noexcept { puts("S(S&&)"); }  // move constructor
    S& operator=(const S&){ puts("operator=(const S&)"); return *this; }   // copy assignment
    S& operator=(S&&) noexcept { puts("operator=(S&&)"); return *this; }  // move assignment
    ~S(){ puts("~S()"); }   // destructor
};

int main() {
    vector<S> vec;
    vec.emplace_back(3);
//    vec.push_back(S(3));
    return 0;
}
