#include <iostream>
#include <string>
#include <ostream>
#include <vector>
#include <utility>
using namespace std;

class CodeBuilder;

class Code {
    friend class CodeBuilder;
private:
    string class_name;
    vector<pair<string, string>> attributes;
    explicit Code(string class_name) : class_name(move(class_name)) {}
    Code() = default;
};

class CodeBuilder
{
private:
    Code code;
public:
    explicit CodeBuilder(const string& class_name){
        code.class_name = class_name;
    }

    CodeBuilder& add_field(const string& name, const string& type){
        code.attributes.emplace_back(make_pair(name, type));
        return *this;
    }

    friend ostream& operator<<(ostream& os, const CodeBuilder& obj)
    {
        os << "class " + obj.code.class_name << endl;
        os << "{" << endl;
        for (auto [name, type] : obj.code.attributes){
            os << "  " << type + " " << name << ";" << endl;
        }
        os << "};" << endl;
        return os;
    }
};

int main() {
    auto cb = CodeBuilder{"Person"}.add_field("name", "string").add_field("age", "int");
    cout << cb;
    return 0;
}
