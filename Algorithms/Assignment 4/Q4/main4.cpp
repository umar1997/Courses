/*
	Time Complexity = O(length_1 * length_2)
	No of sub Problems = length_1 * length_2
	Time for one Sub Problem O(1)
	Recurrence Relation:
		i is the ith char from string 1
		j is the jth char from string 2

		interleave(i,j) = Either str1(i-1)==str3(i-j+1) && interleave(i-1,j) ==1
							||	 str1(j-1)==str3(i-j+1) && interleave(i,j-1) ==1
		Otherwise = 0
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
	string par;
};

int main()
{
	/*FILE READING*/
	ifstream read;
	read.open("qa.txt");

	if(read.is_open())
	{
		string a;
		getline(read, a);
		string b;
		getline(read, b);
		string s;
		getline(read, s);

		cout << a << endl;
		cout << b << endl;
		cout << s << endl;
		cout << endl;

		int an = a.length();
		int bn = b.length();
		int anb = s.length();

		if(an+bn!=anb)
		{
			cout << "Not Valid" << endl;
		}

		node table[bn+1][an+1];
		for(int i=0;i<bn+1;i++)
		{
			for (int j = 0; j < an+1; ++j)
			{
				table[i][j].val = 0;
			}
		}
		table[0][0].val=1;
		table[0][0].par = "";
		
		//Verticle for loop
		for(int i=0;i<bn; i++)
		{
			string sc = s.substr(i,1);
			string sb = b.substr(i,1);
			if(sc==sb)
			{
				if(table[i][0].val==1)
				{
					table[i+1][0].val = 1;
					table[i+1][0].par= table[i][0].par + " 2" + sb;
				}
				else
					table[i+1][0].val = 0;
			}
			else
				table[i+1][0].val = 0;
		}
		//Horizontle for loop
		for(int i=0;i<an; i++)
		{
			string sc = s.substr(i,1);
			string sa = a.substr(i,1);
			if(sc==sa)
			{
				if(table[0][i].val==1)
				{
					table[0][i+1].val = 1;
					table[0][i+1].par= table[0][i].par + " 1" + sa;
				}
				else
					table[0][i+1].val = 0;
			}
			else
				table[0][i+1].val = 0;
		}
		/*The Centre*/
		vector<string> v;
		for (int i = 1; i < bn+1; ++i)
		{
			for (int j = 1; j < an+1; ++j)
			{
				string c = s.substr(i+j-1,1);
				string sb =  b.substr(i-1,1);
				string sa = a.substr(j-1,1);
				if(sb == c)
				{
					if(table[i-1][j].val==1)
					{
						table[i][j].val=1;
						table[i][j].par= table[i-1][j].par + " 2" + sb;
					}

				}
				else if(sa == c)
				{
					if(table[i][j-1].val==1)
					{
						table[i][j].val=1;
						table[i][j].par= table[i][j-1].par + " 1" + sa;
					}
				}
			}
		}
		/*PRINT*/
		for(int i=0;i<bn+1;i++)
		{
			for (int j = 0; j < an+1; ++j)
			{
				cout << table[i][j].val << " ";
			}
			cout << endl;
		}
		cout << endl;
		if(table[bn][an].val)
		{
			string c = "1";
			string s = table[bn][an].par;
			s.erase(remove(s.begin(), s.end(), ' '),s.end());
			for (int i = 1; i <s.length() ; ++i)
			{
				string ch = s.substr(i,1);
				if(ch=="1" || ch=="2")
				{
					if(ch=="1" && c=="1")
					{
						s.erase(i,1);
					}
					else if(ch=="1" && c=="2")
					{
						s.replace(i,1,"1");
						c="1";
					}
					else if(ch=="2" && c =="2")
					{
						s.erase(i,1);
					}
					else if(ch=="2" && c =="1")
					{
						s.replace(i,1,"2");
						c="2";
					}
				}
			}
			for (int i = 0; i <s.length() ; ++i)
			{
				string ch = s.substr(i,1);
				if(ch == "1")
				{
					s.replace(i,1," S1 ");
					i+=3;
				}
				else if(ch == "2")
				{
					s.replace(i,1," S2 ");
					i+=3;
				}
			}
			cout << s << endl;
			cout << "VALID" << endl;
		}
		else
		{
			cout << "INVALID" << endl;
		}
	}
	else
	{
		cout << "Error 404: File not found.";
	}
}

