/*
Time Complexity is O(n^2)

It pops each team from teams. If the location does not already have a team assigned, it assigns it. Else
it compares the higher preference team in the location list. It does this until the total number of teams
assigned are equal to number of locations.
*/
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

struct node
{
	int Index;
	vector<int> Locations;
};

int conv(string s)
{
	stringstream converter(s);
	int x;
	converter >> x;
	return x;
}

bool hasDuplicates(vector<int>& arr) {
    for (int i = 0; i < arr.size(); ++i) {
        for (int j = i + 1; j < arr.size(); ++j) {
            if (arr[i] == arr[j])
                if(arr[i]==0 && arr[j]==0)
                {

                }
                else
                	return true;
        }
    }
    return false;
}

int return_i(vector<int>& arr) {
    for (int i = 0; i < arr.size(); ++i) {
        for (int j = i + 1; j < arr.size(); ++j) {
            if (arr[i] == arr[j])
                if(arr[i]==0 && arr[j]==0)
                {

                }
                else
                	return i;
        }
    }
}

int return_j(vector<int>& arr) {
    for (int i = 0; i < arr.size(); ++i) {
        for (int j = i + 1; j < arr.size(); ++j) {
            if (arr[i] == arr[j])
                if(arr[i]==0 && arr[j]==0)
                {

                }
                else
                	return j;
        }
    }
}

int main()
{
	/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/*FILE READING*/
	int n;
	ifstream read;
	read.open("q22.txt");

	if(read.is_open())
	{
		// Getting the no. of total vertices
		string first_line, loop_no;
		getline(read, first_line);
		loop_no = first_line.substr(2);
		stringstream loop(loop_no);
		loop >> n;

		node table[n];
		vector<int> final(n);
		for (int i = 0; i < final.size(); ++i)
		{
			final[i] = 0;
		}

		int itr = 0;
		while(!read.eof())
		{
			string rest_lines, a, b;
			getline(read, rest_lines);
			int colon = rest_lines.find(":"); // Gives position of colon
			a = rest_lines.substr(0, colon); // Team
			b = rest_lines.substr(colon+1); // Locations
			b.erase(remove(b.begin(), b.end(), ' '),b.end());
			b.erase(remove(b.begin(), b.end(), 'L'),b.end());
			cout << a << ": ";
			cout << b << endl;

			table[itr].Index = itr+1;

			stringstream split(b);
			string token;
			while(getline(split,token,',')) // Seperates from the comma
			{
				if(token=="-")
					table[itr].Locations.push_back(0);
				else
					table[itr].Locations.push_back(conv(token));
			}
			itr++;
		}
		cout << endl;
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*PRINT*/
		for (int i = 0; i < n; ++i)
		{
			cout << "T" << table[i].Index << ": ";
			for(int j = 0; j < table[i].Locations.size(); j++)
			{
				cout << table[i].Locations[j] << " ";
			}
			cout << endl;
		}
		cout << endl;
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*THE LOOP*/
		bool fin_check = false;
		int i = 0;
		while(!fin_check)
		{
			for (int j = 0; j < n; ++j)
			{
				if(final[j]==0 && table[j].Locations[i]!=0)
					final[j] = table[j].Locations[i];
			}

			////////////// Printercls
			/*cout << "PRE_PRINTER\n";
			for (int z = 0; z < n; ++z)
			{
				cout << z+1 << " : " << final[z] << endl;
			}

			cout << endl << endl;*/
			////////////////////////
			for(int j=0;j<n;j++)
			{
				bool dupli_check = hasDuplicates(final);
				bool zero_check = false;
				if(dupli_check)
				{
					int x = return_i(final);
					int y = return_j(final);
					if(final[x]!=0 && final[y]!=0)//////////////////////
					{
						if(final[x]==table[x].Locations[i])
						{
							final[y]=0;
						}
						else if(final[y]==table[y].Locations[i])
						{
							final[x]=0;
						}
					}							////////////////////////
				}
				else
				{
					for (int j = 0; j < n; ++j)
					{
						if(final[j]==0)
						{
							zero_check = true;
							break;
						}

					}
					if(!zero_check)
						fin_check = true;
				}
			}

			////////////// Printer
			/*for (int z = 0; z < n; ++z)
			{
				cout << z+1 << " : " << final[z] << endl;
			}

			cout << endl << endl;*/
			/////////////
			i++;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		cout << "Final Destinations: ";
		for (int i = 0; i < n; ++i)
		{
			if(i==n-1)
				cout << "T" << i+1 <<" L" << final[i];
			else
				cout << "T" << i+1 <<" L" << final[i] << ", ";
		}



	}
	else
		cout << "Error 404: File not found...\n";

}