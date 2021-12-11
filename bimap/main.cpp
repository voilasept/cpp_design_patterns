#include <iostream>
#include <utility>
#include <string>
#include <boost/bimap.hpp>
using namespace std;

// 1-to-1 two-way map
typedef boost::bimap<size_t, string> BIMAP;

int main() {
    BIMAP bm;
    std::hash<string> str_hasher;
    // successful insertion
    bm.insert(decltype(bm)::value_type(str_hasher("one"), "one"));
    bm.insert(BIMAP::value_type(str_hasher("two"), "two"));

    // any duplicate (either left or right key) will be dropped!
    bm.insert(BIMAP::value_type(str_hasher("two"), "three"));
    bm.insert(BIMAP::value_type(str_hasher("three"), "two"));

    for(auto iter=bm.begin(); iter != bm.end(); iter++){
        cout << iter->left << " : " << iter->right << endl;     // key left/right!
    }
    cout << string(5, '-') << endl;

    // left map view
    for(auto iter=bm.left.begin(); iter!=bm.left.end(); iter++){
        cout << iter->first << " : " << iter->second << endl;   // key first/second!
    }
    cout << string(5, '-') << endl;

    // right map view
    for(auto iter=bm.right.begin(); iter!=bm.right.end(); iter++){
        cout << iter->first << " : " << iter->second << endl;
    }
    cout << string(5, '-') << endl;

    // erase from right map changes left map
    bm.right.erase("two");
    for(auto iter=bm.left.begin(); iter!=bm.left.end(); iter++){
        cout << iter->first << " : " << iter->second << endl;
    }
    return 0;
}
