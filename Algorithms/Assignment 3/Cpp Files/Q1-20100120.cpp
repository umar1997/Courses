/*
Time Complexity is O(n^2)

Since we are traversing a 2D array for preference lists.
First list is for planes and second list is for airports.
And then I make another 2D array which checks each preference on each day.

It pops each airport from a plane. If the airport does not already have a plane assigned the assigns it.
Else it compares the higher preference plane in the airport list.
It does this until the total number of airports assigned are equal to number of planes.
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
	int Sizes;
	string Name;
	int Index;
	vector<int> List;
};
struct the_X
{
	vector<int> P;
	vector<int> A;
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
///////////////////////////////////////////////////////////////////////////////////////////
	/*FILE READING*/
	int n;
	ifstream read;
	read.open("q12.txt");

	if(read.is_open())
	{
		// Getting the no. of total vertices
		string first_line, loop_no;
		getline(read, first_line);
		loop_no = first_line.substr(2);
		stringstream loop(loop_no);
		loop >> n;
		// Making Array of Structs
		node plane[n];
		node airport[n];
		node terminal[n];
		the_X invalid[1];

		for(int i=0; i<n; i++)
		{
			string rest_lines, a, b;
			getline(read, rest_lines);

			int colon = rest_lines.find(":"); // Gives position of colon
			a = rest_lines.substr(0, colon); // plane

			plane[i].Name = a;
			plane[i].Index = conv(a.substr(1, colon));
			plane[i].Sizes = 0;


			b = rest_lines.substr(colon+1); // Airports
			b.erase(remove(b.begin(), b.end(), ' '),b.end());
			b.erase(remove(b.begin(), b.end(), 'A'),b.end());

			stringstream split(b);
			string token;
			while(getline(split,token,',')) // Seperates from the comma
			{
				plane[i].List.push_back(conv(token));
			}

		}
		for(int i=0; i<n; i++)
		{
			string rest_lines, a, b;
			getline(read, rest_lines);

			int colon = rest_lines.find(":"); // Gives position of colon
			a = rest_lines.substr(0, colon); // plane

			airport[i].Name = a;
			airport[i].Index = conv(a.substr(1, colon));
			airport[i].Sizes = 0;
			terminal[i].Name = a;
			terminal[i].Index = conv(a.substr(1, colon));
			terminal[i].Sizes = 0;


			b = rest_lines.substr(colon+1); // Airports
			b.erase(remove(b.begin(), b.end(), ' '),b.end());
			b.erase(remove(b.begin(), b.end(), 'P'),b.end());

			stringstream split(b);
			string token;
			while(getline(split,token,',')) // Seperates from the comma
			{
				airport[i].List.push_back(conv(token));
			}
		}
		while(!read.eof())
		{
			string a;
			getline(read, a);
			int colon = a.find(":"); // Gives position of colon
			a = a.substr(colon+1);
			a.erase(remove(a.begin(), a.end(), ' '),a.end());
			a.erase(remove(a.begin(), a.end(), 'P'),a.end());

			stringstream split(a);
			string token;
			while(getline(split,token,',')) // Seperates from the comma
			{
				int colon = token.find("A");
				invalid[0].P.push_back(conv(token.substr(0,colon)));
				invalid[0].A.push_back(conv(token.substr(colon+1)));
			}

		}
///////////////////////////////////////////////////////////////////////////////////////////
		//////////////Print
		for (int i = 0; i < n; ++i)
		{
			cout << plane[i].Name << " " << plane[i].Index << ": ";
			for (int j = 0; j < plane[i].List.size(); ++j)
			{
				cout << "A" << plane[i].List[j] << " ";
			}
			cout << endl;
		}
		cout << endl;
		for (int i = 0; i < n; ++i)
		{
			cout << airport[i].Name << " " << airport[i].Index << ": ";
			for (int j = 0; j < airport[i].List.size(); ++j)
			{
				cout << "P" << airport[i].List[j] << " ";
			}
			cout << endl;
		}
		cout << endl << "P: ";
		for (int i = 0; i < invalid[0].P.size(); ++i)
		{
			cout << invalid[0].P[i] << " ";
		}
		cout << endl << "A: ";
		for (int i = 0; i < invalid[0].A.size(); ++i)
		{
			cout << invalid[0].A[i] << " ";
		}
		cout << endl << endl;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/*THE HUGE ASS FOR LOOP*/
		//cout << invalid[0].P[0] << " " << invalid[0].A[0] << endl;
		vector<int> filler;
		vector<int> temp;
		int invalid_size = invalid[0].A.size();
		for (int j= 0; j < n; j++)
		{
			int term_ind = plane[j].List[0]; // Finding the the index where the P must go to.
			for (int l = 0; l < invalid[0].A.size(); ++l)
			{
				if(term_ind == invalid[0].A[l] && j+1 == invalid[0].P[l])
				{
					filler.push_back(j+1);
				}
				else
				{
					if(find(terminal[term_ind-1].List.begin(), terminal[term_ind-1].List.end(), j+1) == terminal[term_ind-1].List.end())
					{
						terminal[term_ind-1].List.push_back(j+1); // Going to that index of A and putting all the P's whose preference is that.
						terminal[term_ind-1].Sizes++;
					}
				}
			}
		}
		cout << endl << endl;
		/////////////////////////
		int i = 1;
		/////////////////////////////////////////////////////////////////////////////////////
		/*cout << "DAY: " << i << endl;
		for (int z = 0; z < n; ++z)
		{
			cout << z+1 << " : ";
			for (int k = 0; k < terminal[z].Sizes; ++k)
			{
				cout << terminal[z].List[k] << " ";
			}
			cout << endl;
		}
		cout << endl;*/
		////////////////////////////////////////////////////////////////////////////////////
		while(1) // To look at all the planes preferences
		{
			for (int j = 0; j < n; ++j) // To go through all the planes, airports and terminals
			{

				if(i>1)
				{
					int filler_size = filler.size();
					for (int k = 0; k < filler_size; ++k) // Going through elements left in the filler
					{
						int term_ind = plane[filler[k]-1].List[i-1];
						for (int h = 0; h < invalid_size; ++h) // Invalid loop
						{
							if(term_ind == invalid[0].A[h] && filler[k] == invalid[0].P[h])
							{
								if(find(temp.begin(), temp.end(), filler[k]) == temp.end())
									temp.push_back(filler[k]);
							}
							else
							{
								if(find(terminal[term_ind-1].List.begin(),terminal[term_ind-1].List.end(), filler[k]) == terminal[term_ind-1].List.end())
								{
									terminal[term_ind-1].List.push_back(filler[k]); // Going to that index of A and putting all the P's whose preference is that.
									terminal[term_ind-1].Sizes++;
								}
							}
						}
					}
					filler.clear();
					for (int k = 0; k < temp.size(); ++k)
					{
						filler.push_back(temp[k]);
					}
					temp.clear();
				}
				/////////////////////////////////////////////////////////////////////////////////////
				/*cout << "DAY: " << i+1 << endl;
				cout << "Filler Size: " << filler.size() << endl;
				for (int k = 0; k < filler.size(); ++k)
				{
					cout << filler[k] << " ";
				}
				cout << endl;
				for (int z = 0; z < n; ++z)
				{
					cout << z+1 << " : ";
					for (int k = 0; k < terminal[z].Sizes; ++k)
					{
						cout << terminal[z].List[k] << " ";
					}
					cout << endl;
				}
				cout << endl;*/
				/////////////////////////////////////////////////////////////////////////////////////
				if(terminal[j].Sizes>1)
				{
					for (int k = 0; k < terminal[j].Sizes; ++k)// Going through terminal entries
					{
						filler.push_back(terminal[j].List[k]);
					}
					terminal[j].Sizes = 0;
					terminal[j].List.clear();

					bool check_break = false;
					int filler_size = filler.size();
					for (int k = 0; k < n; ++k) // Go through airport preferences
					{
						for (int f = 0; f < filler_size; ++f) // Go through elements in the filler
						{
							if(filler[f]==airport[j].List[k])
							{
								//cout << "This is : " << filler[f] << endl;
								terminal[j].List.push_back(filler[f]);
								terminal[j].Sizes++;
								filler.erase(filler.begin()+f);
								check_break = true;
								break;
							}	
						}
						if(check_break)
							break;
					}
				} // For terminal sizes greater than one ends
			} // Where j ends
			/////////////////////////////////////////////////////////////////////////////////////
			/*cout << "THE  OUTSIDE J DAY: " << i+1 << endl;
			cout << "Filler Size: " << filler.size() << endl;

			for (int z = 0; z < n; ++z)
			{
				cout << z+1 << " : ";
				for (int k = 0; k < terminal[z].Sizes; ++k)
				{
					cout << terminal[z].List[k] << " ";
				}
				cout << endl;
			}
			cout << endl;*/
			/////////////////////////////////////////////////////////////////////////////////////
			bool check_fin = true;
			for (int k = 0; k < n; ++k)
			{
				if(terminal[k].List.size()!=1)
				{
					check_fin = false;
					break;
				}
			}
			if(check_fin)
				break;
			i++;
		} // Where i ends

		cout << "Stable Matching: " << endl;
		for (int i = 0; i < n; ++i)
		{
			cout << "(A"<<i+1 << ", P" << terminal[i].List[0] << ")\n"; 
		}
	}
	else
	{
		cout << "File not found!" << endl;
	}
}
