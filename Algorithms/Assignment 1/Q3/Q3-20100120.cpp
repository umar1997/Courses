/* In Q3 the file reading was a little different than that of Q1 and Q2, In this we additionally had to store the distance of the edges between the two edges.
this was more or less done the smae way with a few changes. I sorted my inputs in an array of structs whose one compartment was a vector of structs.So I had an
array of nodes which had a vector Routes which was of type edges another struct. In my node I stored the weight of my node(accumulated shortest distance from source),
the Parent from where it came, a bool visit and a vector Routes of type edges which had the disance between both nodes and the number of that node to help index.
We then use Dijkstras algorithm to find the shortest path between both nodes. For the scenic spot we first traverse from the Source to scenic spot by Dijkstras algo 
and then from the scenic spot to the friends destination after which I calculate the 20% margin. To display both shortest path I use help from my struct compartment 
which has the Parent of that node and backtrack my path to the source and then print the path.*/

/* RUNNING TIME COMPLEXITY = O(n^2) */
/* SPACE COMPLEXITY = O(m+n) */

/* The running time complexity is O(n^2) because for every node n it visits all the nodes again to see which node has the lowest
weight,Whereas the space complexity is O(m+n) because I have used an array of vector to store my inputs where the array is of size
n nodes and the vector holds vertices who have edges connected to it which are m edges*/
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <queue>
#include <climits>

using namespace std;

struct edges
{
	string Neighbor;
	int Neigh;
	int Distance;
};

struct node
{
	int Weight;
	int Parent;
	string City;
	bool Visit;
	vector<edges> Routes;
};

int converter(string s)
{
	stringstream conv(s);
	int x;
	conv >> x;
	return x;
}

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

		/* PUTTING INPUTS IN MY DATA STRUCTURE */
		int x = 0;
		while(!read.eof())
		{
				string rest_lines, a, b;
				getline(read, rest_lines);

				int colon = rest_lines.find(":"); // Gives position of colon

				a = rest_lines.substr(0, colon); // City
				/* MAKING TABLE OF STRUCTS */
				table[x].City = a;
				table[x].Weight=100000;
				table[x].Visit = 0;

				if(rest_lines.length()>2)
				{
					b = rest_lines.substr(colon+1,rest_lines.length()-1); // The grudges that person has.
					b.erase(remove(b.begin(), b.end(), ' '),b.end());

					/* PUT GRUDGES IN VECTOR */
					stringstream split(b);
					string token;

					/* MAKE THE STRUCT VECTOR*/
					edges temp_edge;
					while(getline(split,token,',')) // Seperate commas and put in a vector
					{
						string c, d, e;
						int semi = token.find(";");
						c = token.substr(0, semi);
						e = c.substr(1, semi);
						d = token.substr(semi+1,token.length()-1);
						int no = converter(d);
						int no2 = converter(e);

						temp_edge.Neigh = no2;
						temp_edge.Distance = no;
						temp_edge.Neighbor = c;
						table[x].Routes.push_back(temp_edge);

					}

				}
				x++;
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/* PRINTING */
		for(int i = 0; i<n; i++)
		{
			cout << "City: " << table[i].City << " Weight: " << table[i].Weight << " Visit: " << table[i].Visit << endl;
			for(int j=0; j<table[i].Routes.size(); j++)
			{
				cout << table[i].Routes[j].Neighbor << "->" << table[i].Routes[j].Neigh << " "<< table[i].Routes[j].Distance << " ";
			}
			cout << endl;
		}
		cout << endl;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		vector<string> ab, axb; 
		int ind, dst, ss, j, k, l;
		string city_A, city_B, city_X;
		cout << "Home City    : ";
		cin >> city_A;
		cout << "Friend's City: ";
		cin >> city_B;
		cout << "Scenic Spot  : ";
		cin >> city_X;
		ind = converter(city_A.substr(1, city_A.length()-1));
		dst = converter(city_B.substr(1, city_B.length()-1));
		ss = converter(city_X.substr(1, city_X.length()-1));
		j = ind;
		k = dst;
		l = ss;
		// DIJKSTRAS ALGO
		vector<string> v;
		table[ind].Weight = 0;
		table[ind].Parent = -1;
		int min;


		while(1)
		{
			table[ind].Visit = 1;
			v.push_back(table[ind].City);
            int g = table[ind].Routes.size();
			for(int i =0; i<table[ind].Routes.size(); i++)
			{
				int temp = table[ind].Routes[i].Neigh;
				if(table[temp].Weight > table[ind].Weight + table[ind].Routes[i].Distance)
				{
				    int sum = table[ind].Weight + table[ind].Routes[i].Distance;
					table[temp].Weight = table[ind].Weight + table[ind].Routes[i].Distance;
					table[temp].Parent = ind;
				}
			}
            table[ind].Weight = 111111;
            min = table[ind].Weight;
			for(int j=0; j<n; j++)
			{
				if(!table[j].Visit && table[j].Weight < min)
				{
					min = table[j].Weight;
					ind = j;
				}
			}
			table[ind].Visit = 1;
			v.push_back(table[ind].City);
			if(ind==dst)
				break;
		}
		/*GETTING THE PATH*/
		ab.push_back(table[ind].City);
		while(1)
		{
			int temp;
			temp = table[ind].Parent;
			ind = table[ind].Parent;
			ab.push_back(table[temp].City);
			if(ind==j)
				break;
		}
		
		int aTOb = table[dst].Weight;

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		ind = j;
		dst = k;
		ss = l;
		for(int i = 0; i<n; i++)
		{
			table[i].Weight = 100000;
			table[i].Visit = 0;
		}

		table[ind].Weight = 0;
		table[ind].Parent = -1;
		min = 999999;


		while(1)
		{
			table[ind].Visit = 1;
			v.push_back(table[ind].City);
            int g = table[ind].Routes.size();
			for(int i =0; i<table[ind].Routes.size(); i++)
			{
				int temp = table[ind].Routes[i].Neigh;
				if(table[temp].Weight > table[ind].Weight + table[ind].Routes[i].Distance)
				{
				    int sum = table[ind].Weight + table[ind].Routes[i].Distance;
					table[temp].Weight = table[ind].Weight + table[ind].Routes[i].Distance;
					table[temp].Parent = ind;
				}
			}
            table[ind].Weight = 111111;
            min = table[ind].Weight;
			for(int j=0; j<n; j++)
			{
				if(!table[j].Visit && table[j].Weight < min)
				{
					min = table[j].Weight;
					ind = j;
				}
			}
			table[ind].Visit = 1;
			if(ind==ss)
				break;
		}
		/*GETTING THE PATH*/
		axb.push_back(table[ind].City);
		while(1)
		{
			if(ind==j)
				break;
			int temp;
			temp = table[ind].Parent;
			ind = table[ind].Parent;
			axb.push_back(table[temp].City);
		}
		reverse(axb.begin(),axb.end());
		int aTOx = table[ss].Weight;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		ind = j;
		dst = k;
		ss = l;
		for(int i = 0; i<n; i++)
		{
			table[i].Weight = 100000;
			table[i].Visit = 0;
		}

		int swap;
		swap = ss;
		ind = swap;
		ss = ind;
		table[ind].Weight = 0;
		table[ind].Parent = -1;
		min = 999999;


		while(1)
		{
			table[ind].Visit = 1;
			v.push_back(table[ind].City);
            int g = table[ind].Routes.size();
			for(int i =0; i<table[ind].Routes.size(); i++)
			{
				int temp = table[ind].Routes[i].Neigh;
				if(table[temp].Weight > table[ind].Weight + table[ind].Routes[i].Distance)
				{
				    int sum = table[ind].Weight + table[ind].Routes[i].Distance;
					table[temp].Weight = table[ind].Weight + table[ind].Routes[i].Distance;
					table[temp].Parent = ind;
				}
			}
            table[ind].Weight = 111111;
            min = table[ind].Weight;
			for(int j=0; j<n; j++)
			{
				if(!table[j].Visit && table[j].Weight < min)
				{
					min = table[j].Weight;
					ind = j;
				}
			}
			table[ind].Visit = 1;
			if(ind==dst)
				break;
		}
		/*GETTING THE PATH*/
		vector<string> b2x;
		b2x.push_back(table[ind].City);
		while(1)
		{
			if(ind==l)
				break;
			int temp;
			temp = table[ind].Parent;
			ind = table[ind].Parent;
			b2x.push_back(table[temp].City);
		}
		reverse(b2x.begin(),b2x.end());
		for(int i=1; i<b2x.size(); i++)
		{
			axb.push_back(b2x[i]);
		}
		int xTOb = table[dst].Weight;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		cout << endl;
		cout << "Shortest Distance: " << aTOb << endl;
		cout << "From Host City to Scenic Spot: " << aTOx << endl;
		cout << "From Scenic Spot to Friend's City: " << xTOb << endl;
		int total = aTOx + xTOb;
		cout << "Total via Scenic Spot: " << total << endl;
		double final = 1.2*aTOb;
		cout << "At max 20\% of Shortest Distance: " << final << endl;
		if(total > final)
		{
			cout << total << ">" << final << endl;
			cout << "It is more than 20\% of the shortest distance from Ca to Cb\n";
		}
		else
		{
			cout << total << "<=" << final << endl;
			cout << "It is NOT more than 20\% of the shortest distance from Ca to Cb\n";
		}
		cout << endl << endl << "Shortest Path: ";
		for(int i=ab.size()-1; i>=0; i--)
		{	
			if(!i)
				cout << ab[i];
			else
				cout << ab[i] << "->";
		}
		cout << endl << endl << "Shortest Path with Scenic Spot: ";
		for(int i=0; i<axb.size(); i++)
		{	
			if(i==axb.size()-1)
				cout << axb[i];
			else
				cout << axb[i] << "->";
		}


	}
	else
    {
        cout << "File not found!" << endl;
    }
}
