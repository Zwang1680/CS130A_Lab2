#include "dictionary.h"
#include <string>
#include <fstream>
#include <iostream>

using namespace std;

int main(int argc, const char* argv[]){
    if (argc != 3){
        cout << "ERROR: not the correct number of inputs" << endl;
        return 0;
    }
    string fname = argv[1];
    string output = argv[2];
    std::ifstream myfile(fname);
    int count = 0;
    string s;
    if (myfile.is_open()){
        while(getline(myfile, s)){
            count += 1;
        }
        dictionary d(fname, count);
        myfile.close();
        d.writeToFile(output);
    } else {
        cout << "ERROR: could not find file" << endl;
        return 0;
    }
}