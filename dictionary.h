#ifndef DICTIONARY
#define DICTIONARY
#include "hash24.h"
#include <vector>
#include <utility>
#include <string>

class dictionary{

    public:
        dictionary(std::string fname, int tsize);
        dictionary(std::pair<std::string, std::string*> *table1,
                Hash24 primaryhash1,
                Hash24 *sechash1,
                int *collisions1,
                int *hashattempts1,
                int numword1,
                int tsize);
        ~dictionary();
        bool find(std::string word);
        void writeToFile(std::string fname);
        static dictionary readFromFile(std::string fname);
    private:
        std::pair<std::string, std::string*> *table;
        Hash24 primaryhash;
        Hash24 *sechash;
        int *collisions;
        int *hashattempts;
        int numword;
        const int size;
        void rehash(std::string s, int phash, int shash);
        int findmax();
};

#endif