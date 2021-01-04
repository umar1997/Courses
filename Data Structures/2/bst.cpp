#ifndef __BST_CPP
#define __BST_CPP
#include "bst.h"
#include <iostream>
#include <queue>
// HELPER FUNCTIONS HERE...
template <class T>
BST<T>::BST(){
	root = NULL;
}

template <class T>
BST<T>:: ~BST(){

    // your destructor code goes here
}

template <class T>
int BST<T> :: height (node<T>* p){
   // your find height code goes here
    if (p != NULL)
	{
		return p->height;
	}
	else
        return 0;
}

template <class T>
int BST<T> :: balanceFactor(node<T>* p){
    // you can use this to find balance factor.
    return (height(p->right)-height(p->left));
}

template <class T>
void BST<T> :: fixHeight(node<T>* p){

    if(p!=NULL)
    {
        p->height= 1+max(height(p->left),height(p->right));
    }
    else
        return;

}

// ROTATING HELPERS
template <class T>
node<T>* BST<T> :: rotateleft(node<T>* p){
    // Rotate left code goes here.
    if (p==NULL)
        return NULL;

    node<T>* next= p->right;
    p->right=next->left;
    next->left=p;

    if(p==root)
        root=next;

     ///update height
    fixHeight(next);
    return next;
}

template <class T>
node<T>* BST<T> :: rotateright(node<T>* p){
    // Rotate right code goes here

    if(p==NULL)
        return NULL;
    node<T>* next= p->left;
    p->left= next->right;
    next->right=p;


    if(p==root)
        root=next;

    ///update height
    fixHeight(next);
    return next;
}

template <class T>
node<T>* BST<T> :: balance(node<T>* p){


//    int bf= balanceFactor(p);
//    cout<<"bf is "<<bf<<endl;
//    if(bf<-1)//left
//    {
//        cout<<"in"<<endl;
//        bf=balanceFactor(p->left);
//        if(bf<-1)//left left
//        {   cout<<"right rotating "<<p->key<<endl;
//            rotateright(p);
//        }
//        else if(bf>1)//left right
//        {
//            rotateleft(p->left);
//            rotateright(p);
//        }
//    }
////    else if(bf>1)//right
////    {
////        bf=balanceFactor(p->right);
////        if(bf<-1)//right left
////        {
////            rotateright(p->right);
////            rotateleft(p);
////        }
////        else if (bf>1)//right right;
////        {
////            rotateleft(p);
////        }
////
////    }
////
//    node<T>*parent=NULL;
//    parent= sparent(getRoot(),p->key);
//    if (parent != NULL)
//	{
//	    cout<<p->key<<" my parent is "<<parent->key<<endl;
//		balance(parent);
//	}
//	else
//        cout<<"no parent of "<<p->key <<endl;

    fixHeight(p);
//    cout<<"height of "<<p->key<< " is "<<p->height<<endl;
//    cout<<"insertion end"<<endl;
    return p;
    // Balancing code goes here. You might need to find balance factor and call appropriate rotations.
}
// CLASS FUNCTIONS HERE
template <class T>
void BST<T> :: insert(string value,T k){

    root = insertHelper(value,k,root);
}
// insertion helpe  r
template <class T>
node<T>* BST<T> :: insertHelper(string value,T k, node<T> *p) { // note we need a helper because we need recursive calls
    if (p==NULL)
    {


        p=new node<T>(k, value);
        //return balance(p); ///
        return (p);
    }
    else
    {
        if (k<p->key){
            p->left= insertHelper(value, k, p->left);
        }
        else if (k>p->key){
            p->right= insertHelper(value, k, p->right);
        }
        else
            //return balance(p); ///
            return (p);
    }
    ///
    return balance(p);
}


template<class T>
node<T>* BST<T> :: search(T key){
    node<T>*temp=root;
    while(temp!=NULL)
    {
        if(key == temp->key)
            return temp;
        else if (key < temp->key)
            temp=temp->left;
        else
            temp= temp->right;
    }

    return NULL;
}

template<class T>
node<T>* BST<T> :: sparent(node<T>* p, T key){

//    node<T>*temp=root;
//    //cout<<"A"<<endl;
//    while(temp!=NULL)
//    {   //cout<<getRoot()->key<<endl;
//        //cout<<temp->key<<": "<<temp->right->key;//<<ends <<temp->left->key<<endl;
//        if(temp->right!=NULL)
//        {
//            if(key==temp->right->key)
//                return temp;
//        }
//        if (temp->left!=NULL)
//        {
//            if (key==temp->left->key)
//                return temp;
//        }
////        if(key == temp->right->key || key== temp->left->key)
////            return temp;
//        if (key < temp->key)
//            temp=temp->left;
//        else
//            temp= temp->right;
//    }
//
//    return NULL;
}



// DELETE HELPER FUNCTIONS
template<class T>
node<T>* BST<T> :: findmin(node<T> *p){
    // This function finds the min node of the tree.
    if (p==NULL)
        return NULL;
    if(p->left==NULL)
        return p;
    findmin(p->left);

}

template<class T>
node<T>* BST<T>::removemin(node<T>* p) {
    //if (p->left==NULL && p->right==NULL)

    if (p->left==NULL)
        return p->right;
    else
        p->left= removemin(p->left);
    //return p;
    return balance(p);
    // This function recursively finds the min node and deletes it.
}

template<class T>
void BST<T>::delete_node(T k){
    root = remove(root, k);
}

template<class T>
node<T>*  BST<T>::remove(node<T>* p, T k) // k key deletion from p tree
{
    if(p==NULL)
        return NULL;
    else if (k<p->key)
        p->left= remove(p->left, k);
    else if (k>p->key)
        p->right= remove (p->right, k);
    else if (k== p->key)
    {
//        if(p->right==NULL)
//            return p->left;
//        else if (p->left==NULL)
//            return p->right;
//        else
//        {
//            node<T>* temp= p;
//            p=findmin(temp->right);
//            p->right= removemin(temp->right);
//            p->left= temp->left;
//
//        }
            if (p->left==NULL && p->right==NULL)///No child
            {
                node<T> *nc;
                nc=p->right;
                delete p;
                return nc;
            }
            else if (p->left ==NULL)///1 child: Right
            {
                node<T> *r;
                r=p->right;
                delete p;
                return r;
            }
            else if (p->right ==NULL)///1 child: Left
            {
                node<T> *l;
                l= p->left;
                delete p;
                return l;
            }
            else///2 Children
            {
                T k=findmin(p->right)->key;
                string val = findmin(p->right)->value;
                p->key=k;
                p->value=val;

                p->right= remove(p->right, k);
                //removemin(p->right);

                return p;
            }
        }

    return balance(p);
    // This function uses findmin and deletemin to delete arbitrary node in the tree.
}
template<class T>
node<T>* BST<T>::getRoot(){
    return root;
}

template<class T>
void BST<T>::print(node<T>* p){

    if(p==NULL)
        return;
    print(p->left);
    cout<<p->key<<ends;
    print(p->right);

}

template<class T>
void BST<T>::changehead(node<T>*p)
{
    root=p;
}
/*int main()
{

//    BST<int> tree;
//    tree.insert("a",34);
//	tree.insert("b",7);
//	tree.insert("c",53);
//	tree.insert("d",12);
//	tree.insert("e",68);
//	tree.insert("f",90);
//	tree.insert("g",24);
//	tree.insert("h",71);
//	tree.insert("i",13);
//	tree.insert("j",3);
//	tree.insert("k",1);
//	tree.insert("l",61);
//	tree.insert("m",18);
//	tree.insert("n",30);
//	tree.insert("o",50);
//	tree.insert("p",4);
//	tree.insert("q",11);
//	tree.insert("r",52);
//	tree.insert("r",54);
//	tree.insert("r",56);
//	tree.insert("r",55);
//	tree.insert("r",80);
//  tree.print(tree.getRoot());
//    cout<<endl;
//    /*
//    cout<<endl<<"Min: "<<tree.findmin(tree.getRoot())->key<<endl;
//
//    tree.removemin(tree.getRoot());
//    tree.print(tree.getRoot());
//    cout<<endl;
//
//    tree.removemin(tree.getRoot());
//    tree.print(tree.getRoot());
//    cout<<endl;
//
//    tree.delete_node(50);
//
//    tree.print(tree.getRoot());
//    cout<<endl;
    int values[25] = {55,43,26,82,93,04,39,95,50,6,62,17,21,49,77,5,32,60,88,16,44,72,80,8,36};

    BST<int> B;
    B.insert("abc",55);
    B.insert("abc",43);
    //B.insert("abc",26);
//    B.insert("abc",9);
//    B.insert("abc",15);
//    B.insert("abc",14);
//    B.insert("abc",16);
//    cout<<endl;
//    cout<<endl;
//    cout<<endl;
//    //cout<<B.getRoot()->key<<endl;
//    //cout<<B.balanceFactor(B.getRoot())<<endl;
////    B.rotateright(B.getRoot());
//    //cout<<B.getRoot()->right->key;
    B.print2(B.getRoot(),0);cout<<endl;
//    //cout<<B.getRoot()->right->key;

    //cout<<B.sparent(B.getRoot(),12)->key<<endl;

}*/
#endif
