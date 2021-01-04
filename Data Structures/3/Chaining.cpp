#ifndef CHAINING_CPP
#define CHAINING_CPP
#include "Chaining.h"
#include <string>
#include <iostream>
#include "hashfunctions.cpp"

using namespace std;

HashC::HashC(int size){
    tableSize=size;
    hashTable= new LinkedList<string>[tableSize];

}
HashC::~HashC(){

}

unsigned long HashC :: hash(string input){

  return divCompression(bitHash(input),tableSize);

}

void HashC::insert(string word){

    unsigned long position= hash(word);
    hashTable[position].insertAtHead(word);
    
}

ListItem<string>* HashC :: lookup(string word){

  unsigned long position = hash(word);
  return hashTable[position].searchFor(word);
}

void HashC :: deleteWord(string word){
  unsigned long position = hash(word);
  hashTable[position].deleteElement(word);
}


// int main()
// {
//    HashC a(4);
//    a.insert("hamza");
//    a.insert("aleeza");
//    a.insert("mama");
//    a.insert("daddy");
//    a.print();
//    cout<<"FOUND: "<<a.lookup("hamza")->value<<endl;
//    a.deleteWord("hamza");
//    a.print();
//    return 0;


// }
#endif
