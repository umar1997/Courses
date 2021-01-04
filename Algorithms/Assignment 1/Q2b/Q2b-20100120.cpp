/* First we read our file as we do in Part 2a, after feeding our inputs into an array of vectors, this time we make two extra arrays, one for
the number of incoming edges for each vertex and the outgoing for each vertex. Our first check is that when we go through all our incoming edges
if none of them is initially 0, then we have a cycle which just prints "No". If not a cycle then we look at the vertices with 0 incomings and put
them in the same row, then I remove that node from the graph meaning i remove all the edges with its outgoings. Now essentially it is as if that
node was never there and then I again look at the incoming edges, see which ones are 0 and put them in the same row. I do this until i have no 
vertices left after which i just print all the rows i pushed into a vector.*/

/* RUNNING TIME COMPLEXITY = O(m+n) */
/* SPACE COMPLEXITY = O(m+n) */

/* The running time complexity is O(m+n) because for every node n it visits all the people he has grudges with is m,
Where the space complexity is also O(m+n) because I have used an array of vector to store my inputs where the array is of size
n nodes and the vector holds all the people who that person has a grudge*/
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <queue>

using namespace std;

int converter(string s)
{
	stringstream conv(s);
	int x;
	conv >> x;
	return x;
}

struct node
{
	int Visited;
	string Person;
	int Parent;
	vector<string> Grudges;
};

struct vertice
{
	string Name;
	int Incoming;
};

struct vertex
{
	string Name;
	int Outgoing;
};
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{
	/* FILE READING */
	int n;
	ifstream read;
	read.open("text1.txt");
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

		vertice counter[n];
		vertex measurer[n];
		for(int j=0; j<n; j++)
		{
			counter[j].Incoming =0;
			measurer[j].Outgoing = 0;
		}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		int x = 0;
		while(!read.eof())
		{
				string rest_lines, a, b;
				getline(read, rest_lines);

				int colon = rest_lines.find(":"); // Gives position of colon

				a = rest_lines.substr(0, colon); // Person
				/* MAKING TABLE OF STRUCTS */
				table[x].Person = a;
				counter[x].Name = a;
				measurer[x].Name = a;
				cout << a << " ";
				table[x].Visited=0;
				table[x].Parent = -3;
				if(rest_lines.length()>2)
				{
					b = rest_lines.substr(colon+1,rest_lines.length()-1); // The grudges that person has.
					b.erase(remove(b.begin(), b.end(), ' '),b.end());


					/* PUT GRUDGES IN VECTOR */
					stringstream parosi(b);
					string token;

					while(getline(parosi,token,',')) // Seperate commas and put in a vector
					{
						cout << token << " ";
						table[x].Grudges.push_back(token);
						string s= token;
						s= s.substr(1,s.length());
						int f = converter(s);
						counter[f].Name = token;
						counter[f].Incoming++;
						measurer[x].Outgoing++;
					}

				}
                cout << endl;
				x++;
		}
        cout << endl;
		for(int j=0; j<n; j++)
		{
			cout << counter[j].Name << " ";
		}
		cout << endl;
		cout << "Incoming: " <<endl;
		for(int j=0; j<n; j++)
		{

			cout << counter[j].Incoming << " ";
		}
		cout << endl;
		cout << "Outgoing: " <<endl;
		for(int j=0; j<n; j++)
		{

			cout << measurer[j].Outgoing << " ";
		}
		cout << endl << endl;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool cycle = true;
		for(int i=0; i<n; i++)
		{
			if(counter[i].Incoming == 0)
			{
				cycle = false;
			}
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		if(!cycle)
		{
				queue<string> qu, pr;
				vector<int> v;
				int index, chk = 0;
				// Find the edge with 0 incoming
				for(int i=0; i<n; i++)
				{
					if(!counter[i].Incoming)
					{
					    index = i;
				    	v.push_back(index);
					}
				}
				if(v.size()==1)
				{
					qu.push(table[index].Person);
					pr.push(table[index].Person);
					chk++;
				}
				else
				{
					string h ="";
					for(int i=0; i<v.size(); i++)
					{
						h += table[v[i]].Person + " ";
						chk++;
					}
					qu.push(h);
					pr.push(h);
				}
				v.clear();
				while(1)
				{
					qu.pop();
					int f;
					for(int i=0;i<table[index].Grudges.size(); i++)
					{
						string s = table[index].Grudges[i];
						s= s.substr(1,s.length());
						f = converter(s);
						counter[f].Incoming--;
						if(!counter[f].Incoming)
						{
							v.push_back(f);
						}

					}
					if(v.size()==1)
					{
						qu.push(table[f].Person);
						pr.push(table[f].Person);
						chk++;
					}

					else
					{
						string h ="";
						for(int i=0; i<v.size(); i++)
						{

							h += table[v[i]].Person + " ";
							chk++;
						}
						qu.push(h);
						pr.push(h);
					}
					v.clear();
					table[index].Grudges.clear();
					string s = qu.front();
					s= s.substr(1,s.length());
					int y = converter(s);
					index = y;
					if(chk == n)
						break;

				}
		        cout << "Yes" << endl;
		        cout << pr.size() << endl;
		        int sze = pr.size();
				for(int i =0; i<sze; i++)
				{
				   cout << pr.front() << endl;
				   pr.pop();

				}
		}
		else///////////////////////////////////////////////// CYCLE ///////////////////////////////////////////////////////////
		{
			cout << "No" << endl;
		}

	}
	else
	{
		cout << "Error 404 File not found!" << endl;
	}
	read.close();
}
