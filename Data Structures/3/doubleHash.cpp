#ifndef DOUBLEHASH_CPP
#define DOUBLEHASH_CPP
#include "doubleHash.h"
#include "hashfunctions.cpp"
HashD::HashD(){
    tableSize = 10000; // you cant change this
    hashTable= new block*[tableSize];
    count=0;
    for(int i=0;i<tableSize;i++)
    	hashTable[i]=NULL;
}

HashD::~HashD(){

}

unsigned long HashD :: hash1(string value){
    unsigned long hash = (3 - bitHash(value)%3);
    //unsigned long hash= madCompression(polyHash(value),tableSize);
    return hash;
}

unsigned long HashD :: hash2(string value){
    unsigned long hash= madCompression(bitHash(value),tableSize);
    return hash;								
}

void HashD::resizeTable(){
	unsigned long oldsize= tableSize;
    
    	tableSize=20*tableSize;
    	//cout<<"new size is "<< tableSize<<endl;
    	block** temp= new block*[tableSize];
    	for(int i=0;i<tableSize;i++)
    		temp[i]=NULL;
    	
    	for (int j=0;j<oldsize;j++)
    	{
			if(hashTable[j]!=NULL)
			{	
				unsigned long i=0;
				unsigned long position= madCompression(hash1(hashTable[j]->value),tableSize) + (i*(hash2(hashTable[j]->value),tableSize));

				while(1)
				{
					if(temp[position]==NULL)
					{
						temp[position]= new block(position, hashTable[j]->value);
						break;
					}	
					++i;
					unsigned long hash11=(hash1(hashTable[j]->value));
					unsigned long hash22=(hash2(hashTable[j]->value));
		
					position=(hash11 + (i*hash22)) % tableSize;	
				}
				
			}
		}
    	delete [] hashTable;
    	hashTable= temp;
   

}

void HashD::insert(string value){
	unsigned long i= 0;
    unsigned long position =madCompression(hash1(value)+ (i*hash2(value)),tableSize);

	while(hashTable[position]!=NULL && hashTable[position]->value!="hamza123ahmad")
	{		
		++i;
		position=(hash1(value) + (i*hash2(value))) % tableSize;		
	}

	hashTable[position] = new block(position, value);
	count++;
	if (count>tableSize*0.5)
		resizeTable();
}

void HashD::deleteWord(string value){
    unsigned long i=0;
    unsigned long position = madCompression(hash1(value)+ (i*hash2(value)),tableSize);
    block* delete1=NULL;
    while(1)
    {
        if(hashTable[position]==NULL)
            break;

    	if (hashTable[position]->value==value)
    		{
    			delete1= hashTable[position];
    			break;
    		}
    	
    	++i;
    	position=(hash1(value) + (i*hash2(value))) % tableSize;	
    }
    if(delete1)
    {
    	delete1->value="hamza123ahmad";
    	
    }

    count--;
    return;
}

block* HashD::lookup(string value){
    unsigned long i=0;
    unsigned long position = madCompression(hash1(value)+ (i*hash2(value)),tableSize);
    
    while(1)
    {
    	if (hashTable[position]==NULL)
    		return NULL;
    	
    	if (hashTable[position]->value==value)
    		return hashTable[position];
    	
    	++i;
    	position=(hash1(value) + (i*hash2(value))) % tableSize;	
       	
    }
}

#endif