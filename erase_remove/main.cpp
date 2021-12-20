#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main() {
    int arr [] {2, 1, 3, 3, 2, 1};
    auto new_end = remove(arr, arr + sizeof(arr) / sizeof(int), 2);
    // remove shunts values forward, but doesn't reduce container size, returns iterator to new end
    // O(N) complexity
    for(auto& i : arr){
        cout << i << " ";
    }
    cout << endl;
    for(int* iptr=arr; iptr!=new_end; iptr++){
        cout << *iptr << " ";
    }
    cout << endl;

    // how to properly erase:
    vector<int> arr2 {2, 1, 3, 3, 2, 1};
    arr2.erase(     // changes container size
            remove(arr2.begin(), arr2.end(), 2),  // first to erase
            arr2.end()                                              // last to erase
    );
    for(auto& i:arr2){
        cout << i << " ";
    }
    cout << "container size: " << arr2.size() << endl;
    return 0;
}
