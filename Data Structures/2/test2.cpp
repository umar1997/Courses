#include "bst.h"
#include <vector>

using namespace std;


void test_insert(BST<int>* tree);
int trav(node<int> *P,int i);
vector<int> find_delete(int k,vector<int> v);
void test_delete(BST<int>* tree);
void test_search(BST<int>* tree);
void test_replace(BST<int>* tree);
void test_height(BST<int>* tree);
vector<int> test_vec;
vector<int> ref_vec;
int main()
{
	BST<int>* tree=new BST<int>();
//------------------------
	tree->insert("a",34);
	tree->insert("b",7);
	tree->insert("c",53);
	tree->insert("d",12);
	tree->insert("e",68);
	tree->insert("f",90);
	tree->insert("g",24);
	tree->insert("h",71);
	tree->insert("i",13);
	tree->insert("j",3);
	tree->insert("k",1);
	tree->insert("l",61);
	tree->insert("m",18);
	tree->insert("n",30);
	tree->insert("o",50);
	tree->insert("p",4);
	tree->insert("q",11);
	tree->insert("r",52);
	tree->insert("r",54);
	tree->insert("r",56);
	tree->insert("r",55);
	tree->insert("r",80);
//--
//--
//---------------------------------------------------------
	ref_vec.push_back(1);
	ref_vec.push_back(3);
	ref_vec.push_back(4);
	ref_vec.push_back(7);
	ref_vec.push_back(11);
	ref_vec.push_back(12);
	ref_vec.push_back(13);
	ref_vec.push_back(18);
	ref_vec.push_back(24);
	ref_vec.push_back(30);
	ref_vec.push_back(34);
	ref_vec.push_back(50);
	ref_vec.push_back(52);
	ref_vec.push_back(53);
	ref_vec.push_back(54);
	ref_vec.push_back(55);
	ref_vec.push_back(56);
	ref_vec.push_back(61);
	ref_vec.push_back(68);
	ref_vec.push_back(71);
	ref_vec.push_back(80);
	ref_vec.push_back(90);
//-----------------------------------------------------------

	cout<< endl<<endl<<"Testing Binary Search Tree"<<endl<<endl;
	test_insert(tree);
	test_search(tree);
	test_delete(tree);
	//test_replace(tree);
	test_height(tree);
	return 0;
}

void test_insert(BST<int>* tree)
{
	cout<<"Testing Insert function.."<<endl;
	test_vec.clear();
	int counter=0;
	int a=trav(tree->getRoot(),0);
	for (int i=0;i<test_vec.size();i++)
	{
		if (test_vec[i]==ref_vec[i])
		{
			counter++;
		}

	}
	cout<<"Total points:: "<<(counter/ref_vec.size())*10<<"/10"<<endl<<endl;
	return;

}
void test_delete(BST<int>* tree)
{
	cout<<"Testing delete function.."<<endl;
	test_vec.clear();
	tree->delete_node(90);
	tree->delete_node(18);
	tree->delete_node(50);
	tree->delete_node(24);
	tree->delete_node(68);
	tree->delete_node(54);
	ref_vec=find_delete(90,ref_vec);
	ref_vec=find_delete(18,ref_vec);
	ref_vec=find_delete(50,ref_vec);
	ref_vec=find_delete(24,ref_vec);
	ref_vec=find_delete(68,ref_vec);
	ref_vec=find_delete(54,ref_vec);
	//for (int j=0;j<ref_vec.size();j++)
		//cout<<ref_vec[j]<<" ref"<<endl;

	int counter=0;
	int a=trav(tree->getRoot(),0);
	//tree->Traverse(tree->getroot());
	for (int i=0;i<test_vec.size();i++)
	{
		if (test_vec[i]==ref_vec[i])
		{
			counter++;
		}

	}

	cout<<"Total points:: "<<(counter/ref_vec.size())*10<<"/10"<<endl<<endl;
	return;


}
void test_search(BST<int>* tree)
{
	cout<< "Testing Search Function.."<<endl;
	vector<int> ref_search;
	int counter=0;
	test_vec.clear();
	test_vec.push_back(tree->search(13)->key);
	test_vec.push_back(tree->search(11)->key);
	test_vec.push_back(tree->search(52)->key);
	test_vec.push_back(tree->search(90)->key);
	test_vec.push_back(tree->search(24)->key);
	ref_search.push_back(13);
	ref_search.push_back(11);
	ref_search.push_back(52);
	ref_search.push_back(90);
	ref_search.push_back(24);
	for (int i=0;i<test_vec.size();i++)
	{
		if (test_vec[i]==ref_search[i])
		{
			counter++;
		}

	}
	cout<<"Total points:: "<<(counter/ref_search.size())*10<<"/10"<<endl<<endl;
	return;
}
// void test_replace(BST<int>* tree)
// {
// 		cout<<"Testing Replace Function.."<<endl;
// 		vector<int> ref_replace;
// 		int counter=0;
// 		for (int i=0;i<test_vec.size();i++)
// 		{
// 			ref_replace.push_back(ref_vec[i]);
// 		}
// 		tree->replace(7,77);
// 		tree->replace(71,17);
// 		test_vec.clear();
// 		trav(tree->getRoot(),0);
// 		ref_replace=find_delete(7,ref_replace);
// 		ref_replace=find_delete(71,ref_replace);
// 		ref_replace.insert(ref_replace.begin()+6,17);
// 		ref_replace.insert(ref_replace.begin()+14,77);
// 		for (int i=0;i<test_vec.size();i++)
// 		{
// 			if (test_vec[i]==ref_replace[i])
// 			{
// 				counter++;
// 			}

// 		}
// 		cout<<"Total points:: "<<(counter/ref_replace.size())*5<<"/5"<<endl<<endl;
// 		return;

// }
void test_height(BST<int>* tree)
{
	cout<<"Testing Height Function.."<<endl;
	test_vec.clear();
	int counter=0;
	int h=tree->height(tree->getRoot());
	//cout <<"HEIGHT IS :" <<h << endl;
	if (h==6)
		counter=1;
	else
		counter=0;
	cout<< "Total Points:: "<<counter*5<<"/5"<<endl;
}
int trav(node<int> *P,int i)
{
	if(P->left)
		i=trav(P->left,i);
	test_vec.push_back(P->key);
	i++;
	if(P->right)
		i=trav(P->right,i);
	return i;

}
vector<int> find_delete(int k,vector<int> v)
{
	for (int i=0;i<v.size();i++)
	{
		if (v.at(i)==k)
		{
			v.erase(v.begin()+i);
			return v;
		}
	}
}
