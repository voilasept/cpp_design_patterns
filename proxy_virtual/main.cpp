#include <iostream>
#include <string>
using namespace std;

class Loader{
public:
    string filename;
    Loader() = default;
    ~Loader() = default;
    explicit Loader(const string& filename):filename(filename){
        cout << "Expensive Load: " << filename << endl;
    }
    void process() const{
        cout << "Process: " << filename << endl;
    }
};

class LazyLoader : public Loader{
protected:
    Loader* loader {};
public:
    explicit LazyLoader(const string& filename):Loader(){
        this->filename = filename;
    }
    void process(){
        if (!loader){
            loader = new Loader {filename};
        }
        loader->process();
    }
};

int main() {
    auto loader = Loader("xyz.txt");
    cout << "waiting..." << endl;
    loader.process();

    cout << "------" << endl;

    auto lazy_loader = LazyLoader("xyz.txt");
    cout << "waiting..." << endl;
    lazy_loader.process();
    return 0;
}
