#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include "LinkedList.h"
#include <iostream>

using namespace std;

template <class T>
LinkedList<T>::LinkedList()
{
	head=NULL;
}

template <class T>
LinkedList<T>::LinkedList(const LinkedList<T>& otherLinkedList)
{
    head= new ListItem<T>(otherLinkedList.head->value);
    ListItem<T>* t1=head;
    ListItem<T>* t2= otherLinkedList.head;
    if(t2==NULL)
    {
        head=NULL;
    }
    else
    {
        while(t2 != NULL)
        {
            t1->value=t2->value;
            if(t2->next==NULL)
                break;
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

    /*if(otherLinkedList.head==NULL)
        head=NULL;
    else
    {
        ListItem<T>* t1;
        ListItem<T>* t2;
        t2=otherLinkedList.head;

        head= new ListItem<T>(t2->value);

        t1=head;
        t1->value=t2->value;
        t1->next=NULL;
        t1->prev=NULL;
        while(t2!=NULL)
        {
            ListItem<T> *n = new ListItem<T>(t2->value);
            //n->value = t2 -> value;
            n->next = NULL;
            n->prev = t1;
            t1->next = n;
            t2 = t2->next;
            t1 = t1->next;
        }
    }*/

}

template <class T>
LinkedList<T>::~LinkedList()
{
	ListItem<T>* temp;
    while (head!=NULL)
    {
      	temp= head->next;
        delete head;
        head=temp;
    }
}

template <class T>
void LinkedList<T>::insertAtHead(T item)
{

	ListItem<T> *temp= new ListItem<T>(item);
	//temp->value= item;
	temp->prev= NULL;
	temp->next= head;
	if (head!=NULL)
		head->prev=temp;
	head=temp;
}

template <class T>
void LinkedList<T>::insertAtTail(T item)
{
	if (head==NULL)
		insertAtHead(item);
	else
	{
		ListItem<T>* traverse=head;
		while(traverse->next !=NULL)
			traverse=traverse->next;

		ListItem<T> *temp= new ListItem<T>(item);
		//temp->value= item;
		temp->prev= traverse;
		temp->next=NULL;
		traverse->next=temp;
	}
}

template <class T>
void LinkedList<T>::insertAfter(T toInsert, T afterWhat)
{
	bool check=false;
	if (head !=NULL)
    {
        ListItem<T>* traverse = head;

        if (traverse->value==afterWhat)
        {
            check=true;
        }
        else
        {
            while(traverse !=NULL)
            {
                if (traverse->value == afterWhat)
                {
                    check=true;
                    break;
                }
                else
                    traverse=traverse->next;
            }
        }
        if (check==true)
        {
            if (traverse->next==NULL)
                insertAtTail(toInsert);
            else
            {
                ListItem<T> *temp= new ListItem<T>(toInsert);
                temp->prev= traverse;
                temp->next= traverse->next;
                (traverse->next)->prev= temp;
                traverse->next= temp;
            }
        }
    }


}

template <class T>
void LinkedList<T>::insertSorted(T item)
{
    if (head==NULL || item<head->value)
        insertAtHead(item);
    else
    {
        ListItem<T> *n= head;
        bool check=false;
        while(n !=NULL)
        {
            if (n->value>item)
            {
                check=true;
                break;
            }
            else
                n=n->next;
        }
        if (check==false)
            insertAtTail(item);
        else
        {
            ListItem<T> *temp= new ListItem<T>(item);
            temp->next=n;
            temp->prev=n->prev;
            n->prev->next= temp;
            n->prev=temp;
        }

    }

}

template <class T>
ListItem<T>* LinkedList<T>::getHead()
{
    if (head==NULL)
        return NULL;
    else
        return this->head;
}

template <class T>
ListItem<T>* LinkedList<T>::getTail()
{

	ListItem<T>* traverse=head;
	while (traverse->next!=NULL)
		traverse=traverse->next;
	return traverse;
}

template <class T>
ListItem<T> *LinkedList<T>::searchFor(T item)
{

	ListItem<T>* traverse=head;
	while (traverse!=NULL)
	{
	    if (traverse->value == item)
			return traverse;
		else
			traverse=traverse->next;
	}
}

template <class T>
void LinkedList<T>::deleteElement(T item)
{
    if(head==NULL){}
    else
    {
        bool check=false;
        ListItem<T>* temp= head;
        while(temp!=NULL)
        {
            if (temp->value==item)
            {
                //cout<<"found1"<<endl;
                check=true;
                break;
            }
            else
                temp=temp->next;
        }

        if (check==true)
        {
            if(temp==head)
                deleteHead();
            else if(temp->next==NULL)
                deleteTail();
            else{
            //cout<<"found"<<endl;
            ListItem<T>* p= temp->prev;
            ListItem<T>* n= temp->next;

            p->next=n;
            n->prev=p;
            delete temp;
            }
        }

    }

}

template <class T>
void LinkedList<T>::deleteHead()
{
    if(head==NULL){}
    else if(head->next==NULL)
    {
        delete head;
        head=NULL;
    }
    else
    {
        ListItem<T> *temp= head->next;
        delete head;
        head=temp;
        head->prev=NULL;
    }
}

template <class T>
void LinkedList<T>::deleteTail()
{
    if (head==NULL)
        cout<<"Nothing to Delete."<<endl;
    else
    {
        if(head->next==NULL){
            deleteHead();
        }
    	else
    	{
            ListItem<T>* traverse=head;
            while (traverse->next!=NULL)
                traverse=traverse->next;

            (traverse->prev)->next=NULL;
            delete traverse;
        }
    }

}

template <class T>
int LinkedList<T>::length()
{
	int counter=0;
	ListItem<T>* traverse=head;
	while (traverse->next!=NULL)
	{
		counter++;
		traverse=traverse->next;
	}
    counter++;
    return counter;
}

template <class T>
void LinkedList<T>::reverse()
{
	if (head!=NULL)
    {
    	ListItem<T>* t2= getTail();
		ListItem<T>* temp = new ListItem<T>(0);

		int len= this->length();
		head=t2;
		for (int i=0;i<len;i++)
		{
		    temp->next=t2->next;
			t2->next=t2->prev;
			t2->prev= temp->next;
			t2=t2->next;
		}

    }

}

template <class T>
void LinkedList<T>::parityArrangement()
{
    if (head==NULL || head->next==NULL){}
    else{

    int oddlen;
    int evenlen;
    if (length()%2==0)
    {
        oddlen=length()/2;
        evenlen=length()/2;
    }
    else
    {
        oddlen=(length()/2)+1;
        evenlen=(length()/2);
    }
    T odd[oddlen];
    T even[evenlen];
    int counter=0;
    int counter2=0;
    int counter3=0;

    ListItem<T>*temp = head;
    while(temp!=NULL)
    {
        if(counter2%2==1)
        {
            odd[counter]=temp->value;
            counter++;

        }
        else
        {
            even[counter3]=temp->value;
            counter3++;
        }
        temp=temp->next;
        counter2++;
    }

    ListItem<T> *traverse=head;
    int x=0;
    while(x<oddlen)
    {
        traverse->value=even[x];
        x++;
        traverse=traverse->next;
    }
    int r=0;
    while(x<length())
    {
        traverse->value=odd[r];
        r++;
        x++;
        traverse=traverse->next;
    }
    }
}

template <class T>
void LinkedList<T>::print_list()
{
    if (head==NULL)
        cout<<"EMPTY AF"<<endl;
    else
    {
        ListItem<T>* here=head;
        while (here!=NULL)
        {
            cout << here->value <<ends<<" next: "<<here->next<<ends<<" prev: "<<here->prev<< endl;
            here = here->next;
        }
        //cout << here->value <<ends<<" next: "<<here->next<<ends<<" prev: "<<here->prev<< endl;

    }
}

template <class T>
int LinkedList<T>::isPalindrome()
{
    if(head==NULL)
    {
        return 0;
    }
    else if (head->next==NULL)
    {
        return 0;
    }
    else
    {
    bool check=true;
    ListItem<T>*start=head;
    ListItem<T>*finish=getTail();

    while(start!=NULL)
    {
        if(start->value!=finish->value)
        {
            check=false;
            break;
        }
        else
        {
            start=start->next;
            finish=finish->prev;
        }
    }
    if(check==true)
        return 1;
    else
        return 0;
    }
}

/*
int main()
{
    LinkedList<int> l;
    l.insertAtTail(1);
    l.insertAtTail(2);
    l.insertAtTail(3);
    l.insertAtTail(4);
    l.insertAtTail(5);

    l.insertAtTail(4);
    l.insertAtTail(3);
    l.insertAtTail(2);
    l.insertAtTail(1);
    LinkedList<int> a(l);
    a.print_list();
    cout<<endl;
    cout<<"pal "<<a.isPalindrome();
    //l.insertAfter(2,1);
    //l.insertAfter(3,2);
    //l.print_list();


    return 0;
}*/
#endif
