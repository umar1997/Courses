#ifndef __STACK_CPP
#define __STACK_CPP
#include "stack.h"

template <class T>
Stack<T>::Stack()
{
    ListItem<T>* point=list.getHead();
    point=NULL;

}

template <class T>
Stack<T>::Stack(const Stack<T>& otherStack)
{
    list.insertAtHead(NULL);
    LinkedList<T> l1= otherStack.list;
    ListItem<T>* t1=list.getHead();
    ListItem<T>* t2= l1.getHead();
    //cout<<t2->value<<endl;
    t1->value=t2->value;

    //t1= new ListItem<T>(t2->value);
    //cout<<t1->value<<ends<<t1->next<<ends<<t1->prev<<endl;
    if(t2==NULL)
    {
        ListItem<T>*temp=list.getHead();
        temp=NULL;
    }
    else
    {
        while(t2 != NULL)
        {
            t1->value=t2->value;
            if(t2->next==NULL)
            {
                break;
            }
            else
            {
                t2=t2->next;
                ListItem<T>* agla =new ListItem<T>(t2->value);
                agla->prev=t1;
                t1->next=agla;
                t1=t1->next;
            }
        }
    }
    t1->next=NULL;



}

template <class T>
Stack<T>::~Stack()
{
}

template <class T>
void Stack<T>::push(T item)
{
    list.insertAtTail(item);
    //cout<<"PUSH"<<endl;
}

template <class T>
T Stack<T>::top()
{
    if(list.getTail()!=NULL)
        return list.getTail()->value;
    //cout<<"TOP"<<endl;
}

template <class T>
T Stack<T>::pop()
{
    //cout<<"POP"<<endl;
    if(list.length()!=0)
    {
        T v=list.getTail()->value;
        list.deleteTail();
        return v;
    }

}

template <class T>
int Stack<T>::length()
{
    //cout<<"LENGTH"<<endl;
    return list.length();
}

template <class T>
bool Stack<T>::isEmpty()
{
    //cout<<"ISEMPTY"<<endl;
    return (list.length()==0);

}

#endif
