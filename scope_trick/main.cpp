#include <iostream>
#include <utility>
using namespace std;

class DataLoader{
public:
    string dir;
    DataLoader(string&& dir):dir(dir){};
    void set_dir(string new_dir){dir=move(new_dir);};
    string& get_dir() { return dir; }
};

class UserToken{
public:
    DataLoader& loader;
    string user_name;
    string old_dir;
    UserToken(string&& user_name, DataLoader& loader):user_name(user_name), loader(loader){
        old_dir = loader.dir;
        loader.set_dir(old_dir + "/"s + user_name);
    };
    ~UserToken(){
        loader.set_dir(old_dir);
    }
};

int main() {
    auto loader = DataLoader("/usr/local/bin");
    {
        UserToken hchen {"hchen", loader};
        cout << "Inside: " << loader.get_dir() << endl;
    }
    cout << "Outside: " << loader.get_dir() << endl;
    return 0;
}
