#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

struct node
{
	int num;
	int ind;
};
int convi(string s)
{
	stringstream converter(s);
	int x;
	converter >> x;
	return x;
}
int main()
{
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*File Reading*/
	ifstream read;
	read.open("q32.txt");
	if(read.is_open())
	{
		int n;
		string line1, line2, line3;
		vector<node> row, col;
		/////////////////////////////
		getline(read, line1);
		n = convi(line1.substr(2));
		int table[n][n];
		for(int i=0; i<n; i++)
		{
			for(int j=0;j<n; j++)
			{
			 table[i][j]=0;
			}
		}
		/////////////////////////////
		getline(read, line2);
		int c=0, sep = line2.find("w");
		node a, b;
		line2 = line2.substr(sep+2);
		stringstream token(line2);

		string tab;
		while(getline(token,tab,' '))
		{	
			a.ind = c;
			a.num=convi(tab);
			row.push_back(a);
			c++;
		}
		/////////////////////////////
		getline(read, line3);
		sep = line3.find("l");
		line3 = line3.substr(sep+2);
		stringstream token2(line3);
		string tab2;
		c=0;
		while(getline(token2,tab2,' '))
		{
			b.ind = c;
			b.num =convi(tab2);
			col.push_back(b);
			c++;
		}
		/////////////////////////////
		// Print the numbers in row and column
		cout << "Row ";
		for(int i=0; i<row.size(); i++)
		{
			cout << row[i].num << "(" << row[i].ind <<")" << " ";
		}
		cout << endl << "Col ";
		for(int i=0; i<col.size(); i++)
		{
			cout << col[i].num << "(" << col[i].ind <<")" << " ";
		}
		cout << endl;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		int sum1=0, sum2=0;
		for(int i=0;i<n;i++)
		{
			sum1+=row[i].num;
			sum2+=col[i].num;
		}
		bool sum = true;
		if(sum1!=sum2)
		{
			sum = false;
			cout << endl << endl;
			cout << "Not Possible.";
		}
		// Here is where the magic begins...
		for(int i=0; i<row.size(); i++)
		{

			int size = row[i].num;
			node maxi[size];
			for (int k = 0; k < col.size()-1; k++) 
    		{ 
	        // Sorting the vector col.
	        	int min = k; 
	        	for (int j = k+1; j < col.size(); j++) 
	          		if (col[j].num < col[min].num) 
	            		min = j; 
	  
	        	int temp = col[min].num;
	        	int temp_ind = col[min].ind;
	        	col[min].num = col[k].num;
	        	col[min].ind = col[k].ind;
	        	col[k].num = temp;
	        	col[k].ind = temp_ind;
   			}
   			// Putting the Maximums in Maxi
   			int rev_itr = col.size()-1;
   			for(int j=0; j<size; j++)
   			{
   				maxi[j] = col[rev_itr];
   				rev_itr--;
   			}
   			// Filling the table and decrementing the values
   			int dec_itr = col.size()-1;
   			for(int j=0; j<size; j++)
   			{
   				int col_ind = maxi[j].ind;
   				table[i][col_ind] = 1;
   				col[dec_itr].num--;
   				dec_itr--;
   			} 
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	
		// Print the table
		if(sum)
		{
			cout << endl;
			for(int i=0; i<n; i++)
			{
				cout << i+1 << " | ";
				for(int j=0;j<n; j++)
				{
					cout << table[i][j] << " ";
				}
				cout << endl;
			}
			// Printing the indexes
			cout << endl;
			for(int i=0; i<n; i++)
			{
				for(int j=0;j<n; j++)
				{
					if(table[i][j])
					{
						cout << "(" << i+1 << "," << j+1 << ") ";
					}
				}
				cout << endl;
			}
		}
	}
return 0;
}
