#ifndef __SORTS_H
#define __SORTS_H

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <ctime>

#include "list.cpp"

using namespace std;

vector<long> InsertionSort(vector<long> nums);
vector<long> MergeSort(vector<long> nums);
vector<long> QuickSortArray(vector<long> nums);
vector<long> QuickSortList(vector<long> nums);
vector<long> HeapSort(vector<long> nums);

ListItem<long> *combine(List<long> *first1, List<long> *second1);
List<long>* merge1(List<long> * a);

long* qs1(long arr[], int low, int high);

List<long> *qs2(List<long> *a);
ListItem<long> *combine2(List<long>*left, List<long>*mid, List<long>*right);

// ListItem<long> *merge1(ListItem<long> *a);
// ListItem<long> *findMiddle(ListItem<long> *start);
// ListItem<long> *combine(ListItem<long> *first, ListItem<long> *second);

//void qs1(long arr[], int low, int high);


//List<long>* qs2(List<long> list, ListItem<long> low, ListItem<long> high);


#endif