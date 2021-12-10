#include <iostream>
#include <memory>
#include <ostream>
#include <utility>
#include <vector>
#include <initializer_list>
using namespace std;

class TagBuilder;

struct Tag{
public:
    friend class TagBuilder;
    Tag() = default;
    Tag(string name, string text
    ): name(std::move(name)), text(std::move(text)){}
    Tag(string name, const vector<Tag>& children
    ): name(std::move(name)), children(children){}
    string name, text;
    vector<Tag> children;
    vector<pair<string, string>> attributes;

    static TagBuilder create(string name, string text);

    friend ostream& operator<<(ostream&, const Tag&);
};

struct Para : public Tag{
public:
    explicit Para(string text):Tag("Para", std::move(text)){}
};

struct IMG : public Tag{
public:
    IMG() = default;
    explicit IMG(const string& url){
        attributes.emplace_back(make_pair("url", url));
    }
};

class TagBuilder{
public:
    Tag root;
    TagBuilder(string&& name, string&& text){
        root.text = text;
        root.name = name;
        name.clear();
        text.clear();
    }
    TagBuilder& add_child(const Tag& tag){
        root.children.emplace_back(tag);
        return *this;
    }
    explicit operator Tag() const {
        return root;
    }
};

ostream& operator<<(ostream& os, const Tag& tag){
    os << "<" << tag.name;
    for(const auto& attr : tag.attributes){
        os << " " << attr.first << "=\"" << attr.second << "=\"";
    }
    if (not tag.children.empty() and tag.text.length() == 0){
        os << "/>" << endl;
    }
    else{
        os << ">" << endl;
        if (tag.text.length()){
            os << tag.text << endl;
        }
        for (const auto& child: tag.children){
            os << child;
        }
        os << "</" << tag.name << ">" << endl;
    }
    return os;
}

TagBuilder Tag::create(string name, string text) {
    return {move(name), move(text)};
}


int main()
{
    Tag tag = static_cast<Tag>(
            Tag::create("Da", "Quan").add_child(
                    {"black", "bean"} ) );
    TagBuilder tb = TagBuilder("hello", "birdy").add_child(
            {"pepper", "rice"});
    string name0 {"Chilli"};
    string text0 {"Curry"};
    tb.add_child({name0, text0});
    cout << static_cast<Tag>(tb) << endl;

    Para p = Para("para_text");
    cout << p << endl;

    IMG img = IMG("http:/");
    cout << img << endl;
    return 0;
}
