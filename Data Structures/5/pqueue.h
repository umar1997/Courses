#ifndef PQUEUE__H
#define PQUEUE__H
#include <iostream>
#include <vector>
using namespace std;

template<class T>
class pqueue
{
	protected:
		int size;
	public:
		int numE; //num of elements in heap
		T* heap;
		pqueue(vector<T> insert);
		T ExtractMin();

		void insertKey(T k); //for pqueue()
		void MinHeapify(int i);//for ExtractMin()
		T getMin();
		void deleteKey(int i);
		bool isEmpty();
};


#endif
