/*
	Time Complexity O(n) *2^log(sum)
	Number of sub problems n*sum
	Time for each sub Problem O(1)

	Recursive Relation
	Closest_Diff(i,j)  = 1 
				where Closest_Diff(i-ele, j-1) == 1
				or    Closest_Diff(i+ele, j-1) == 1
				otherwise = 0
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


struct node
{
	int val;
	vector<int> v;
};

int conv(string s)
{
	stringstream converter(s);
	int x;
	converter >> x;
	return x;
}

int isSum(int i,int W, int a[])
{
	if(i<0)
	{
		return 0;
	}
	else if(W<a[i])
	{
		int x = isSum(i-1,W,a);
		return x;
	}
	else
	{
		int x = max(isSum(i-1,W,a),a[i]+isSum(i-1,W-a[i],a));
		return x;
	}
}
int main()
{
	ifstream read;
	read.open("qt.txt");
	if(read.is_open())
	{
		int k;
		string first_line, loop_no;
		getline(read, first_line);
		loop_no = first_line.substr(2);
		stringstream loop(loop_no);
		loop >> k;

		string b;
		getline(read, b);
		b = b.substr(2);
		stringstream split(b);
		string token;
		vector<int> store;
		while(getline(split,token,' '))
		{
			store.push_back(conv(token));
		}
		int a[store.size()];
		for (int i = 0; i < store.size(); ++i)
		{
			a[i]=store[i];
		}

		int n = sizeof(a)/sizeof(a[0]);
		int total = 0;
		cout << "K " << k << endl;
		cout << "Array: ";
		for (int i = 0; i < n; ++i)
		{
			cout << a[i] << " ";
			total+=a[i];
		}
		cout << endl;
		int W = (total + k)/2;
	    int sum = isSum(n-1,W,a); // size of array, Capacity, array name 

	    if(sum==W)
	    {
	    	/*Knap Sack Memoization*/
	    	node M[n+1][W+1];
		    for (int i = 0; i < n+1; i++)
		    {
		        for (int j = 0; j < W+1; j++)
		        {
		            if (i==0)
		                M[i][j].val = 0;
		            else if(j==0)
		           		M[i][j].val = 0;
		            else if (a[i-1]< j+1)
		            {

		                int one = a[i-1] + M[i-1][j-a[i-1]].val;
		                int two =  M[i-1][j].val;
		                if(one > two)
		                {
		                	M[i][j].v = M[i-1][j-a[i-1]].v;
		                	M[i][j].v.push_back(a[i-1]);
		                	M[i][j].val = one;
		                }
		                else
		                {
		                	M[i][j].v = M[i-1][j].v;
		                	M[i][j].val= two;
		                }
			       	}	
		            else
		                M[i][j].val = M[i-1][j].val;
		        }
		    }

			   /*for(int i = 0; i<n+1; i++)
			   {
			       for(int j=0; j<W+1; j++)
			       {
			          cout << M[i][j].val << " ";
			       }
			       cout << endl;
			   }*/

			/*Remaining Vector*/
			int two = total-W;
			vector<int> rem;
			for (int i = 0; i < n; ++i)
			{
				bool check = true;
				for (int j = 0; j < M[n][W].v.size(); ++j)
				{
					if( M[n][W].v[j]==a[i])
					{
						check = false;
					}
				}
				if(check)
					rem.push_back(a[i]);
			}
			int rem_sum = 0;
			for (int i = 0; i < rem.size(); ++i)
			{
				rem_sum += rem[i];
			}
			if(rem_sum == two)
			{
				cout << "POSSIBLE" << endl;
				cout << "S1: ";
				for (int i = 0; i < M[n][W].v.size(); ++i)
				{
					cout << M[n][W].v[i] << " ";
				}
				cout << "= " << W << endl;
				cout << "S2: ";
				for (int i = 0; i < rem.size(); ++i)
				{
					cout << rem[i] << " ";
				}
				cout << "= " << two << endl;
				cout << "Difference = " << W << " - " << two << " = " << k;
			}
			else
				cout << "NOT POSSIBLE" << endl;
	    }
	    else
	    	cout << "NOT POSSIBLE" << endl;
	}

}
