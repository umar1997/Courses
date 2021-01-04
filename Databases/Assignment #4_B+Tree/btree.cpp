// C++ program for B-Tree insertion 
#ifndef __BTREE_CPP
#define __BTREE_CPP

#include "btree.h"


using namespace std; 

Node::Node(){
	keySize = 0;
	for(int i = 0;i<DEG;i++)
	{
		
		key.push_back(900000);

	}
	for (int i = 0; i < DEG+1; ++i)
	{
		children.push_back(NULL);
		vector<int> v;
		for (int i = 0; i < DEG; ++i)
		{
			v.push_back(100000);
		}
		value.push_back(v);
	}
}


bool compareInterval(int i1, int i2) 
{ 
	 return (i1 < i2); 
} 


BPlusTree::BPlusTree(int _m){

	DEG = _m;
	root = NULL;
}

string BPlusTree::display(){
	// Do not edit this function
	ss.str("");
	traverse(root);
	string s = ss.str();
	for(int i = s.length()-1; i>0; i--)
	{
		if(s[i] == ' ')
		{
			s.erase(i,1);
		}
		else
		{
			break;
		}
	}
	s+=" ";
	return s;
}

void BPlusTree::traverse(Node* cursor){
	
	// Do not edit this function
	if(cursor!=NULL)
	{
		for(int i = 0; i < DEG; i++)
		{
			if(cursor->key[i]!=900000){
				ss<<"{"<<cursor->key[i]<<"}";
			}

		}
		ss<<" ";
		if(cursor->isLeaf)
		{
			for(int i = 0; i < DEG; i++)
			{
				for (int j = 0; j < DEG; ++j)
				{
					if(cursor->value[i][j]!=100000){
						ss<<"{"<<cursor->value[i][j]<<"}";
					}
				}
				if(i!=DEG-1)
				{
					ss<<" ";
				}
			}
			ss<<" ";
		}
		else
		{
			for(int i = 0; i < DEG+1; i++)
			{
				traverse(cursor->children[i]);
			}
		}
	}
}

void BPlusTree::print()
{
	cout << "Key: " << endl;
	for(int i = 0;i<DEG; i++)
	{
		cout << root->key[i] << endl;
	}
	cout << "##################" << endl;
	cout << "Value: " << endl;
	cout << "---------------------" << endl;
	for(int i = 0;i<DEG+1; i++)
	{
		for (int j = 0; j < root->value[i].size(); ++j)
		{			
			cout << root->value[i][j] << endl;
		}
		cout << "---------------------" << endl;
	}





	cout << "Key: " << endl;
	for(int i = 0;i<DEG; i++)
	{
		cout << (root->children[0])->key[i] << endl;
	}
	cout << "##################" << endl;
	cout << "Value: " << endl;
	cout << "---------------------" << endl;
	for(int i = 0;i<DEG+1; i++)
	{
		for (int j = 0; j < (root->children[0])->value[i].size(); ++j)
		{			
			cout << (root->children[0])->value[i][j] << endl;
		}
		cout << "---------------------" << endl;
	}





	cout << "Key: " << endl;
	for(int i = 0;i<DEG; i++)
	{
		cout << (root->children[1])->key[i] << endl;
	}
	cout << "##################" << endl;
	cout << "Value: " << endl;
	cout << "---------------------" << endl;
	for(int i = 0;i<DEG+1; i++)
	{
		for (int j = 0; j < (root->children[1])->value[i].size(); ++j)
		{			
			cout << (root->children[1])->value[i][j] << endl;
		}
		cout << "---------------------" << endl;
	}

}

void BPlusTree::filler(int m,int k)
{
	bool emptySpace = false;
	for(int i = 0; i<DEG; i++)
	{
		if(root->value[m][i] == 100000)
		{
			emptySpace = true;
			root->value[m][i] = k;
			sort(root->value[m].begin(), root->value[m].end(),compareInterval);
			return;
		}
	}
	if(!emptySpace && m+1<=DEG)
	{
		if(!emptySpace && m == root->keySize)
		{
			root->value[m].push_back(k);
			sort(root->value[m].begin(), root->value[m].end(),compareInterval);
			root->key[m] = root->value[m][DEG-1];
			root->value[m+1][0] = root->value[m][DEG-1];
			root->value[m][DEG-1] = 100000;
			root->value[m+1][1] = root->value[m][DEG];
			root->value[m].pop_back();
			root->keySize = m+1;
		}
		else
		{
			root->value[m].push_back(k);
			sort(root->value[m].begin(), root->value[m].end(),compareInterval);
			root->key[m] = root->value[m][DEG-1];
			root->value[m].pop_back();
			bool recursive = true;
			for(int i = 0; i<DEG; i++)
			{
				if(root->value[m+1][i] == 100000)
				{
					recursive = false;
					root->value[m+1][i] = root->key[m];
					sort(root->value[m+1].begin(), root->value[m+1].end(),compareInterval);
					break;
				}
			}

		}
	}
	else
	{
		Node* Temp1 = new Node();
		Node* Temp2 = new Node();
		if(k>root->key[DEG-1])
		{
			root->value[DEG].push_back(k);
			sort(root->value[DEG].begin(), root->value[DEG].end(),compareInterval);
			Temp1->key[0] = root->value[DEG][0];
			Temp2->key[0] = root->value[DEG][DEG-1];
			Temp2->value[0][0] = root->value[DEG][0];
			Temp2->value[0][1] = root->value[DEG][1];
			Temp2->value[1][0] = root->value[DEG][DEG-1];
			Temp2->value[1][1] = root->value[DEG][DEG];
			root->value[DEG].pop_back();
			root->key[DEG-1] = 900000;
			for (int i = 0; i < DEG; ++i)
			{
				root->value[DEG][i] = 100000;
			}
			Temp1->isLeaf = false;
			Temp2->isLeaf = true;
			root->isLeaf = true;
			Temp1->children[0] = root;
			Temp1->children[1] = Temp2;
			root = Temp1;
		}
	}
	
}

void BPlusTree::insert(int k){
	if(root == NULL)
	{
		Node *Temp = new Node();
		Temp->value[0][0] = k;
		root = Temp;
		root->isLeaf = true;
	}
	else
	{
		if(root->isLeaf)
		{
			int keyLvl = DEG;
			for (int i = 0; i < DEG; ++i)
			{
				if(k < root->key[i])
				{
					keyLvl = i;
					break;
				}
			}

			filler(keyLvl, k);
		}
	  
	}
} 

bool BPlusTree::search(int k){
	bool isAlive = false;
	if(root->isLeaf)
	{
		for(int i = 0; i < DEG; i++)
		{
			for (int j = 0; j < DEG; ++j)
			{
				if(root->value[i][j]==k){
					isAlive = true;
				}
			}

		}
	}
	else
	{
		for(int i = 0; i < DEG+1; i++)
		{
			traverse(root->children[i]);
		}
	}

	return isAlive;
} 

void BPlusTree::remove(int k){
	
	if(root->isLeaf)
	{
		for(int i = 0; i < DEG; i++)
		{
			for (int j = 0; j < DEG; ++j)
			{
				if(root->value[i][j] == k){
					root->value[i][j]=100000;
					sort(root->value[i].begin(), root->value[i].end(),compareInterval);
				}
			}
		}
	}
	else
	{
		for(int i = 0; i < DEG+1; i++)
		{
			traverse(root->children[i]);
		}
	}
} 

#endif