#ifndef __HEAP_CPP
#define __HEAP_CPP
#include "heap.h"
#include <cmath>

MinHeap::MinHeap(int cap)
{
    capacity= cap;
    harr= new int[capacity];
    heap_size=0;
}

void MinHeap::MinHeapify(int i) //sort the array
{
    if(i>= heap_size)
        return;

    int right_child= 2*i+2;
    int left_child= 2*i+1;
    int min1=i;
    if(right_child<heap_size) //first compare with right child
    {
        min1 = (harr[right_child]<harr[i])? right_child:i;
    }

    if(left_child<heap_size) //then compare with left child
    {
        min1= (harr[left_child]<harr[min1])? left_child:min1;
    }

    if (harr[min1]==harr[i]) //now check if any child was smaller
    {

    }
    else
    {
        int temp= harr[min1];
        harr[min1]= harr[i];
        harr[i]=temp;

        MinHeapify(min1);
    }

}

int MinHeap::parent(int i)
{
    int x= floor(i-1)/2;
    return x;
}

int MinHeap::left(int i)
{
    int x = 2*i +1;
    return x;

}

int MinHeap::right(int i)
{
    int x = 2*i +2;
    return x;

}

int MinHeap::extractMin()
{
    if (heap_size<1)
        return INT_MIN;
    else if(heap_size==1)
    {
        int min1= getMin();
        heap_size=0;

        return min1;
    }
    else
    {
        int min1= getMin();

        heap_size=heap_size-1;
        harr[0]=harr[heap_size];
        MinHeapify(0);

        return min1;
    }
}

void MinHeap::decreaseKey(int i, int new_val)
{
    if (i>= heap_size)
        return;

    harr[i]=new_val;
    while(i>0)
    {
        if(harr[i]<harr[parent(i)])
        {
            int temp= harr[parent(i)];
            harr[parent(i)]=harr[i];
            harr[i]=temp;

            i=parent(i);
        }
        else 
        	break;
    }
}

int MinHeap::getMin()
{
    int x= harr[0];
    return x;
}

void MinHeap::deleteKey(int i)
{
    if(i>=heap_size)
        return;
    //bring the key to the start of the array by replacing its value with INT_MIN and then remove it by extractMin()
    int replace_key= INT_MIN;
    harr[i]=replace_key;
    while(i>0)
    {
        if(harr[i]<harr[parent(i)])
        {
            int temp= harr[parent(i)];
            harr[parent(i)]=harr[i];
            harr[i]=temp;

            i=parent(i);
        }
        else
        	break;
    }

    extractMin();

}

void MinHeap::insertKey(int k)
{
    if (capacity==heap_size){}
    else
    {
        harr[heap_size]=k;
        int i=heap_size;
        heap_size=heap_size+1;

        //now check against parents if law is violated and fix it
        while(i>0)
        {
            if(harr[i]<harr[parent(i)])
            {
                //cout<<"smaller"<<endl;
                int temp= harr[parent(i)];
                harr[parent(i)]=harr[i];
                harr[i]=temp;

                i=parent(i);
            }
            else
                break;
                //cout<<harr[i]<< " is not smaller than parent "<<harr[parent(i)]<<endl;
        }

    }
    // cout<<"harr"<<ends;
    // for (int i=0;i<heap_size;i++)
    //     cout<<harr[i]<<ends;
    // cout<<endl;
}

int* MinHeap::getHeap()
{
	return harr;
}

#endif
