#include "dictionary.h"
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

using namespace std;

int main(int argc, const char* argv[]){
    if (argc != 3){
        cout << "ERROR: not the correct number of inputs" << endl;
        return 0;
    } 
    string fname = argv[1];
    string input = argv[2];
    vector <string> inputs;
    // ifstream file;
    // file.open(fname, ios::in | ios::binary);
    //cout << "your here" << endl;
    int begin = 0;
    for(int i = 0; i < input.length(); i++){
        if (input[i] == ','){
            inputs.push_back(input.substr(begin, i-begin));
            begin = i + 2;
            i =begin;
        }
        if (i == input.length()-1){
            inputs.push_back(input.substr(begin, i-begin+1));
        }
    }
    // if (file.is_open()){
    //     file.close();
        dictionary d = dictionary::readFromFile(fname);
        for (int i = 0; i < inputs.size(); i++){
            if (d.find(inputs[i])){
                cout << inputs[i] << " found" << endl;
            } else {
                cout << inputs[i] << " not found" << endl;
            }
        }
    // } else {
    //     cout << "file not found" << endl;
    // }
}