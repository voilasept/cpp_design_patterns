#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

int main() {
    /*
     * fstream: for both read/write
     * ifstream: read-only (in)
     * ofstream: write-only (out)
     */
    string file_name = "/Users/hanchen/CLionProjects/fstream/test.txt";
    fstream ofile;
    ofile.open(file_name, fstream::out);
    ofile << "Hello World\n";
    ofile.close();

    auto load_file = [&](){
        ifstream ifile;
        ifile.open(file_name);
        stringstream ss;
        ss << ifile.rdbuf();    // NOTE: rdbuf readbuffer
        cout << ss.str() << endl << endl;
        ifile.close();
    };

    load_file();

    ofile.open(file_name, fstream::out | fstream::app);     // append
    ofile << "Watermelon\n";
    ofile.close();

    load_file();

    ofile.open(file_name, fstream::out | fstream::trunc);   // overwrite
    ofile << "Overwritten\n";
    ofile.close();

    load_file();
    return 0;
}
