#include "dictionary.h"

#include "hash24.h"
#include <iostream>
#include <utility>
#include <string>
#include <fstream>
#include <stdlib.h> 

using namespace std;

dictionary::dictionary(std::string fname, int tsize) : size(tsize){
    if (tsize <= 0){
        cout << "tsize is 0" << endl;
        exit (EXIT_FAILURE);
    }
    std::ifstream myfile(fname);
    const int size = tsize;
    table = new std::pair<std::string, string*>[size];
    for (int i = 0; i < tsize; i++){
        table[i].second = new string[tsize];
    }
    string line = "";
    sechash = new Hash24[size];
    int x, y;
    numword = 0;
    collisions = new int[size];
    hashattempts = new int[size];
    if (myfile.is_open()){
        while (std::getline(myfile, line)){
            numword += 1;
            x = primaryhash.hash(line);
            x = x % tsize;
            if (table[x].first.length() == 0){
                table[x].first = line;
            } else {
                if (hashattempts[x] == 0){
                    hashattempts[x] = 1;
                }
                collisions[x] += 1;
                y = sechash[x].hash(line);
                y = y % tsize;
                if ((table[x].second)[y].length() == 0){
                    (table[x].second)[y] = line;
                } else {
                    dictionary::rehash(line, x, y);
                }
            }
        }
        myfile.close();
    } else {
        std::cout << "Error: could not find file" << std::endl;
    }
    int collisionamount[20];
    for (int i = 0; i < tsize; i++){
        if(collisions[i]<20){
            if (collisions[i]==0 && table[i].first.length() == 0){
                collisionamount[0] +=1;
            } else if (collisions[i] == 0){
                collisionamount[1] += 1;
            } else {
                collisionamount[collisions[i]+1] += 1;
            }
        }
    }
    int hashnum[20];
    int hashmean;
    int hashcount;
    for (int i = 0; i <tsize; i++){
        if(hashattempts[i] < 20){
            hashnum[hashattempts[i]] += 1;
        }
        if (hashattempts[i] != 0){
            hashmean += hashattempts[i];
            hashcount += 1;
        }
    }
    hashmean = hashmean/hashcount;
    int maxhash = dictionary::findmax();
    int maxcollisions = collisions[maxhash];
    primaryhash.dump();
    cout << "Number of words = " << numword << endl;
    cout << "Table size = " << size << endl;
    cout << "Max collisions = " << maxcollisions << endl;
    for (int i = 0; i < 20; i++){
        cout << "# of primary slots with " << i << " words = " << collisionamount[i] << endl;
    }
    cout << "*** Words in the slot with most collisions ***" << endl;
    cout << table[maxhash].first << endl;
    for (int i =0; i < tsize; i++){
        if (table[maxhash].second[i].length() != 0){
            cout << table[maxhash].second[i] << endl;
        }
    }
    for (int i =1; i< 20; i++){
        cout << "# of secondary hash tables trying " << i << " hash functions = " << hashnum[i] << endl;
    }
    cout << "Average # of hash functions tried = " << hashmean << endl;
    // cout << table[maxhash].first << endl;
    // for (int i = tsize - 1; i >= 0; i--){
    //     if (table[i].first.length() != 0){
    //         cout << table[i].first << " ";
    //         if (table[i].second){
    //             for (int j = 0; j < tsize; j++){
    //                 if(table[i].second[j].length() != 0){
    //                     cout << table[i].second[j]<< " ";
    //                 }
    //             }
    //         }
    //         cout << "\n";
    //     }
    // }
}

dictionary::dictionary(std::pair<std::string, std::string*> *table1,
    Hash24 primaryhash1,
    Hash24 *sechash1,
    int *collisions1,
    int *hashattempts1,
    int numword1,
    int tsize) : size(tsize){
        table = table1;
        primaryhash = primaryhash1;
        sechash = sechash1;
        collisions = collisions1;
        hashattempts = hashattempts1;
        numword = numword1;
        for (int i = 0; i < tsize; i++){
            if (table[i].first.length() != 0){
                cout << table[i].first << " ";
                for (int j = 0; j < tsize; j++){
                    if (table[i].second[j].length() != 0){
                        cout << table[i].second[j] << " ";                    }
                }
            }
        }
        // int collisionamount[20] = {0};
        // for (int i = 0; i < size; i++){
        //     if(collisions[i]<20){
        //         if (collisions[i]==0 && table[i].first.length() == 0){
        //             collisionamount[0] +=1;
        //         } else if (collisions[i] == 0){
        //             collisionamount[1] += 1;
        //         } else {
        //             collisionamount[collisions[i]+1] += 1;
        //         }
        //     }
        // }
        // int hashnum[20] = {0};
        // int hashmean = 0;
        // int hashcount = 0;
        // for (int i = 0; i < size; i++){
        //     if(hashattempts[i] < 20){
        //         hashnum[hashattempts[i]] += 1;
        //     }
        //     if (hashattempts[i] != 0){
        //         hashmean += hashattempts[i];
        //         hashcount += 1;
        //     }
        // }
        // hashmean = hashmean/hashcount;
        // int maxhash = dictionary::findmax();
        // int maxcollisions = collisions[maxhash];
        // primaryhash.dump();
        // cout << "Number of words = " << numword << endl;
        // cout << "Table size = " << size << endl;
        // cout << "Max collisions = " << maxcollisions << endl;
        // for (int i = 0; i < 20; i++){
        //     cout << "# of primary slots with " << i << " words = " << collisionamount[i] << endl;
        // }
        // cout << "*** Words in the slot with most collisions ***" << endl;
        // cout << table[maxhash].first << endl;
        // for (int i =0; i < tsize; i++){
        //     if (table[maxhash].second[i].length() != 0){
        //         cout << table[maxhash].second[i] << endl;
        //     }
        // }
        // for (int i =1; i< 20; i++){
        //     cout << "# of secondary hash tables trying " << i << " hash functions = " << hashnum[i] << endl;
        // }
        // cout << "Average # of hash functions tried = " << hashmean << endl;
    }

dictionary::~dictionary(){
    for (int i = 0; i < size; i++){
        delete[] table[i].second;
    }
    delete[] table;
    delete[] hashattempts;
    delete[] collisions;
    delete[] sechash;
}

void dictionary::rehash(string s, int phash, int shash){
    vector<string> temp;
    temp.push_back(s);
    hashattempts[phash] += 1;
    Hash24 *thash = &(sechash[phash]);
    sechash[phash] = *(new Hash24);
    delete thash;
    for(int i=0; i < size; i++){
        if ((table[phash].second)[i].length() != 0){
            temp.push_back(table[phash].second[i]);
        }
    }
    string *tstr = table[phash].second;
    table[phash].second = new string[size];
    delete[] tstr;
    int y;
    for (int i = 0; i < temp.size(); i++){
        y = sechash[phash].hash(temp[i]);
        y = y % size;
        if (table[phash].second[y].length() != 0){
            rehash(s, phash, shash);
        } else {
            table[phash].second[y] = temp[i];
        }
    }
}

bool dictionary::find(string word){
    int x = primaryhash.hash(word);
    x = x % size;
    if (table[x].first == word){
        return true;
    } else {
        int y = sechash[x].hash(word);
        y = y % size;
        if(!(table[x].second)){
            return false;
        }
        if (table[x].second[y] == word){
            return true;
        }
    }
    return false;
}


int dictionary::findmax(){
    int x = collisions[0];
    int c = 0;
    for (int i = 0; i < size; i++){
        if (collisions[i] > x){
            x = collisions[i];
            c = i;
        }
    }
    return c;
}

void dictionary::writeToFile(string fname){
    ofstream out_file;
    out_file.open(fname, ios::out | ios::binary);
    out_file.write((char*)&size, sizeof(size));
    out_file.write((char*)&numword, sizeof(numword));
    out_file.write((char*)&primaryhash, sizeof(primaryhash));
    for (int i = 0; i < size; i++){
        out_file.write((char*)&sechash[i], sizeof(sechash[i]));
        out_file.write((char*)&collisions[i], sizeof(collisions[i]));
        out_file.write((char*)&hashattempts[i], sizeof(hashattempts[i]));
    }
    for (int i = 0; i < size; i++){
        if(table[i].first.length() != 0){
            size_t len = table[i].first.length();
            out_file.write((char*)&len, sizeof(len));
            out_file.write(table[i].first.c_str(), table[i].first.length());
            if (table[i].second){
                for(int j = 0; j < size; j++){
                    if(table[i].second[j].length() != 0){
                        size_t len = table[i].second[j].length();
                        out_file.write((char*)&len, sizeof(len));
                        out_file.write(table[i].second[j].c_str(), len);
                    }
                }
            }
        }
    }
}

dictionary dictionary::readFromFile(string fname){
    ifstream in_file;
    in_file.open(fname, ios::in | ios::binary);
        int tsize;
        in_file.read((char*)&tsize, sizeof(tsize));
        //cout << tsize << endl;
        int numword;
        in_file.read((char*)&numword, sizeof(numword));
        //cout << "here" << endl;
        Hash24 primhash;
        in_file.read((char*)&primhash, sizeof(primhash));
        Hash24 *seconhash = new Hash24[tsize];
        int *tempcollision = new int[tsize];
        int *temphashattempt = new int[tsize];
        int temp1;
        //cout << "here" << endl;
        Hash24 temp2;
        for (int i = 0; i < tsize; i++){
            //cout << "here" << endl;
            in_file.read((char*)&temp2, sizeof(temp2));
            //cout << "here" << endl;
            seconhash[i] = temp2;
            in_file.read((char*)&temp1, sizeof(temp1));
            tempcollision[i] = temp1;
            //cout << tempcollision[i] << " ";
            in_file.read((char*)&temp1, sizeof(temp1));
            temphashattempt[i] = temp1;
        }
        //cout<< "here" << endl;
        std::pair<std::string, std::string*> *table = new std::pair<std::string, string*>[tsize];
        //cout << "here" << endl;
        for (int i = 0; i < tsize; i++){
            table[i].second = new string[tsize];
        }
        for (int i = 0; i < numword; i++){
            //cout << "here" << endl;
            size_t len = 0;
            //cout << "here" << endl;
            in_file.read((char*)&len, sizeof(len));
            //cout << "here" << endl;
            char* strData = new char[len];
            //cout << "here" << endl;
            in_file.read(strData, len);
            //cout << "here" << endl;
            string stringtemp(strData);
            // cout << "here" << endl;
            // cout << stringtemp << " ";
            // cout << "here" << endl;
            int x = primhash.hash(stringtemp);
            //cout << "here" << endl;
            x = x % tsize;
            //cout << "here" << endl;
            if (table[x].first.length() == 0){
                //cout<< table[x].first.length() << " ";
                table[x].first = stringtemp;
                //cout << table[x].first << " ";
            } else {
                //cout << "bruh" << endl;
                int y = seconhash[x].hash(stringtemp);
                y = y % tsize;
                table[x].second[y] = stringtemp;
            }
        }
    in_file.close();
    //cout << "out of file" << endl;
    dictionary boi(table, primhash, seconhash, tempcollision, temphashattempt, numword, tsize);
    return boi;
}