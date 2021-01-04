/*
	
	Time Complexity Is n^n if not memoized
					and Is n^3 if memoized
	ruler(n) = min(q, y-x + ruler( a , i   , k-1 ,   x  , a[k]   ,  k , M )
				          + ruler( a , k+1 , j   , a[k] ,   y    , n-k, M ));
*/



#include <iostream>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

int n = 3;

int **M = new int*[n];

int ruler(int a[], int i, int j, int x, int y, int n, int **M)
{
	/*if(M[i][j]!=-1)
		return M[i][j];*/
	if(i > j)
		return 0;
	else
	{	
		int q = 999999;
		for (int k = i; k <= j; ++k)
		{
			q = min(q, y-x + ruler( a , i   , k-1 ,   x  , a[k]   ,  k , M )
						   + ruler( a , k+1 , j   , a[k] ,   y    , n-k, M ));
		}
		M[i][j]= q;
		return q;
	}
}

int main()
{
	int a[]={3,5,10};
	int L = 15;
	int n = 3
	for (int i = 0; i < n; ++i)
	{
		M[i] = new int[n];		
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			M[i][j] = -1;
		}
	}

	int x = ruler(a,0,n-1,0,L,n,M);

	/*for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout << M[i][j] << " ";
		}
		cout << endl;
	}*/
	cout << "Least Cost: " << x << endl;
}