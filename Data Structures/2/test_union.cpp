#include <iostream>
#include "bst.cpp"
#include "union.cpp"
#include <set>
#include <stdlib.h>
#include <time.h>
#include <assert.h>
#include <vector>

using namespace std;

template<class T>
void insertIntoSet(node<T>* node,std::set<T>& testSet){

	if (node==NULL)
		return;

	testSet.insert(node->key);

	insertIntoSet(node->left,testSet);
	insertIntoSet(node->right,testSet);

}

template<class T>
bool test_balance(node<T>* root,BST<T>* tree){

    if (root==NULL)
    	return true;

    int heightL=tree->height(root->left);
    int heightR=tree->height(root->right);

    int heightDiff=max(heightL,heightR)-min(heightL,heightR);

    return (heightDiff<2) && test_balance(root->left,tree) && test_balance(root->right,tree);

}

template <class T>
int countNodes(node<T>* root){

	if (root==NULL)
		return 0;

	return 1+countNodes(root->left)+countNodes(root->right);


}

template<class T>
bool test_ordering(BST<T>* tree,vector<T> vec){


	assert(vec.size()==countNodes(tree->getRoot()));
    
    T* testArray = new T[vec.size()]; 
 

    std::set<int> testSet;
    std::set<int>::iterator it;
    insertIntoSet(tree->getRoot(),testSet);
    std::vector<int> vecTree;

    for (it=testSet.begin();it!=testSet.end();it++){
    	vecTree.push_back(*it);
    }



    for (int i=0;i<vec.size();i++){

       if (vec[i]!=vecTree[i])
       	  return false;

    }


    return true;


}


int main(){

	cout<<"Starting tests..."<<endl;

	srand(time(NULL));

	BST<int>* tree1 = new BST<int>();
	BST<int>* tree2 = new BST<int>();


	std::set<int> testSet;
	std::set<int>::iterator it;
	std::vector<int> vec;
    


	for (int i=0;i<40000;i++){
		int n = rand()%30000;
		testSet.insert(n);
		tree1->insert(" ",n);
	}

	for (int i=0;i<40000;i++){
		int m = rand()%30000;
		testSet.insert(m);
		tree2->insert(" ",m);
	}
	

	for (it=testSet.begin();it!=testSet.end();it++){
		vec.push_back(*it);
	}

	

	BST<int>* mergedTree = bst_Union(tree1,tree2);

    
    int b_points=0;
    int o_points=0;

    cout<<"Testing tree balance..."<<endl;

	if (test_balance(mergedTree->getRoot(),mergedTree)){
		cout<<"Balance test passed - ";
		b_points+=5;
	}
	else{
		cout<<"Balance test failed - ";
	}

	cout<<b_points<<"/5"<<endl;


	cout<<"Testing tree ordering..."<<endl;

	if (test_ordering(mergedTree,vec)){
		cout<<"Ordering test passed - ";
		o_points+=5;
	}
	else{
		cout<<"Ordering test failed - ";
	}
	cout<<o_points<<"/5"<<endl;


	cout<<"Total Points: "<<b_points+o_points<<"/10"<<endl;

}