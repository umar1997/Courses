
/*
	Recurrence Realtion = 2T(n/2) + (n)
	Time Complexity = O(nlogn)

	In this code we are basically using a D&C method to divide our arrays into smaller arrays
	where in every we check if a specie is greater than that size of the array by 2 and if it 
	is greater than n/2 return that value of that specie.

*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iomanip>
#include <time.h>

using namespace std;

int digit = 0;

bool decode(int arr[], int val_a, int val_b)
{
	if(val_b == val_a)
		return true;
	else
		return false;
}
int checkSpecies(int arr[], int L, int S, int a, int b)
{
	int c1 =0, c2 =0;
	for (int i = L; i < L+S; ++i)
	{
		if(decode(arr,arr[i],a))
		{
			c1++;
		}
		else if(decode(arr,arr[i],b))
		{
			c2++;
		}
	}

	if(c1>c2 && c1>(S/2))
	{
		return a;
	}
	else if(c2>c1 && c2>(S/2))
	{
		return b;
	}
	else
		return -1;

}

int maxFreq(int arr[], int L, int R, int S)
{
	if (S<=2)
	{
		int r;
		if(S==1 || S==0)
		{
			r = arr[L];
		}
		else
		{
			int val_a = arr[L];
			int val_b = arr[R];
			bool same = decode(arr,val_a,val_b);
			if(same)
				r = val_a;
			else
				r = -1;
		}
		return r;
	}
	else
	{
		int ax = maxFreq(arr, L , L+(R-L)/2 , R-L+1);
		int bx = maxFreq(arr, L+((R-L/2)+1) , R , R-L+1);
		digit = checkSpecies(arr,L,S,ax,bx);
	}
}
int main()
{
	/*srand(time(NULL));
	int n, m;
	cout << "Enter n: ";
	cin >> n;
	cout << "Enter m(species): ";
	cin >> m;
	int arr[n];
	for (int i = 0; i < n; ++i)
	{
		arr[i]= rand() % m + 1;

	}*/


	int arr[] = {1, 2, 3, 3, 1, 2, 2, 1, 2, 2, 3, 2, 2, 2, 1};
	//int arr[]= {2, 1, 1, 2, 2, 1, 1, 1, 2, 2, 2};
	int n = sizeof(arr)/sizeof(arr[0]);
	int m=2;

	digit = maxFreq(arr,0,n-1,n);
	cout << "{";
	for(int i=0;i<n;i++)
	{
		if(i==n-1)
			cout << arr[i] << "}";
		else
			cout << arr[i] << ", ";
	}
	cout << endl;
	if(digit!=-1)
    {
        cout << "SUCCESS!" << endl;
        cout << "{ ";
        for(int i=0;i<n;i++)
        {   if(arr[i]==digit)
            {
                cout << i << " ";
            }
            if(i==n-1)
                cout << "}";
        }
    }
    else
        cout << "FAILURE!";
}
