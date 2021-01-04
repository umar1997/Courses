/*
    Time Complexity O(n)
    Number of Sub Problems: n
    Time for each Sub Problem: O(1)

    Recurrence Relation:
    Where n is the week number
    maximizer[n] = max(high[n]+maximizer(n-2), low[n] + maximizer(n-1))  
*/


#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

int conv(string s)
{
	stringstream converter(s);
	int x;
	converter >> x;
	return x;
}

struct node
{
    int value;
    int check;
};

vector<node > v;

int maximizer(int rh[], int rl[], int m[], int n)
{
	if(m[n]!=-1 && n>-1)
	{
		return m[n];
	}
	else if(n<0)
	{
		return 0;
	}
	else
	{
		int x = max(rh[n]+maximizer(rh, rl, m, n-2), rl[n]+maximizer(rh, rl, m, n-1));
		m[n]=x;
		return x;
	}
}

int main()
{
	/*FILE READING*/
	int n;
	ifstream read;
	read.open("qe.txt");

	if(read.is_open())
	{
		string first_line, loop_no;
		getline(read, first_line);
		loop_no = first_line.substr(2);
		stringstream loop(loop_no);
		loop >> n;

		int rh[n];
		int rl[n];
		int m[n];
		for (int i = 0; i < n; ++i)
		{
			m[i]= -1;
		}

		for (int i = 0; i < 2; ++i)
		{
			string b;
			getline(read, b);
			b = b.substr(3);
			stringstream split(b);
			string token;
			int j = 0;
			while(getline(split,token,' '))
			{
				if(i==0)
					rh[j] = conv(token);
				else
					rl[j] = conv(token);
				j++;
			}
		}
		cout << "RH: ";
        for(int i=0;i<n;i++)
        {
            cout << rh[i] << " ";
        }
        cout << endl << "RL: ";
        for(int i=0;i<n;i++)
        {
            cout << rl[i] << " ";
        }
        cout << endl;
        cout << endl;
		int x = maximizer(rh, rl, m, n-1);
        m[-1]= 0;
        vector<node> v;
        for(int i=0;i<n;i++)
        {
            if(rh[i]==m[i])
            {
                if(i!=0)
                {
                    v[v.size()-1].value = -1;
                }
                node temp;
                temp.check = 1;
                temp.value = rh[i];
                v.push_back(temp);
            }
            else if(rl[i]==m[i])
            {
                node temp;
                temp.check = 0;
                temp.value = rl[i];
                v.push_back(temp);
            }
            else if(m[i]-rh[i]==m[i-2])
            {
                v[v.size()-1].value = -1;
                node temp;
                temp.check = 1;
                temp.value = rh[i];
                v.push_back(temp);
            }
            else if(m[i]-rl[i]==m[i-1])
            {
                node temp;
                temp.check = 0;
                temp.value = rl[i];
                v.push_back(temp);
            }
        }
        for(int i=0;i<v.size();i++)
        {
            if(v[i].value==-1 && v[i-1].value==-1)
            {
                v[i-1].value = rl[i-1];
            }
        }
        for(int i=0;i<v.size();i++)
        {
            if(v[i].value==-1)
                cout << "Week " << i+1 << ": Primming...\n";
            else if(v[i].check == 1)
                cout << "Week " << i+1 << ": High " << v[i].value << endl;
            else if(v[i].check == 0)
                cout << "Week " << i+1 << ": Low " << v[i].value << endl;
        }
		cout << "Total Revenue: " << x << endl;

	}
	else
	{
		cout << "Error 404: File not found." << endl;
	}
}
