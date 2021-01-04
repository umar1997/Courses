/* Firstly I read the file and stored all the Chemicals in an array of structs. My struct consisted of a Visit (which tells if the node was visited), a Chemical (Which was the specific chemical),
a Colour(Which was given one of two colours), a Parent (From where the BFS previously came from), a Neighbour vector (Which had the Chemicals which the chemicals react with). I run a BFS which takes the
first chemical C0 and marks it visited and colours its neighbours the opposite of its colour and store its neighbours in a queue from the Neighbours vector. We then traverse to the first chemical in the
queue. We do the same for that chemical as we mark it visited and colour its neighbours the opposite colour. And put its neighbours in the queue. Then again we check the front of the queue. While doing this 
I put the two different colours in two different vectors. When all my chemicals are visited then I print both coloured vectors. IF while colouring a neighbour, that neighbour is already coloured with the same 
colour as the chemical then we have a conflict and check cycle true. When check cycle is true I back track by using the Parent sturct in  the node. I take both nodes in conflict and store their Parents in a vectors
and when both parents are the same I stop my backtracking and I print the vectors which have the path of my cycle.*/

/* RUNNING TIME COMPLEXITY = O(m+n) */
/* SPACE COMPLEXITY = O(m+n) */

/* The running time complexity is O(m+n) because for every node n it visits all the chemicals that react with it which is m,
which I run by BFS which is O(m+n), hence the time complexity also being O(m+n). For the space complexity is also O(m+n) because
I have used an array of vector to store my inputs where the array is of size n nodes and the vector holds all the chemicals that
react with it which are m chemicals*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <iterator>
#include <list>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

struct node
{
	int Visited;
	string Colour;
	string Chemical;
	int Parent;
	vector<string> Neighbour;
};

int converter(string s)
{
	stringstream conv(s);
	int x;
	conv >> x;
	return x;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	/* FILE READING */
	int n;
	ifstream read;
	read.open("text4.txt");
	if(read.is_open())
	{
		// Getting the no. of total vertices
		string first_line, loop_no;
		getline(read, first_line);
		loop_no = first_line.substr(2);
		stringstream loop(loop_no);
		loop >> n;

		/* MAKING ARRAY OF STRUCTS*/
		node table[n];
		/* MAKE THE LINK LIST */
		list <string> chemlist;
		/* MAKE VECTOR OF LINK LIST */
		vector<list<string> > cl;

		int x = 0;
		while(!read.eof())
		{
				string rest_lines, a, b;
				getline(read, rest_lines);

				int colon = rest_lines.find(":"); // Gives position of colon
				// Dividing the string from the colon
				a = rest_lines.substr(0, colon); // Chemical
				b = rest_lines.substr(colon+1,rest_lines.length()-1); // That chemicals neighbours
				b.erase(remove(b.begin(), b.end(), ' '),b.end());


				/* PUT CHEMICALS IN VECTOR */
				vector<string> s;
				stringstream parosi(b);
				string token;
				s.push_back(a);

				while(getline(parosi,token,',')) // Seperate commas and put each reacting chemical in a vector
				{
					s.push_back(token);
					table[x].Neighbour.push_back(token);
				}

				/* MAKING TABLE OF STRUCTS */
				table[x].Visited=0;
				table[x].Colour = "R";
				table[x].Chemical = a;
				table[x].Parent = -3;

				for(int j=0; j<s.size();j++)
				{
				    cout << s[j] << " ";
					chemlist.push_back(s[j]);
				}
				cout << endl;
				cl.push_back(chemlist);
				x++;
		}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Get the first Chemicals Index
		string first_chem = cl[0].front().substr(1,cl[0].front().length()-1);
		int index = converter(first_chem);


		queue<int> qu;
		vector<string> white, black;
		string clr = "W";
		white.push_back(table[index].Chemical);
		table[index].Colour = clr;
		table[index].Parent = -1;
		int check_list = 0;
		int par1, par2;
		bool check_cycle = false;
		vector<string> cyc1, cyc2;
		// The while loop that does all the magic
		while(1)
		{
                table[index].Visited = 1;
                check_list++;
				for(int i=0; i<table[index].Neighbour.size();i++)
				{
				    string s= table[index].Neighbour[i];
				    s= s.substr(1,s.length());
					int temp;
					temp = converter(s);

					if(!table[temp].Visited)
					{
						qu.push(temp);
						if(clr == "W")
						{
							if(table[temp].Colour == "W") // && Parent != -3
							{
								check_cycle = true;
								par1= index;
								par2= temp;
								break;
							}
							table[temp].Colour = "B";
							black.push_back(table[temp].Chemical);
						}
						else if(clr == "B")
						{
							if(table[temp].Colour == "B") // && Parent != -3
							{
								check_cycle = true;
								par1= index;
								par2= temp;
								break;
							}
							table[temp].Colour = "W";
							white.push_back(table[temp].Chemical);
						}

					}

					table[temp].Parent = index;

				}

				if(check_cycle)
					break;
				index = qu.front();
				qu.pop();
				if(table[index].Colour=="W")
	                clr = "W";
	            else if(table[index].Colour=="B")
	                clr = "B";

				if(check_list == n)
					break;
		}
		if(!check_cycle)
        {
        	cout << "Yes\n";
        	cout << "Colour 1: ";
			for(int i=0;i<white.size();i++) cout << white[i] << " ";
			cout << endl;
			cout << "Colour 2: ";
			for(int i=0;i<black.size();i++) cout << black[i] << " ";
		}
		else if(check_cycle)
		{
			cyc1.push_back(table[par1].Chemical);
			cyc2.push_back(table[par2].Chemical);
			while(1)
			{
				par1 = table[par1].Parent;
				par2 = table[par2].Parent;
				cyc1.insert(cyc1.begin(), table[par1].Chemical);
				cyc2.push_back(table[par2].Chemical);
				if(par1 == par2)
					break;

			}
			cout << "No" << endl;
			for(int i=0; i<cyc1.size();i++)
			{
				cout << cyc1[i] << "->";
			}
			for(int i=0; i<cyc2.size();i++)
			{
			    if(i==cyc2.size()-1)
                    cout << cyc2[i];
                else
                    cout << cyc2[i] << "->";
			}
		}

	}
	else
	{
		cout << "Error 404 File not found!" << endl;
	}
	read.close();
}
