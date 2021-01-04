#ifndef __QUEUE_CPP
#define __QUEUE_CPP
#include "queue.h"

template <class T>
Queue<T>::Queue()
{
    ListItem<T>* point=list.getHead();
    point=NULL;
}

template <class T>
Queue<T>::Queue(const Queue<T>& otherQueue)
{   list.insertAtHead(NULL);
    LinkedList<T> l1= otherQueue.list;
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
Queue<T>::~Queue()
{

}

template <class T>
void Queue<T>::enqueue(T item)
{
    list.insertAtTail(item);
}

template <class T>
T Queue<T>::front()
{
    if (list.getHead()!=NULL)
        return list.getHead()->value;

}

template <class T>
T Queue<T>::dequeue()
{
    if(list.length()!=0)
    {
        T x=list.getHead()->value;
        list.deleteHead();
        return x;
    }
}

template <class T>
int Queue<T>::length()
{
	return list.length();
}

template <class T>
bool Queue<T>::isEmpty()
{
    return (list.length()==0);
}

template <class T>
void Queue<T>::print()
{
    list.print_list();
}


#endif
