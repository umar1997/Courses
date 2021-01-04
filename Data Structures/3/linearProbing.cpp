#ifndef LINEARPROBING_CPP
#define LINEARPROBING_CPP

#include "linearProbing.h"
#include "hashfunctions.cpp"


HashL::HashL(){
    tableSize = 1000; // you cant change this
    hashTable= new block*[tableSize];
    count=0;
    for(int i=0;i<tableSize;i++)
    	hashTable[i]=NULL;
}

HashL::~HashL(){
    
}

unsigned long HashL :: hash(string value){
    return divCompression(bitHash(value),tableSize);
}

void HashL::resizeTable(){
	unsigned long oldsize= tableSize;
    if (count>tableSize*0.5)
    {
    	tableSize=2*tableSize;
    	block** temp= new block*[tableSize];
    	for(int i=0;i<tableSize;i++)
    		temp[i]=NULL;
    	
    	for (int i=0;i<oldsize;i++)
    	{
			if(hashTable[i]!=NULL)
			{
				unsigned long position = hash(hashTable[i]->value);
				while(1)
				{	
					if(temp[position]==NULL)
						break;
					++position;
					position=position%tableSize;
					
				}   			
				temp[position]= new block(position, hashTable[i]->value);
			}
		}
    	delete [] hashTable;
    	hashTable= temp;
    }
}

void HashL::insert(string value){
	unsigned long position = hash(value);
	
	while(hashTable[position]!=NULL && hashTable[position]->value!="hamza123ahmad")
	{	
		++position;
		position=position%tableSize;		
		//position= divCompression(++position, tableSize);
	}
	hashTable[position] = new block(position, value);
	count++;
	resizeTable();
}

void HashL::deleteWord(string value){
    block* delete1=NULL;
    unsigned long position = hash(value);

    while(1)
    {
        if(hashTable[position]==NULL)
            break;
        
        if (hashTable[position]->value==value)
            delete1= hashTable[position];
        
        position++;
        position=position%tableSize;
        
    }

    if(delete1)
    {
    	delete1->value="hamza123ahmad";
    	
    }

    count--;
    return;
}
block* HashL::lookup(string value){
    unsigned long position = hash(value);

    while(1)
    {
        if(hashTable[position]==NULL)
            return NULL;
    	
        if (hashTable[position]->value==value)
    		return hashTable[position];
    	
    	position++;
    	position=position%tableSize;
    	
    }
}

// void HashL::print()
// {
// 	for (int i=0;i<tableSize;i++)
// 	{
// 		cout<<i<<": "<<hashTable[i]->key<<ends<<hashTable[i]->value<<endl;
// 	}

// }


// int main()
// {
// 	HashL a;
// 	a.insert("hamza");
// 	a.insert("aleeza");
// 	// a.insert("mama");
// 	// a.insert("daddy");
// 	a.print();
// 	return 0;



// }

#endif
