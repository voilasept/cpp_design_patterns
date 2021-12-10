#include <iostream>
#include <vector>
using namespace std;

class ContainsIntegers{
public:
    virtual ~ContainsIntegers() = default;
    [[nodiscard]] virtual int get_sum() const = 0;
};

class SingleValue : public ContainsIntegers{
public:
    explicit SingleValue(int value):value(value){}
    [[nodiscard]] int get_sum() const override {return value;}
private:
    int value;
};

class ManyValues : public ContainsIntegers{
public:
    ManyValues() = default;
    vector<ContainsIntegers*> children;
    void add(int new_value){
        auto* nv = new SingleValue {new_value};
        children.push_back(nv);
    }
    [[nodiscard]] int get_sum() const override {
        int result {0};
        for(auto v : children){
            result += v->get_sum();
        }
        return result;
    }
};

int sum(const vector<ContainsIntegers*> items)
{
    int result {0};
    for(auto v : items){
        result += v->get_sum();
    }
    return result;
}

int main() {
    SingleValue single_value {1};
    ManyValues other_values;
    other_values.add(2);
    other_values.add(3);
    cout << sum({&single_value, &other_values});
    return 0;
}
