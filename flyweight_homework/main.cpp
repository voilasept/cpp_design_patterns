#include <iostream>
#include <map>
#include <sstream>
#include <utility>
using namespace std;

struct Sentence
{
private:
    string plain_text;
    struct WordToken
    {
        explicit WordToken(bool capitalize):capitalize(capitalize){}
        bool capitalize;
    };
    map<size_t, WordToken*> tokens {};
public:
    explicit Sentence(string&& text):plain_text(text) {}
    ~Sentence(){
        for(auto iter:tokens){
            delete iter.second;
        }
    }
    WordToken& operator[](size_t index)
    {
        if(auto ti=tokens.find(index);
           ti==tokens.end()){
            auto* token = new WordToken {false};
            tokens.insert({index, token});
        }
        return *tokens[index];
    }
    [[nodiscard]] string str() const
    {
        ostringstream oss;
        auto word_cnt = pair<int, int>{0, 0};   // {last_word_cnt, word_cnt}
        bool is_space = true;
        bool word_capitalize = false;
        for(char c : plain_text){
            if(is_space and c!=' '){ word_cnt.second++; }
            if (word_cnt.first != word_cnt.second) {
                if (auto wt = tokens.find(word_cnt.first);
                        wt != tokens.end()) {
                    word_capitalize = wt->second->capitalize;
                } else {
                    word_capitalize = false;
                }
                word_cnt.first = word_cnt.second;
            }
            if(word_capitalize)  oss << static_cast<char>(toupper(c));
            else  oss << c;
            is_space = c==' ';
        }
        return oss.str();
    }
};

int main() {
    Sentence sentence ("the   world   is a bag.");
    sentence[1].capitalize = true;
    sentence[4].capitalize = true;
    sentence[0].capitalize = false;
    cout << sentence.str();
    return 0;
}
