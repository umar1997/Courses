#include <iostream>
#include "bst.h"
#include <vector>


using namespace std;

template <class T>
void store(vector<T>& v, node<T>* p)
{
    if (p==NULL)
        return;
    store(v, p->left);
    v.push_back(p->key);
    //cout<<"pushed "<<p->key<<endl;
    store(v,p->right);
}

template <class T>
bool notin(T arr[],T x, int s)
{
    cout<<"size is "<<s<<endl;
    for(int i=0;i<s;i++)
    {
        if (x==arr[i])
            return false;
    }
    return true;

}


template <class T>
vector<T> merge1(vector<T> x, vector<T> y)
{
    int s1=x.size();
    int s2=y.size();
    int s3=s1+s2;
    vector<T> z;
    int x1=0;
    int y1=0;
    int z1=0;

    while(x1<s1 && y1<s2)
        {
            if(x[x1]<y[y1]) //&& notin(z,x[x1],z1)==true)
            {
                z.push_back(x[x1]);
                z1++;
                x1++;
            }
            else if(x[x1]>=y[y1])//&& notin(z,y[y1],z1)==true)
            {
                z.push_back(y[y1]);
                z1++;
                if(x[x1]==y[y1])
                    x1++;
                y1++;
            }

        }

    while(x1<s1)
    {
        z.push_back(x[x1]);
        x1++;
        z1++;
    }

    while(y1<s2)
    {
        z.push_back(y[y1]);
        y1++;
        z1++;
    }

//    cout<<endl<<endl<<endl;
//    for (int i=0;i<z.size();i++)
//        cout<<z[i]<<ends;
    return z;


}

template <class T>
node<T>* maketree(vector<T> v,int start, int size1,node<T>* p)
{
    if (start> size1 || v.size()==0)
      return NULL;

    int mid;
    mid = (start+size1)/2;
    int leftcase= mid-1;
    int rightcase= mid+1;

    p = new node<T>(v[mid]," ");
    p->right = maketree(v, rightcase, size1, p->right);
    p->left =  maketree(v, start, leftcase, p->left);

    //cout<<root->key<<endl;
    return p;

}



template <class T>
BST<T>* bst_Union(BST<T>* tree1,BST<T>* tree2){

    vector<T> x;
    store(x, tree1->getRoot());
//    cout<<"SET 1"<<endl;
//    for(int i=0;i<x.size();i++)
//        cout<<x[i]<<ends;
//    cout<<endl<<endl;

    vector<T> y;
    store(y, tree2->getRoot());
//    cout<<"SET 2"<<endl;
//    for(int i=0;i<y.size();i++)
//        cout<<y[i]<<ends;
//    cout<<endl<<endl;

    vector<T> msorted=merge1(x,y);
//    cout<<"MERGED SET"<<endl;
//    for(int i=0;i<msorted.size();i++)
//        cout<<msorted[i]<<ends;

    node<T>* ret = maketree(msorted, 0, msorted.size()-1,ret);
    BST<T> * n= new BST<T>;
    n->changehead(ret);

    return n;

}



//int main()
//{
//    BST<int>* B = new BST<int>();
//	BST<int>* A = new BST<int>();
//
//    B->insert("abc",5);
//    B->insert("abc",4);
//    B->insert("abc",8);
//    B->insert("abc",6);
//    B->insert("abc",7);
//
//
//    A->insert("abc",5);
//    A->insert("abc",3);
//    A->insert("abc",7);
//    A->insert("abc",6);
//    A->insert("abc",9);
//
//    BST<int>* mergedTree =bst_Union(A ,B);
//
//
//}
