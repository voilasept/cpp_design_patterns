#include <iostream>
#include <functional>
#include <string>
using namespace std;

template<typename Func>
class LogFunc{
public:
    explicit LogFunc(const Func& func) : func(func) {}
    const Func& func;
    template<typename ...Args>
    auto operator()(const string& save_to, Args ...args){
        auto result = func(std::forward<Args>(args)...);
        cout << "result: " << result << " saved to " << save_to << endl;
        return result;
    }
};

template<typename Func>
auto log_func(const Func& func){
    return LogFunc<Func> {func};
}


double add(double x, double y){
    return x+y;
}

unsigned long count_str(const string& input){
    return input.size();
}

int main() {
    auto log_add = log_func(add);
    auto log_count = log_func(count_str);
    log_add("google_drive", 1.1, 2.2);
    log_count("dropbox", "hello"s);
    return 0;
}
