/*
	Recurrence Relation: 2T(n/2) + O(1)
	Time Complexity: O(log(n)) because we have log(n) levels and perform b simple comparisons at each level in O(1)
	Space Complexity: O(n)

	we create a binary tree from the given array and then pass to my recursive func. The base case is when the node has two children but
	its children do not have any children. in that case return sum of child and parent for both children, and their paths. when the returns of left and right contain a
	total of 4 elements, we find the max 2 and send them forward the sum. after the final callback, we traverse paths of both max nodes and sum their elements.
*/


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;
#define COUNT 10
int index =1;
struct node
{
	int value;
	node* right;
	node* left;
	int Leaf1;
	int Leaf2;
	int Sum1;
	int Sum2;
	int Anc_Sum;
	vector<int> v1;
	vector<int> v2;

};


void print2DUtil(node *root, int space)
{
    if (root == NULL)
        return;
    space += COUNT;
    print2DUtil(root->right, space);
    cout << endl;
    for (int i = COUNT; i < space; i++)
        cout << " ";
    cout << root->value;
    print2DUtil(root->left, space);
}

void print2D(node *root)
{
   print2DUtil(root, 0);
}

node* makeTree(int arr[], node* root, int i, int n)
{
	if(i<n)
	{
		node* temp = new node;
		temp->value = arr[i];
		temp->Anc_Sum = 0;
		temp->Sum1 = 0;
		temp->Sum2 = 0;
		temp->left = NULL;
		temp->right = NULL;
		root = temp;

		root->left = makeTree(arr, root->left, 2*i+1, n);
		root->right = makeTree(arr, root->right, 2*i+2, n);
	}
	return root;
}

bool sortFunc(int i, int j)
{
	return (i<j);
}
void compare(node* rootP, node* rootL, node* rootR)
{
	vector<int> hold;
	hold.push_back(rootL->Sum1);
	hold.push_back(rootL->Sum2);
	hold.push_back(rootR->Sum1);
	hold.push_back(rootR->Sum2);
	sort(hold.begin(),hold.end(),sortFunc);
	rootP->Sum1 = hold[hold.size()-1] + rootP->value;
	rootP->Sum2 = hold[hold.size()-2] + rootP->value;

	if(hold[hold.size()-1] == rootL->Sum1)
		{
			rootP->Leaf1 = rootL->Leaf1;
			for (int i = 0; i < rootL->v1.size(); ++i)
			{
				rootP->v1.push_back(rootL->v1[i]);
			}
			rootP->v1.push_back(rootP->value);
		}
	else if(hold[hold.size()-1] == rootL->Sum2)
		{
			rootP->Leaf1 = rootL->Leaf2;
			for (int i = 0; i < rootL->v2.size(); ++i)
			{
				rootP->v1.push_back(rootL->v2[i]);
			}
			rootP->v1.push_back(rootP->value);
		}
	else if(hold[hold.size()-1] == rootR->Sum1)
		{
			rootP->Leaf1 = rootR->Leaf1;
			for (int i = 0; i < rootR->v1.size(); ++i)
			{
				rootP->v1.push_back(rootR->v1[i]);
			}
			rootP->v1.push_back(rootP->value);
		}
	else if(hold[hold.size()-1] == rootR->Sum2)
		{
			rootP->Leaf1 = rootR->Leaf2;
			for (int i = 0; i < rootR->v2.size(); ++i)
			{
				rootP->v1.push_back(rootR->v2[i]);
			}
			rootP->v1.push_back(rootP->value);
		}
/////////////////////////////////////////////
	if(hold[hold.size()-2] == rootL->Sum1)
		{
			rootP->Leaf2 = rootL->Leaf1;
			for (int i = 0; i < rootL->v1.size(); ++i)
			{
				rootP->v2.push_back(rootL->v1[i]);
			}
			rootP->v2.push_back(rootP->value);
		}
	else if(hold[hold.size()-2] == rootL->Sum2)
		{
			rootP->Leaf2 = rootL->Leaf2;
			for (int i = 0; i < rootL->v2.size(); ++i)
			{
				rootP->v2.push_back(rootL->v2[i]);
			}
			rootP->v2.push_back(rootP->value);
		}
	else if(hold[hold.size()-2] == rootR->Sum1)
		{
			rootP->Leaf2 = rootR->Leaf1;
			for (int i = 0; i < rootR->v1.size(); ++i)
			{
				rootP->v2.push_back(rootR->v1[i]);
			}
			rootP->v2.push_back(rootP->value);
		}
	else if(hold[hold.size()-2] == rootR->Sum2)
		{
			rootP->Leaf2 = rootR->Leaf2;
			for (int i = 0; i < rootR->v2.size(); ++i)
			{
				rootP->v2.push_back(rootR->v2[i]);
			}
			rootP->v2.push_back(rootP->value);
		}


    if(hold[hold.size()-1] == rootL->Sum1 && hold[hold.size()-2] == rootL->Sum2 || hold[hold.size()-1] == rootL->Sum2 && hold[hold.size()-2] == rootL->Sum1)
        rootP->Anc_Sum = rootL->Anc_Sum + rootP->value;
    else if(hold[hold.size()-1] == rootR->Sum1 && hold[hold.size()-2] == rootR->Sum2 || hold[hold.size()-1] == rootR->Sum2 && hold[hold.size()-2] == rootR->Sum1)
        rootP->Anc_Sum = rootR->Anc_Sum + rootP->value;
    else
       rootP->Anc_Sum =  hold[hold.size()-1] + hold[hold.size()-2] + rootP->value;

	hold.clear();




}
void getSum(node* root)//, int ancestorySum, int sum1, int sum2, int ind1, int ind2)
{
	if((root->left)->left == NULL && (root->right)->left == NULL && (root->left)->right == NULL && (root->right)->right == NULL)
	{
	    cout << endl;
		root->Leaf1 = index++;
		root->Leaf2 = index++;
		root->v1.push_back((root->left)->value);
		root->v1.push_back(root->value);
		root->v2.push_back((root->right)->value);
		root->v2.push_back(root->value);
		root->Anc_Sum = (root->left)->value + (root->right)->value + root->value;
		root->Sum1 = (root->left)->value + root->value;
		root->Sum2 = (root->right)->value + root->value;
		return;
	}
	else
	{
		getSum(root->left);//,ancestorySum,sum1,sum2,ind1,ind2);
		getSum(root->right);//,ancestorySum,sum1,sum2,ind1,ind2);
		compare(root,root->left, root->right);
	}
}

int main()
{

	int arr[] = {29, 6, 11, 15, 5, 10, 20, 1, 3, 4, 2, 15, 45, 10, 50};
	//int arr[] = {27,15,3,17,37,3,4};
	int n = sizeof(arr)/sizeof(arr[0]);
	node* root = makeTree(arr,root,0,n);
	print2D(root);
	getSum(root);

	/*cout << endl;
	cout << "Ancestory Sum: " << root->Anc_Sum << endl;
	cout << "Sum 1: " << root->Sum1 << endl;
	cout << "Sum 2: " << root->Sum2 << endl;
	cout << "Leaf 1: " << root->Leaf1 << endl;
	cout << "Leaf 2: " << root->Leaf2 << endl;
	cout << endl;*/
	cout << "xi = x" <<  root->Leaf1 << endl;
	cout << "xj = x" <<  root->Leaf2 << endl;
	cout << "Max Ancestory (x"<< root->Leaf1 << ", x" << root->Leaf2 << ") = " <<  root->Anc_Sum << endl;
	cout << "Sum values for (xi, xj): (" << root->Sum1 << ", " << root->Sum2  << ")" << endl;
	cout << "Values for xi and xj:\n";
	cout << "{";
	for(int i=0; i<root->v1.size();i++)
	{
		if(i==root->v1.size()-1)
			cout << root->v1[i] << "} ";
		else
			cout << root->v1[i] << ", "; 
	}
	cout << endl;
	cout << "{";
	for(int i=0;i<root->v2.size();i++)
	{
		if(i==root->v2.size()-1)
			cout << root->v2[i] << "} ";
		else
			cout << root->v2[i] << ", ";
	}
}
