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
	read.open("q52.txt");

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
				if(!table[i].Visit)
				{
					visited = false;
					break;
				}
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

			if(visited)
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
		int to, from;
		cout << "Edge Removed: (C#, C#) ";
		cin>> to >> from;
		/////////////////////////// REMOVING EDGE FROM TRACKS
		int here = -1;
		for(int i=0;i<tracks.size();i++)
		{
			if((tracks[i].Origin == to && tracks[i].Dest == from)||(tracks[i].Origin == from && tracks[i].Dest == to))
			{
				here = i;
				break;
			}

		}
		for(int i=0;i<all_tracks.size();i++)
		{
			if(all_tracks[i].Origin == from && all_tracks[i].Dest == to)
			{
				all_tracks.erase(all_tracks.begin()+i);
				i--;
			}
			else if(all_tracks[i].Origin == to && all_tracks[i].Dest == from)
			{
				all_tracks.erase(all_tracks.begin()+i);
				i--;
			}
		}
		if(here==-1)
		{
			cout << "This Edge Isnt In The MST..." << endl;
		}
		else
		{
			tracks.erase(tracks.begin()+here);
			cout << "Tracks\n";
			for(int i=0; i<tracks.size(); i++)
			{
				cout << tracks[i].Origin << " " << tracks[i].Dest << " " << tracks[i].Length << endl;
			}
			cout << endl;
		/*	cout << "All Tracks\n";
			for(int i=0; i<all_tracks.size(); i++)
			{
				cout << all_tracks[i].Origin << " " << all_tracks[i].Dest << " " << all_tracks[i].Length << endl;
			}
			cout << endl;*/
			cout << "Rail\n";
			for(int i=0; i<rail.size(); i++)
			{
				cout << rail[i].Origin << " " << rail[i].Dest << " " << rail[i].Length << endl;
			}
			cout << endl;
		}
		/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		vector<int> one;
		vector<int> two;
		int cmp1 = to;
		int cmp2 = from;
		one.push_back(cmp1);
		int fst =0, snd =0;
		while(fst<one.size())
		{
			cmp1	 = one[fst];
			for(int i=0;i<all_tracks.size();i++)
			{
				if(all_tracks[i].Origin == cmp1)
				{
					if(find(one.begin(), one.end(), all_tracks[i].Dest) != one.end())
					{

					}
					else
						one.push_back(all_tracks[i].Dest);
				}
			}
			fst++;
		}
		///////////////////////////////////
		two.push_back(cmp2);
		while(snd<two.size())
		{
			cmp2 = two[snd];
			for(int i=0;i<all_tracks.size();i++)
			{
				if(all_tracks[i].Origin == cmp2)
				{
					if(find(two.begin(), two.end(), all_tracks[i].Dest) != two.end())
					{

					}
					else
						two.push_back(all_tracks[i].Dest);
				}
			}
			snd++;
		}
		/////////////////////////////////
		cout << "Component 1: ";
		for(int i=0;i<one.size(); i++)
		{
			cout << one[i] << " ";
		}
		cout << endl << "Component 2: ";
		for(int i=0;i<two.size(); i++)
		{
			cout << two[i] << " ";
		}
		cout << endl;
		////////////////////////////////////////////////MERGE BOTH VECTORS AND COMPARE WITH VEC SETS
		vector<int> merge;
		for(int i=0;i<one.size();i++)
		{
			merge.push_back(one[i]);
		}
		for(int i=0;i<two.size();i++)
		{
			merge.push_back(two[i]);
		}
		cout << endl;
		cout << "Merged: ";
		for(int i=0;i<merge.size();i++)
		{
			cout << merge[i] << " ";
		}
		cout << endl;
		vector<int> remaining;
		for(int i=0;i<vec_sets[0].size();i++)
		{
			if(find(merge.begin(), merge.end(), vec_sets[0][i]) != merge.end())
			{

			}
			else
				remaining.push_back(vec_sets[0][i]);
		}
		cout << "Remaining: ";
		for(int i=0;i<remaining.size();i++)
		{
			cout << remaining[i] << " ";
		}
		cout << endl;
		bool ones = false, twos = false;
		for(int i=0;i<remaining.size();i++)
		{
			for(int j=0;j<tracks.size();j++)
			{
				if(remaining[i]==tracks[j].Origin)
				{
					if(find(one.begin(), one.end(), tracks[j].Dest) != one.end())
					{
						ones = true;
						break;
					}
					if(find(two.begin(), two.end(), tracks[j].Dest) != two.end())
					{
						twos = true;
						break;
					}
				}
				else if(remaining[i]==tracks[j].Dest)
				{
					if(find(one.begin(), one.end(), tracks[j].Origin) != one.end())
					{
						ones = true;
						break;
					}
					if(find(two.begin(), two.end(), tracks[j].Origin) != two.end())
					{
						twos = true;
						break;
					}
				}
			}
			if(ones||twos)
			{
				break;
			}
		}
		cout << endl;
		if(twos)
		{
			for(int i=0;i<remaining.size();i++)
			{
				two.push_back(remaining[i]);
			}
		}
		else if(ones)
		{
			for(int i=0;i<remaining.size();i++)
			{
				one.push_back(remaining[i]);
			}
		}
		else
		{
			//cout << "I dont know what is happening...\n";
		}
		cout << "Component 1: ";
		for(int i=0;i<one.size(); i++)
		{
			cout << one[i] << " ";
		}
		cout << endl << "Component 2: ";
		for(int i=0;i<two.size(); i++)
		{
			cout << two[i] << " ";
		}
		cout << endl;
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		int y = rail.size()-1;
		bool done = false;
		while(!rail.empty())
		{

			if(find(one.begin(), one.end(), rail[y].Origin) != one.end())
			{
				if(find(one.begin(), one.end(), rail[y].Dest) != one.end())
				{
					rail.pop_back();
					y--;
				}
				else if(find(two.begin(), two.end(), rail[y].Dest) != two.end())
				{
					tracks.push_back(rail[y]);
					done = true;
					break;
				}
			}
			else if(find(two.begin(), two.end(), rail[y].Origin) != two.end())
			{
				if(find(two.begin(), two.end(), rail[y].Dest) != two.end())
				{
					rail.pop_back();
					y--;
				}
				else if(find(one.begin(), one.end(), rail[y].Dest) != one.end())
				{
					tracks.push_back(rail[y]);
					done = true;
					break;
				}
			}
			if(done)
				break;
		}
		// PRINT MST 2
		cout << "MST 2: ";
		bool no_mst = false;
		for(int j=0;j<vec_sets[0].size();j++)
		{
			no_mst = false;
			for(int i=0; i<tracks.size();i++)
			{
				if(vec_sets[0][j]==tracks[i].Origin || vec_sets[0][j]==tracks[i].Dest)
				{
					no_mst = true;
					break;
				}
				
			}
			if(!no_mst)
				break;
		}
		if(no_mst)
		{
			for(int i=0; i<tracks.size();i++)
			{
				cout << "(C" << tracks[i].Origin << ", C" << tracks[i].Dest << ") ";
			}
			cout << endl;
		}
		else
		{
			cout << "No possible MST can be formed....\n";
		}
		
	}	
	else
    {
        cout << "File not found!" << endl;
    }
}