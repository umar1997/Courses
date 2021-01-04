#ifndef __LIST_CPP
#define __LIST_CPP

#include <cstdlib>
#include "list.h"
#include <iostream>
using namespace std;

template <class T>
List<T>::List()
{
	head=NULL;
}

template <class T>
List<T>::List(const List<T>& otherList)
{
	head = NULL;
	ListItem<T> *temp;
	temp=otherList.head;
	while (temp != NULL)
	{
		insertAtTail(temp->value);
		temp = temp->next;
	}
	
}

template <class T>
List<T>::~List()
{
/*	ListItem<T>* temp;
	while( head != NULL )
	{
		temp=head->next;
		delete head;
		head=temp;
	}
	head = NULL;
*/
}

template <class T>
void List<T>::insertAtHead(T item)
{
	ListItem<T> *temp;
	temp=new ListItem<T>(item);
	temp->next=head;
	temp->prev=NULL;
	if(head!=NULL)
	{	head->prev=temp;	}
	head=temp;
}

template <class T>
void List<T>::insertAtTail(T item)
{
	ListItem<T> *temp;
	temp=new ListItem<T>(item);
	temp->next=NULL;
	temp->prev=getTail();
	if(head!=NULL)
	{	getTail()->next=temp;	}
	else
	{	head=temp;	}
}

template <class T>
void List<T>::insertAfter(T toInsert, T afterWhat)
{
	ListItem<T> *temp, *temp2;
	temp2=head;
	while(temp2->value!=afterWhat&&temp2!=NULL)
	{	temp2=temp2->next;	}
	if(temp2->value==afterWhat)
	{
		if(temp2->next==NULL)
		{
			insertAtTail(toInsert);
		}
		else
		{
			temp=new ListItem<T>(toInsert);
			temp->next=temp2->next;
			temp2->next=temp;
			temp->prev=temp2;
			temp2=temp->next;
			temp2->prev=temp;
		}
	}
}

template <class T>
void List<T>::insertSorted(T item)
{
		ListItem<T> *temp, *temp2;
		temp2=head;
		while(temp2!=NULL&&temp2->value < item)
		{	temp2=temp2->next;	}
		if(temp2==NULL)
		{
			insertAtTail(item);
		}	
		else if(temp2==head)
		{
			insertAtHead(item);
		}
		else
		{
			temp=new ListItem<T>(item);
			temp2=temp2->prev;
			temp->next=temp2->next;
			temp2->next=temp;
			temp->prev=temp2;
			temp2=temp->next;
			temp2->prev=temp;
		}
}

template <class T>
ListItem<T>* List<T>::getHead()
{
	return head;
}

template <class T>
ListItem<T>* List<T>::getTail()
{
	if(length())
	{
		ListItem<T> *temp;
		temp = head;
		while (temp->next != NULL)
		{
 				temp = temp->next;
		}
		return temp;
	}
	else
	{	return NULL;	}
}

template <class T>
ListItem<T> *List<T>::searchFor(T item)
{
	ListItem<T> *temp;
	temp = head;
	while (temp != NULL)
	{
		if(temp->value==item)
		{	return temp;	}
		temp=temp->next;
	}
	return NULL;
}

template <class T>
void List<T>::deleteElement(T item)
{
	ListItem<T> *temp, *temp2;
	temp=head;
	if(head!=NULL)
	{
		while(temp->value!=item&&temp!=NULL)
		{	temp=temp->next;	}
		if(temp==head)
		{	deleteHead();	}
		else if(temp==getTail())
		{	deleteTail();	}
		else if(temp!=NULL)
		{
			temp2=temp->next;
			temp=temp->prev;
			temp->next=temp2;
			temp2->prev=temp;
			temp=temp->next;
			delete temp;
		}
	}
}

template <class T>
void List<T>::deleteHead()
{
	if(head!=NULL)
	{
		ListItem<T> *temp;
		temp=head;
		if(temp->next==NULL)
		{
			head=NULL;
		}
		else
		{
			head=head->next;
			head->prev=NULL;
		}
		delete temp;
	}
}

template <class T>
void List<T>::deleteTail()
{
	if(head!=NULL)
	{
		ListItem<T> *temp;
		temp=getTail();
		if(temp->prev==NULL)
		{
			head=NULL;
		}
		else
		{
			ListItem<T> *temp2;
			temp2=getTail()->prev;
			temp2->next=NULL;
		}
		delete temp;
	}
}

template <class T>
int List<T>::length()
{
	ListItem<T> *temp;
	int len=0;
	temp = head;
	while (temp != NULL)
	{
 			temp = temp->next;
 			len++;
	}
	return len;
}


template <class T>
void List<T>::display_list ()
{
	ListItem<T> *temp2;
	temp2 = head;
	while (temp2 != NULL)
	{
		cout<< temp2->value <<endl;
 		temp2 = temp2->next;
	}
}


#endif
