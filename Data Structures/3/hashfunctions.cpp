#ifndef HASHFUNCTIONS_CPP
#define HASHFUNCTIONS_CPP
#include <string>
#include <cmath>
// this takes in a string and returns a 64bit hash.
unsigned long polyHash(std::string value,int a = 5){
	unsigned long x=0.0;
	int k= value.length();
	for (int i=0;i<k;i++)
	{
		x+= int(value[i]) * pow(a,k-i);
	}
	return x;
}
//does some bitwise operation and generates a 64bit hash.
unsigned long bitHash(std::string value){
	unsigned long x=0.0;
	int k= value.length();
	for (int i=0;i<k;i++)
	{
		x^= (x<<5) + (x>>2) + int(value[i]);
	}
	return x;
}
// Size is the size of array maintained by the hashtable.
unsigned long divCompression(unsigned long hash,long size){
    unsigned long x = (hash) % size;
    return x;
}
// multiplication addition and division compression.
unsigned long madCompression(unsigned long hash,long size,int m = 1993,int a = 1637){
    unsigned x = ((a*hash)+m) % size;
    return x;
}
// 'm' and 'a' can take any value
#endif
// you may write your own program to test these functions.
