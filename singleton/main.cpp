#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <memory>
using namespace std;

#include <boost/lexical_cast.hpp>

class DataBase{
private:
    static map<string, shared_ptr<DataBase>> dbs;  // bind to class
    explicit DataBase(const string& file_name){  // private constructor
        ifstream fs(file_name);
        string city, popu_str;
        int popu;
        while(getline(fs, city)){
            getline(fs, popu_str);
            popu = boost::lexical_cast<int>(popu_str);
            loaded_data[city] = popu;
        }
    }
public:
    map<string, int> loaded_data {};    // bind to object
    DataBase(const DataBase&) = delete;
    DataBase& operator=(const DataBase&) = delete;
    static shared_ptr<DataBase> get(const string& file_name){
        if (dbs.find(file_name) == dbs.end()){
            dbs[file_name] = shared_ptr<DataBase>(new DataBase (file_name));
        }
        return dbs[file_name];
    }
    friend ostream& operator<<(ostream& os, const DataBase& db){
        for(auto [city, popu] : db.loaded_data){
            os << city << ": " << popu << endl;
        }
        return os;
    }
};

// static must be defined out-of-line, otherwise gets undefined DataBase::dbs
map<string, shared_ptr<DataBase>> DataBase::dbs {};  //

int main() {
    auto db = DataBase::get("/Users/hanchen/CLionProjects/singleton/population.txt");
    cout << *db;
    auto db2 = DataBase::get("/Users/hanchen/CLionProjects/singleton/population.txt");
    cout << db << endl << db2 << endl << endl;  // same address
    auto db3 = DataBase::get("/Users/hanchen/CLionProjects/singleton/wealth.txt");
    cout << *db3;
    cout << db3 << endl;
    return 0;
}
