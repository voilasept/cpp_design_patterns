#include <iostream>
#include <sstream>
#include <map>
using namespace std;

map<string, int> countWords(istringstream is){
    string word;
    map<string, int> freq {};
    while (is >> word){
        cout << word << endl;
        if (freq.find(word) != freq.end()){
            freq[word] += 1;
        }
        else{
            freq[word] = 1;
        }
    }
    return freq;
}

ostream& operator<<(ostream& os, const map<string, int>& map_data){
    for(auto [ss, ii] : map_data){
        os << ss << ": " << ii << endl;
    }
    return os;
}

int main() {
    string input {"Huo Huo is a fox."};
    auto freq = countWords(move(istringstream{input}));
    cout << freq << endl;
    return 0;
}
