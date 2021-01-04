#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <queue>

using namespace std;

struct node
{
	string Name;
	bool Visit;
	int Par;
};

struct edge
{
	int Length;
	int Origin;
	int Dest;
};

int converter(string s)
{
	stringstream conv(s);
	int x;
	conv >> x;
	return x;
};

int main()
{
	/* FILE READING */
	int n;
	ifstream read;
	read.open("q5.txt");

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
		vector<edge> rail;
		vector<vector<int> > vec_sets;

		int x = 0;
		while(!read.eof())
		{
			string rest_lines, a, b;
			getline(read, rest_lines);

			int colon = rest_lines.find(":"); // Gives position of colon

			a = rest_lines.substr(0, colon); // City
			/* MAKING TABLE OF STRUCTS */
			table[x].Name = a;
			table[x].Visit = 0;


			b = rest_lines.substr(colon+1);
			b.erase(remove(b.begin(), b.end(), ' '),b.end());

			/* PUT DISTANCES & INDEXES IN VECTOR */
			stringstream split(b);
			string token;

			while(getline(split,token,',')) // Seperate commas and put in a vector
			{
				string c, d;
				int semi = token.find(";");
				c = token.substr(1, semi);
				d = token.substr(semi+1);
				int len = converter(d);
				int org = converter(a.substr(1));
				int dst = converter(c);

				bool check_repeat = false;
				for(int i=0;i<rail.size();i++)
				{
					if(rail[i].Length == len && rail[i].Origin == dst && rail[i].Dest == org)
					{
						check_repeat = true;
					}
				}
				if(!check_repeat)
				{
					edge temp_rail;
					temp_rail.Length = len;
					temp_rail.Origin = org;
					temp_rail.Dest = dst;
					rail.push_back(temp_rail);
				}	
			}
			x++;
		}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        // Sorting the vector rail.
		for (int k = 0; k < rail.size()-1; k++) 
		{ 
        	int max = k; 
        	for (int j = k+1; j < rail.size(); j++) 
          		if (rail[j].Length > rail[max].Length) 
            		max = j; 
        	int temp = rail[max].Length;
        	int temp_org = rail[max].Origin;
        	int temp_dst = rail[max].Dest;
        	rail[max].Length = rail[k].Length;
        	rail[max].Origin = rail[k].Origin;
        	rail[max].Dest = rail[k].Dest;
        	rail[k].Length = temp;
        	rail[k].Origin = temp_org;
        	rail[k].Dest = temp_dst;
		}
		cout << "Rail\n";
		for(int i=0; i<rail.size(); i++)
		{
			cout << rail[i].Origin << " " << rail[i].Dest << " " << rail[i].Length << endl;
		}
		cout << endl;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		vector<edge> tracks;
		vector<edge> all_tracks;
		int z = rail.size()-1;
		while(1)
		{
			if(z<0)
			{
				cout << "Cant form Minimum Spanning Tree.\n";
				break;
			}
			int org = rail[z].Origin;
			int dst = rail[z].Dest;
			int len = rail[z].Length;
			if(table[org].Visit == 0 && table[dst].Visit == 0)
			{
				table[org].Visit = 1;
				table[dst].Visit = 1;
				tracks.push_back(rail[z]);

				vector<int> temp_set;
				temp_set.push_back(org);
				temp_set.push_back(dst);
				vec_sets.push_back(temp_set);

				edge temp_rail;
				temp_rail.Length = len;
				temp_rail.Origin = dst;
				temp_rail.Dest = org;
				all_tracks.push_back(temp_rail);
				all_tracks.push_back(rail[z]);

				rail.pop_back();
				z--;

			}
			else if(table[org].Visit == 0 && table[dst].Visit == 1)
			{
				table[org].Visit = 1;
				tracks.push_back(rail[z]);

				vector<int> temp_set;
				temp_set.push_back(org);

				for(int j=0;j<vec_sets.size();j++)
				{
					for(int k=0;k<vec_sets[j].size();k++)
					{
						if(dst == vec_sets[j][k])
						{
							vec_sets[j].insert(vec_sets[j].end(),temp_set.begin(),temp_set.end());
						}
					}
				}


				edge temp_rail;
				temp_rail.Length = len;
				temp_rail.Origin = dst;
				temp_rail.Dest = org;
				all_tracks.push_back(temp_rail);
				all_tracks.push_back(rail[z]);

				rail.pop_back();
				z--;
			}
			else if(table[org].Visit == 1 && table[dst].Visit == 0)
			{
				table[dst].Visit = 1;
				tracks.push_back(rail[z]);

				vector<int> temp_set;
				temp_set.push_back(dst);


				for(int j=0;j<vec_sets.size();j++)
				{
					for(int k=0;k<vec_sets[j].size();k++)
					{

						if(org == vec_sets[j][k])
						{
							vec_sets[j].insert(vec_sets[j].end(),temp_set.begin(),temp_set.end());
						}
					}
				}


				edge temp_rail;
				temp_rail.Length = len;
				temp_rail.Origin = dst;
				temp_rail.Dest = org;
				all_tracks.push_back(temp_rail);
				all_tracks.push_back(rail[z]);

				rail.pop_back();
				z--;
			}
			else if(table[org].Visit == 1 && table[dst].Visit == 1)
			{

				bool cycle = false;
				int sp_index;
				for(int j=0;j<vec_sets.size();j++)
				{
					for(int k=0;k<vec_sets[j].size();k++)
					{
						if(org == vec_sets[j][k])
						{
							sp_index=j;
							for(int k=0;k<vec_sets[j].size();k++)
							{
								if(dst == vec_sets[j][k])
								{
									cycle = true;
									rail.pop_back();
									z--;
									//break;
								}
							}
						}
					}
				}
				if(!cycle)
				{
					tracks.push_back(rail[z]);
					for(int j=0;j<vec_sets.size();j++)
					{
						for(int k=0;k<vec_sets[j].size();k++)
						{
							if(dst == vec_sets[j][k])
							{
								vec_sets[sp_index].insert(vec_sets[sp_index].end(),vec_sets[j].begin(),vec_sets[j].end());
								vec_sets[j].clear();
								//break;
								
							}
						}
					}
				}

			}
			bool visited = true;
			for(int i=0; i<n; i++)
			{
				if((!table[i].Visit))
				{
					visited = false;
					break;
				}
			}
/*
			for(int j=0;j<vec_sets.size();j++)
				{
					for(int k=0;k<vec_sets[j].size();k++)
					{
						cout << vec_sets[j][k] << " ";
					}
					cout << endl;
				}
				cout << endl;*/

			if(visited==1)
			{
				break;
			}


		}
		if(vec_sets.size()==2)
		{	
			bool found = false;
			int i;
			for(i=rail.size()-1;i>=0;i--)
			{
				if(find(vec_sets[0].begin(), vec_sets[0].end(), rail[i].Origin) != vec_sets[0].end())
				{
					if(find(vec_sets[1].begin(), vec_sets[1].end(), rail[i].Dest) != vec_sets[1].end())
					{
						found = true;
						break;
					}
				}
				else if(find(vec_sets[0].begin(), vec_sets[0].end(), rail[i].Dest) != vec_sets[0].end())
				{
					if(find(vec_sets[1].begin(), vec_sets[1].end(), rail[i].Origin) != vec_sets[1].end())
					{
						found = true;
						break;
					}
				}
			}
			if(found)
			{
				tracks.push_back(rail[i]);
			}
			vec_sets[0].insert(vec_sets[0].end(),vec_sets[1].begin(),vec_sets[1].end());
			vec_sets[1].clear();
		}

		/*for(int j=0;j<vec_sets.size();j++)
		{
			for(int k=0;k<vec_sets[j].size();k++)
			{
				cout << vec_sets[j][k] << " ";
			}
			cout << endl;
		}
		cout << endl;*/
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////////// Print
		cout << endl;
		cout << "Tracks\n";
		for(int i=0; i<tracks.size(); i++)
		{
			cout << tracks[i].Origin << " " << tracks[i].Dest << " " << tracks[i].Length << endl;
		}
		cout << endl;
		/*cout << "All Tracks\n";
		for(int i=0; i<all_tracks.size(); i++)
		{
			cout << all_tracks[i].Origin << " " << all_tracks[i].Dest << " " << all_tracks[i].Length << endl;
		}
		cout << endl;*/
		// PRINT MST 1
		cout << "MST 1: ";
		for(int i=0; i<tracks.size();i++)
		{
			cout << "(C" << tracks[i].Origin << ", C" << tracks[i].Dest << ") ";
		}
		cout << endl;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////////////////INPUT FROM USER
		int to, from, dist;
		cout << "Edge Added: (C#, C#) ";
		cin>> to >> from;
		cout << "Edge Length: ";
		cin>> dist;

		
		for(int i=0;i<n;i++)
		{
			table[i].Visit =0;
		}
		vector<int> dfs;
		vector<int> visited;
		table[to].Par = -1;
		dfs.push_back(to);
		int c=0;
		int ele = 1;
		while(1)
		{
			int curr = dfs[c];
			table[curr].Visit =1;
			if(curr == from)
				break;
			dfs.pop_back();
			ele--;
			int counter = 0;
			for(int i=0;i<tracks.size();i++)
			{
				if(tracks[i].Origin == curr && table[tracks[i].Dest].Visit!=1)
				{
					counter++;
					ele++;
					table[tracks[i].Dest].Par = curr;
					dfs.push_back(tracks[i].Dest);
				}
				else if(tracks[i].Dest == curr && table[tracks[i].Origin].Visit!=1)
				{
					counter++;
					ele++;
					table[tracks[i].Origin].Par = curr;
					dfs.push_back(tracks[i].Origin);
				}

			}
			c=ele - 1;
			if(!ele)
				break;
			//cout << "Do i break\n";

		}
		vector<int> bt;
		int e = from;
		bt.push_back(from);
		while(table[e].Par!=-1)
		{
			bt.push_back(table[e].Par);
			e = table[e].Par;
		}
		/////////////////////////// Print back tracking
		/*for(int i=0;i<bt.size();i++)
		{
			cout << bt[i] << " ";
		}
		cout << endl;*/
		int l = bt.size() -1;
		vector<edge> poss;
		for(int k=0;k<l;k++)
		{
			for(int i=0;i<tracks.size();i++)
			{
				if(tracks[i].Origin==bt[bt.size()-1] && tracks[i].Dest ==bt[bt.size()-2])
				{
					poss.push_back(tracks[i]);
					bt.pop_back();
				}
				else if(tracks[i].Origin==bt[bt.size()-2] && tracks[i].Dest == bt[bt.size()-1])
				{
					poss.push_back(tracks[i]);
					bt.pop_back();
				}
			}
		}
		/*for(int i=0;i<poss.size();i++)
		{
			cout << poss[i].Origin << " " << poss[i].Dest << endl;
		}*/

		/////////////////////SORT
		for (int k = 0; k < poss.size()-1; k++) 
		{ 
        	int max = k; 
        	for (int j = k+1; j < poss.size(); j++) 
          		if (poss[j].Length < poss[max].Length) 
            		max = j; 
        	int temp = poss[max].Length;
        	int temp_org = poss[max].Origin;
        	int temp_dst = poss[max].Dest;
        	poss[max].Length = poss[k].Length;
        	poss[max].Origin = poss[k].Origin;
        	poss[max].Dest = poss[k].Dest;
        	poss[k].Length = temp;
        	poss[k].Origin = temp_org;
        	poss[k].Dest = temp_dst;
		}
		/*for (int i = 0; i < poss.size();i++) 
		{ 
			cout << poss[i].Origin << " " << poss[i].Dest << endl;
		}*/
		if(dist < poss[poss.size()-1].Length)
		{
			int here = 0;
			for(int i=0;i<tracks.size();i++)
			{
				if(poss[poss.size()-1].Origin == tracks[i].Origin && poss[poss.size()-1].Dest == tracks[i].Dest)
				{
					here = i;
					break;
				}
			}
			tracks.erase(tracks.begin()+here);
			edge temp_rail;
			temp_rail.Length = dist;
			temp_rail.Origin = to;
			temp_rail.Dest = from;
			tracks.push_back(temp_rail);

		}
		cout << "MST 2: ";
		for(int i=0; i<tracks.size();i++)
		{
			cout << "(C" << tracks[i].Origin << ", C" << tracks[i].Dest << ") ";
		}
		cout << endl;

	}	
	else
    {
        cout << "File not found!" << endl;
    }
}