#include "Chaining.cpp"
#ifndef CHAINING__H
#define CHAINING__H
#include <string>
#include "LinkedList.cpp" // Your Own Implementation
#include <iostream>
using namespace std;
class HashC
{
	private:
		long tableSize;
		LinkedList<string>* hashTable;
		unsigned long hash(string input); // Given a String, return its hash
	public:
		HashC(int);
		~HashC(); // Destructor
		void insert(string word); // Takes a hash of 'word' and inserts it into hashTable accordingly
		void deleteWord(string word);
		ListItem<string>* lookup(string word);
};
#endif
