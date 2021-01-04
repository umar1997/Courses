/*

	Time Complexity = n^3
	Number of Sub problems n^2
	Time for one sub problem n
	Space Complexity n^2

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
	int start_i;
	int start_j;
	int stop_i;
	int stop_j;
	int width;
	int sum;
};

int conv(string s)
{
	stringstream converter(s);
	int x;
	converter >> x;
	return x;
}

int main()
{
	/*FILE READING*/
	int n;
	ifstream read;
	read.open("qc.txt");

	if(read.is_open())
	{
		string first_line, loop_no;
		getline(read, first_line);
		loop_no = first_line.substr(2);
		stringstream loop(loop_no);
		loop >> n;
		int a[n][n];
		for (int i = 0; i < n; ++i)
		{
			string s;
			getline(read, s);
			s.erase(s.length()-1,1);
			if(s.find("{")==0)
				s.erase(0,1);
			s.erase(remove(s.begin(), s.end(), ' '),s.end());
			stringstream split(s);
			string token;
			int j = 0;
			while(getline(split,token,','))
			{
				a[i][j] = conv(token);
				j++;
			}

		}

		
		int b[n][n];
		/*Initialize*/
		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				b[i][j] = 0;
			}
		}
		/*Vertical*/
		for (int i = 0; i < n; ++i)
		{
			if(i==0)
				b[i][0] = a[i][0];
			else
				b[i][0] = b[i-1][0] + a[i][0];
		}
		/*Horizontle*/
		for (int j = 0; j < n; ++j)
		{
			if(j==0)
				b[0][j] = a[0][j];
			else
				b[0][j] = b[0][j-1] + a[0][j];
		}
		/*Centre*/
		for (int i = 1; i < n; ++i)
		{
			for (int j = 1; j <n; ++j)
			{
				b[i][j]= a[i][j] + b[i-1][j] + b[i][j-1] -b[i-1][j-1];
			}
		}
		node final;
		final.sum=0;
		/*The other Shiz*/
		for (int s = 1; s <= n; ++s)
		{
			for (int i = 0; i < n-s+1; ++i)
			{
				for (int j = 0; j < n-s+1; ++j)
				{
					int b_i = i+s-1;
					int b_j = j+s-1;
					int temp;
					if(b_i-s<0 && b_j-s<0)
						temp = b[b_i][b_j]-0-0+0;
					else if(b_i-s<0)
						temp = b[b_i][b_j]-0-b[b_i][b_j-s]+0;
					else if(b_j-s<0)
						temp = b[b_i][b_j]-b[b_i-s][b_j]-0+0;
					else
						temp = b[b_i][b_j]-b[b_i-s][b_j]-b[b_i][b_j-s]+b[b_i-s][b_j-s];

					if(temp>final.sum)
					{
	                    final.sum = temp;
	                    final.start_i = i;
	                    final.start_j = j;
	                    final.stop_i = b_i;
	                    final.stop_j = b_j;
	                    final.width = s;
					}
				}
			}

		}


		for (int i = 0; i < n; ++i)
		{
			for (int j = 0; j < n; ++j)
			{
				cout << b[i][j] << " ";
			}
			cout << endl;
		}
		cout << endl;

		cout << "Width: " << final.width << endl;
		cout << "Top Left: (" << final.start_i << ", " << final.start_j << ")" << endl; 
		cout << "Bottom Right: (" << final.stop_i << ", " << final.stop_j << ")" << endl; 
		cout << "Maximum Sum: " << final.sum << endl; 
	}
	else
		cout << "Error 404. File not found.";
}