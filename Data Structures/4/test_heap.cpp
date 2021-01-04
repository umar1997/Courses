#include "heap.cpp"
#include <vector>
#include <algorithm>
#include <iostream>
using namespace std;

void test_insert(MinHeap* heap);
void test_delete(MinHeap* heap);
void test_extractMin(MinHeap* heap);
vector<int> ref_vec;

int main()
{
	MinHeap* heap = new MinHeap(100);
//------------------------
	heap->insertKey(34);
	heap->insertKey(7);
	heap->insertKey(53);
	heap->insertKey(12);
	heap->insertKey(68);
	heap->insertKey(90);
	heap->insertKey(24);
	heap->insertKey(71);
	heap->insertKey(13);
	heap->insertKey(3);
	heap->insertKey(1);
	heap->insertKey(61);
	heap->insertKey(18);
	heap->insertKey(30);
	heap->insertKey(50);
	heap->insertKey(11);
	heap->insertKey(52);
	heap->insertKey(54);
	heap->insertKey(56);
	heap->insertKey(55);
	heap->insertKey(80);
	heap->insertKey(97);
	heap->insertKey(91);
	heap->insertKey(23);
	heap->insertKey(29);
	heap->insertKey(33);
	heap->insertKey(73);
	heap->insertKey(77);
	heap->insertKey(89);
	heap->insertKey(16);
	heap->insertKey(20);
	heap->insertKey(35);
	heap->insertKey(43);
	heap->insertKey(47);
	heap->insertKey(57);
	heap->insertKey(66);
	heap->insertKey(88);
	heap->insertKey(2);
	heap->insertKey(9);
	heap->insertKey(64);

//------------------------------
	
	ref_vec.push_back(1);
	ref_vec.push_back(2);
	ref_vec.push_back(16);
	ref_vec.push_back(3);
	ref_vec.push_back(7);
	ref_vec.push_back(23);
	ref_vec.push_back(18);
	ref_vec.push_back(13);
	ref_vec.push_back(9);
	ref_vec.push_back(55);
	ref_vec.push_back(12);
	ref_vec.push_back(24);
	ref_vec.push_back(33);
	ref_vec.push_back(53);
	ref_vec.push_back(20);
	ref_vec.push_back(35);
	ref_vec.push_back(47);
	ref_vec.push_back(54);
	ref_vec.push_back(11);
	ref_vec.push_back(64);
	ref_vec.push_back(80);
	ref_vec.push_back(97);
	ref_vec.push_back(91);
	ref_vec.push_back(90);
	ref_vec.push_back(29);
	ref_vec.push_back(61);
	ref_vec.push_back(73);
	ref_vec.push_back(77);
	ref_vec.push_back(89);
	ref_vec.push_back(50);
	ref_vec.push_back(30);
	ref_vec.push_back(71);
	ref_vec.push_back(43);
	ref_vec.push_back(52);
	ref_vec.push_back(57);
	ref_vec.push_back(66);
	ref_vec.push_back(88);
	ref_vec.push_back(56);
	ref_vec.push_back(34);
	ref_vec.push_back(68);
	
	test_insert(heap);

	heap->deleteKey(5);
	heap->deleteKey(11);
	heap->deleteKey(17);
	heap->deleteKey(29);
	heap->deleteKey(33);
	heap->deleteKey(21);
	heap->deleteKey(34);
	heap->deleteKey(5);
	heap->deleteKey(9);

	ref_vec.clear();
	ref_vec.push_back(1);
	ref_vec.push_back(2);
	ref_vec.push_back(16);
	ref_vec.push_back(3);
	ref_vec.push_back(7);
	ref_vec.push_back(33);
	ref_vec.push_back(18);
	ref_vec.push_back(13);
	ref_vec.push_back(9);
	ref_vec.push_back(43);
	ref_vec.push_back(12);
	ref_vec.push_back(34);
	ref_vec.push_back(61);
	ref_vec.push_back(53);
	ref_vec.push_back(20);
	ref_vec.push_back(35);
	ref_vec.push_back(47);
	ref_vec.push_back(56);
	ref_vec.push_back(11);
	ref_vec.push_back(64);
	ref_vec.push_back(80);
	ref_vec.push_back(57);
	ref_vec.push_back(91);
	ref_vec.push_back(90);
	ref_vec.push_back(68);
	ref_vec.push_back(66);
	ref_vec.push_back(73);
	ref_vec.push_back(77);
	ref_vec.push_back(89);
	ref_vec.push_back(88);
	ref_vec.push_back(30);
	ref_vec.push_back(71);

	test_delete(heap);
	test_extractMin(heap);
}

void test_insert(MinHeap* heap)
{
	cout<<"Testing Insert function.."<<endl;
	int counter=0;
	int len = ref_vec.size();
	int *head = heap->getHeap();
	for (int i=0;i<len;i++)
	{
		if (head[i]==ref_vec[i])
		{
			counter++;
		}

	}

	cout<<"Total points:: "<<(counter/ref_vec.size())*10<<"/10"<<endl<<endl;
	return;
}

void test_delete(MinHeap* heap)
{
	cout<<"Testing delete function..."<<endl;
	int counter=0;
	int len = ref_vec.size();
	int *head = heap->getHeap();
	for (int i=0;i<len;i++)
	{
		if (head[i]==ref_vec[i])
		{
			counter++;
		}

	}
	cout<<"Total points:: "<<(counter/ref_vec.size())*10<<"/10"<<endl<<endl;
	return;
}

void test_extractMin(MinHeap* heap)
{
	cout << "Testing ExtractMin function..."<<endl;
	int counter = 0;
	sort(ref_vec.begin(), ref_vec.end());
	int len = ref_vec.size();
	for (int i=0;i<len;i++)
	{
		if (heap->extractMin()==ref_vec[i])
		{
			counter++;
		}
	}
	cout<<"Total points:: "<<(counter/ref_vec.size())*10<<"/10"<<endl<<endl;
	return;
}