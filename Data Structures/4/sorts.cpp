#ifndef __SORTS_CPP
#define __SORTS_CPP
#include "sorts.h"
#include "heap.cpp"
#include "list.cpp"
#include <cstdlib>
#include <ctime>

//=====================================================================================
vector<long> InsertionSort(vector<long> nums)
{
	int size1= nums.size();
	int j;
	long temp;
	
	long numbers[size1];
	for (int k=0;k<size1;k++) //copy to array
		numbers[k]= nums[k];
	
	for (int i=0;i<size1;i++)
	{
		j=i;	

		while (1)
		{
			if(j<=0)
				break;
			if(numbers[j-1]<=numbers[j])
				break;
			temp=numbers[j-1];
			
			numbers[j-1]= numbers[j];
			numbers[j]= temp;
			
			j=j-1;
		}	
	}
	
	for(int i=0;i<size1;i++)
		nums[i]=numbers[i];
	
	return nums;

}

//=====================================================================================
vector<long> MergeSort(vector<long> nums)
{
	int x= nums.size();
	if(x<=1)
		return nums;
	else
	{	
		List<long>*a;
		int x= nums.size();
		a = new List<long>;
		for(int i=0;i<x;i++)
			a->insertAtHead(nums[i]);
		
		List<long>*mergedlist = merge1(a);
		ListItem<long>*merged = mergedlist->head;

		int counter=0;
		while(merged)
		{    
		 	nums[counter]=merged->value;
			merged=merged->next;
			counter++;
		}
		return nums;

	} 

}

List<long>* merge1(List<long>* a)
{
	
	if(a->getHead()==NULL)
		return a;
	if(a->getHead()->next==NULL)
		return a;

	ListItem<long>* temp = a->head;
	int len=0;
	while(temp)
	{
		len++;
		temp=temp->next;
	}

	temp=a->head;

	
	List<long>* first = new List<long>;
	List<long>* second = new List<long>;
	int mid = len/2;
	int counter=0;
	while(temp!=NULL)
	{
		if(counter<mid)
			first->insertAtHead(temp->value);
		else
			second->insertAtHead(temp->value);
		
		counter++;
		temp=temp->next;
	}

	List<long>* combined= new List<long>;
	combined->head= combine(merge1(first), merge1(second));
	combined->deleteHead();
	return combined;
}



ListItem<long> *combine(List<long> *first1, List<long> *second1)
{
	ListItem<long> *newlist_start = new ListItem<long> (INT_MAX);
	ListItem<long> *newlist = newlist_start;
	
	ListItem<long> *first=first1->getHead();
	ListItem<long> *second=second1->getHead();	
	
	while(1)
	{
		if(first==NULL)
			break;
		else if(second==NULL)
			break;
		else
		{
			if(first->value< second->value)
			{	
				newlist->next=first;
				first=first->next;
				newlist=newlist->next;
			}
			else if(first->value >=second->value)
			{	
				newlist->next=second;
				second=second->next;
				newlist=newlist->next;
			}
		}	
	}	

	List<long>*rem= new List<long>;
	rem->head= first;
	List<long>*rem2= new List<long>;
	rem2->head= second;
	
	if(rem->getHead())
		newlist->next=rem->getHead();
	else if (rem2->getHead())
		newlist->next= rem2->getHead();
	
	return newlist_start;
	
}

//=====================================================================================
vector<long> QuickSortArray(vector<long> nums)
{
	
	int size1= nums.size();
	if (size1>1)
	{
		long *quicksortarray= new long[size1];
		
		for(int i=0;i<size1;i++)
			quicksortarray[i]=nums[i];

		qs1(quicksortarray, 0, size1-1);
		for (int i=0;i<size1;i++)
			nums[i]=quicksortarray[i];
		
	}
	return nums;


}

long* qs1(long arr[], int low, int high)
{
	if (low<high)
	{
		int i= low;
		int j= high;
		
		int p[3];
		int pivot;
		int pivotindex;
		p[0]=  arr[low];
		p[1]=  arr[(low+high)/2];
		p[2]=  arr[high];
		
		if( (p[0]<p[1] && p[0]>p[2]) || (p[0]<p[2] && p[0]>p[1]) )
		{
			
			pivot= p[0];
			pivotindex=low;

		}
		else if ((p[1]<p[0] && p[1]>p[2]) || (p[1]<p[2] && p[1]>p[0]))
		{
			pivot= p[1];
			pivotindex=(low+high)/2;
		}
		else{
			pivot=p[2];
			pivotindex= high;
		}
	
		pivot=p[0];	
		while(1)
		{ 
			if(i>j)
				break;
			else
			{
				while(1)
				{
					if(arr[i]<pivot)
						i=i+1;
					else
						break;
				}
				while(1)
				{	
					if (arr[j]>pivot)
						j=j-1;
					else
						break;
				}
				if(!(i>j))
				{
					long temp= arr[i]; 		//swap i and j 
					arr[i]=arr[j];
					arr[j]=temp;
					j=j-1;
					i=i+1;
				}	
			}


		}

			qs1(arr,low,j);
			qs1(arr,i,high);
	}

	return arr;

}


//=====================================================================================
vector<long> QuickSortList(vector<long> nums)
{
	int size1= nums.size();
	if(size1>1)
	{
		List<long> *qslist= new List<long>;

		for(int i=0;i<size1;i++)
			qslist->insertAtHead(nums[i]);
		
		List<long>*sortedlist = qs2(qslist);
		
		ListItem<long> *temp= sortedlist->getHead(); 
		for(int i=0; i<size1;i++){
			nums[i]= temp->value;
			temp=temp->next;
		}


	}
	return nums;
}

List<long> *qs2(List<long> *a)
{	
	if(a->getHead()==NULL)
		return a;
	if(a->getHead()->next==NULL)
		return a;
	
	
	int len=0;
	ListItem<long>*temp= a->getHead();
	while(temp)
	{
		len++;
		temp=temp->next;
	}
	srand(time(NULL));
	int midlen= rand()%len;
	
	temp = a->getHead();
	for (int i=0;i<midlen;i++)
		temp = temp->next;
	
	ListItem<long> *check = a->getHead();
	
	List<long>* left = new List<long>;
	List<long>* mid= new List<long>;
	List<long> *right= new List<long>;
	
	
	while (1)
	{
		if(check==NULL)
			break;

		if (temp->value>check->value)
		{
			left->insertAtHead(check->value);
			check=check->next;
		}
		else if (temp->value==check->value)
		{
			mid->insertAtHead(check->value);
			check=check->next;
		}
		else if(temp->value<check->value)
		{
			right->insertAtHead(check->value);
			check=check->next;
		}	
	}
	
	List<long>* combined= new List<long>;
	combined->head =combine2(qs2(left),mid,qs2(right));
	combined->deleteHead();
	
	return combined;
}

ListItem<long> *combine2(List<long>*left, List<long>*mid, List<long>*right)
{
	ListItem<long>*newlist_start= new ListItem<long>(INT_MAX);
	ListItem<long>*newlist= newlist_start;

	ListItem<long>*first1= left->getHead();
	ListItem<long>*mid1= mid->getHead();
	ListItem<long>*sec1= right->getHead();

	while(1)
	{
		if(first1)
		{
			newlist->next=first1;
			newlist=newlist->next;
			first1=first1->next;
		}
		else{

			break;	
		}
	}
	while(1)
	{
		if(mid1)
		{
			newlist->next=mid1;
			newlist=newlist->next;
			mid1=mid1->next;
		}
		else{

			break;
		}

	}
	while(1)
	{
		if(sec1)
		{
			newlist->next=sec1;
			newlist=newlist->next;
			sec1=sec1->next;
		}
		else 
			break;

	}
	return newlist_start;

}


//=====================================================================================
vector<long> HeapSort(vector<long> nums)
{

	int size1= nums.size();
	MinHeap a(size1);

	for(int i=0;i<size1;i++)
		a.insertKey(nums[i]);
	
	for(int i=0;i<size1;i++)
		nums[i]= a.extractMin();

	return nums;

}



#endif
