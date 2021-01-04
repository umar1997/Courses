#ifndef __PQUEUE_CPP
#define __PQUEUE_CPP
#include "pqueue.h"
#include <cmath>

template <class T>
pqueue<T>::pqueue(vector<T> insert)
{
	size= insert.size();
	heap= new T[size];
	numE=0;
	for (int i=0; i<size;i++)
	{
		insertKey(insert[i]);
	}


}

template <class T>
T pqueue<T>::ExtractMin()
{
	// if (numE<1)
 //        return INT_MIN;
 //    else if(numE==1)
 //    {
 //        T min1= heap[0];
 //        numE=0;

 //        return min1;
 //    }
 //    else
 //    {
        T min1= heap[0];

        numE=numE-1;
        heap[0]=heap[numE];
        MinHeapify(0);

        return min1;
 //    }
}

template <class T>
void pqueue<T>:: MinHeapify(int i)
{
	if(i>= numE)
        return;

    int right_child= 2*i+2;
    int left_child= 2*i+1;
    int min1=i;
    if(right_child<numE) //first compare with right child
    {
        min1 = (heap[right_child]<heap[i])? right_child:i;
    }

    if(left_child<numE) //then compare with left child
    {
        min1= (heap[left_child]<heap[min1])? left_child:min1;
    }

    if (heap[min1]==heap[i]) //now check if any child was smaller
    {

    }
    else
    {
        T temp= heap[min1];
        heap[min1]= heap[i];
        heap[i]=temp;

        MinHeapify(min1);
    }
}

template <class T>
T pqueue<T>::getMin()
{
    T x= heap[0];
    return x;
}

template <class T>
void pqueue<T>:: insertKey(T k)
{
	if (size==numE){

	}
    else
    {
        heap[numE]=k;
        int i=numE;
        numE=numE+1;

        //now check against parents if law is violated and fix it
        while(i>0)
        {
            if(heap[i]<heap[(i-1)/2])
            {
                T temp= heap[(i-1)/2];
                heap[(i-1)/2]=heap[i];
                heap[i]=temp;

                i=(i-1)/2;
            }
            else
                break;
        }

    }
}

template <class T>
void pqueue<T>::deleteKey(int i)
{
    if(i>=numE)
        return;
    //bring the key to the start of the array by replacing its value with INT_MIN and then remove it by extractMin()
    int replace_key= -2147483647; //INT_MIN
    heap[i]=replace_key;
    while(i>0)
    {
        if(heap[i]<heap[(i-1)/2])
        {
            T temp= heap[(i-1)/2];
            heap[(i-1)/2]=heap[i];
            heap[i]=temp;

            i=(i-1)/2;
        }
        else
            break;
    }

    ExtractMin();

}

template <class T>
bool pqueue<T>::isEmpty()
{
    if (numE==0)
        return true;
    return false;
}

// int main()
// {
// 	cout<<"hello world"<<endl;

// }
#endif
