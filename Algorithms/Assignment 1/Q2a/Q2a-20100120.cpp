/* I first read all the file and stored the People in an array of structs. The struct node included a Visited(Which tells if we have landed on the node),
a Person(The specific person), a Parent (The node that we previously visited), Grudges vector (Which has all the people we have grudges with). Then I make
two other arrays which hold the count for both incoming and outgoing edges. We then check the incoming edges if any single one has the count 0 incoming edges 
then I wont have a cycle and for that case I make a queue which pushes the nodes with incoming 0 and removes all of its edges with its neighbours. Then we 
decrement the incoming of that nodes outgoing. The next node whose incoming then becomes 0 is pushed in the queue and the process is continued. For the case 
where there is a cycle I remove all nodes with 0 outgoings and all edges going to it. That essentially means all the nodes that are left will always be a cycle 
and we can start from any node and push it in a vector and when that node is visited twice then we print the path of the cycle by printing the whole vector*/

/* RUNNING TIME COMPLEXITY = O(m+n) */
/* SPACE COMPLEXITY = O(m+n) */

/* The running time complexity is O(m+n) because we are visiting each node n in our queue and for each vertex you are visiting
each of its outgoing edge which is m. Where the space complexity is also O(m+n) because I have used an array of vector to store 
my inputs where the array is of size n nodes and the vector holds all the people who that person has a grudge with*/

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
	read.open("text3.txt");
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
		
        cout << endl;int x = 0;
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
				queue<int> qu;
				vector<string> v;
				int index;
				// Find the edge with 0 incoming
				for(int i=0; i<n; i++)
				{
					if(!counter[i].Incoming)
					{
					    index = i;
						qu.push(index);
					}
				}
				int par = -1,chk_lst = 0;
				while(1)
				{

		            index = qu.front();
					qu.pop();

					table[index].Visited = 1;
					table[index].Parent = par;
					for(int i=0;i<table[index].Grudges.size(); i++)
					{
						string s = table[index].Grudges[i];
						s= s.substr(1,s.length());
						int f = converter(s);
						counter[f].Incoming--;
						if(!counter[f].Incoming)
						{
							qu.push(f);
						}

					}
					table[index].Grudges.clear();
					v.push_back(table[index].Person);
					par = index;
					chk_lst++;

					if(chk_lst == n)
						break;


				}
		        cout << "Yes" << endl;
				for(int i =0; i<v.size(); i++)
				{
				    if(i==v.size()-1)
		            {
		                cout << v[i];
		            }
		            else
		            {
		                cout << v[i] << "->";
		            }

				}
		}
		else///////////////////////////////////////////////// CYCLE ///////////////////////////////////////////////////////////
		{
				vector<int> exc;
				for(int i=0; i<n; i++)
				{
					if(!measurer[i].Outgoing)
					{
						exc.push_back(i);
					}
				}
				// REMOVE EDGES FROM OTHER VERTICE TO VERTICE WITH 0 OUTGOING
				for(int i=0; i<n; i++)
				{
					int z = table[i].Grudges.size();
					for(int j=0; j<z; j++)
					{
						for(int k=0; k<exc.size(); k++)
						{

							string s = table[i].Grudges[j];
							s= s.substr(1,s.length());
							int f = converter(s);
							if(f==exc[k])
							{
								for(int p=j;p<(z-1);p++)
								{
									table[i].Grudges[p]=table[i].Grudges[p+1];
								}
								table[i].Grudges.pop_back();
							}
						}
					}
				}
				/*for(int i=0; i<table[1].Grudges.size(); i++)
				{
					cout << table[1].Grudges[i] << " ";
				}*/
				int index; // FIND WHERE TO START
				for(int i=0; i<n; i++)
				{
					if(measurer[i].Outgoing != 0)
					{
						index = i;
						break;
					}

				}
				int par = -1;
				vector<int> stack;

				while(1)
				{
					table[index].Parent = par;
					table[index].Visited++;
					stack.push_back(index);
					if(table[index].Visited==2)
					{
						break;
					}
					string s = table[index].Grudges[0];
					s= s.substr(1,s.length());
					int f = converter(s);
					index = f;
					par = index;
				}
				cout << "No" << endl;
				for(int i=0; i<stack.size(); i++)
				{
					if(i==stack.size()-1)
		            {
		                cout << table[stack[i]].Person;
		            }
		            else
		            {
		                cout << table[stack[i]].Person << "->";
		            }
					
				}
		}

	}
	else
	{
		cout << "Error 404 File not found!" << endl;
	}
	read.close();
}
