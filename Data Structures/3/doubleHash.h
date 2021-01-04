#include "doubleHash.cpp"
#ifndef DOUBLEHASH_H
#define DOUBLEHASH_H

#include <string>
#include <iostream>

using namespace std;
class block{
    public:
        unsigned long key;
        string value;
        block(unsigned long _key,string _value){
            this->key = _key;
            this->value = _value;
        }
};
class HashD{
    private:
        block** hashTable;
        long tableSize;
        unsigned long hash1(string value); 
        unsigned long hash2(string value);
        long count; // keeps a count of the number of entries in the table.
        void resizeTable();
    public:
        HashD();
        ~HashD();
        void insert(string value);
		void deleteWord(string value);
		block* lookup(string value);
};
#endif
