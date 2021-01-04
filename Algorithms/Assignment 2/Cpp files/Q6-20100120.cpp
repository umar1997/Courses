#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <queue>

using namespace std;

struct node
{
	int index;
	int no_of_x;
};

int conv(string s)
{
	stringstream conv(s);
	int x;
	conv >> x;
	return x;
}
int convch(char s)
{
	int x = (int)s - 48;
	return x;
}

int main()
{
	/*FILE READING*/
	int n;
	ifstream read;
	read.open("q6.txt");
	if(read.is_open())
	{
		string first_line, loop_no;
		getline(read, first_line);
		n = conv(first_line.substr(2));

		////////////////////// Initialize Confirm Vector
		vector<int> cfrm(n);
		for(int i=0;i<cfrm.size(); i++)
		{
			cfrm[i]=-1;
		}
		////////////////////// Put in vector lines
		vector<string> lines;
		while(!read.eof())
		{
			string read_line;
			getline(read, read_line);
			lines.push_back(read_line);
		}
		////////////////////// Print the file
		/*for(int i=0;i<lines.size();i++)
		{
			cout << lines[i] << endl;
		}*/
		////////////////////// Create the box array
		vector<node> box(lines.size());
		cout << "No of x\n";
		for(int i=0;i<lines.size();i++)
		{
			int count =0;
			string curr_line = lines[i];
			while(1)
			{
				int xs = curr_line.find("x");
				if(xs==-1)
					break;
				curr_line = curr_line.substr(xs+1);
				count++;

			}
			cout << lines[i] << " | " << count << endl;
			box[i].no_of_x = count;
			box[i].index = i;
		}
		////////////////////// Sort the box to get least x ones
		cout << endl;
		for (int k = 0; k < box.size()-1; k++) 
		{ 
        	int max = k; 
        	for (int j = k+1; j < box.size(); j++) 
          		if (box[j].no_of_x > box[max].no_of_x) 
            		max = j; 
        	int temp = box[max].index;
        	int temp_x = box[max].no_of_x;
        	box[max].index = box[k].index;
        	box[max].no_of_x = box[k].no_of_x;
        	box[k].index = temp;
        	box[k].no_of_x = temp_x;
		}
		/////////////////// Print the sorted box
		cout << "Number of x ----- Index in Lines\n";
		for (int i = 0; i < box.size(); ++i)
		{
			cout << i+1 << "| "<<lines[box[i].index] << " | "<<box[i].no_of_x << "--" << box[i].index << endl;
		}
		cout << endl;
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		////////////////// The Magic?
		int x = box.size()-1;
		bool swap_once = false;
		while(x>=0)
		{
			string s = lines[box[x].index];
			cout << s << endl;
			s.erase(remove(s.begin(), s.end(), ' '),s.end());
			s.erase(remove(s.begin(), s.end(), 'x'),s.end());
			if(box[x].no_of_x == 1)
			{
				if(s[0]=='(') //(3')
				{
					int b = convch(s[1]);
					cfrm[b-1]=2;
				}
				else if(s[0]== '=') //=>4
				{
					int b = convch(s[2]);
					cfrm[b-1]=1;
				}

			}
			else // Not one digestd start
			{
				if(s[0]!='(') //4=>2
				{
					int a = convch(s[0]);
					int b = convch(s[3]);
					if(cfrm[a-1]==1)
						cfrm[b-1]=1;
					else if(cfrm[a-1]==2)
						cfrm[b-1]=2;
					else
						cfrm[b-1]=0;
				}
				else
				{
					int ets = s.find("=");
					if(ets!=-1) //(^)=>
					{
						int snd_brac = s.find(")");
						string isequal = s.substr(snd_brac+3);
						string bracket = s.substr(1,snd_brac-1);
						vector<int> numbers;
						stringstream split(bracket);
						string token;

						while(getline(split,token,'^')) // Seperate commas and put in a vector
						{
							numbers.push_back(conv(token));
						}
						bool swap = false;
						for (int i = 0; i < numbers.size(); ++i)
						{
							if(cfrm[numbers[i]-1] == -1)
								swap = true;
						}
						if(swap && !swap_once && x!=0)
						{
							//cout << "swapping was done..\n";
							string temp = lines[box[x].index];
							lines[box[x].index] = lines[box[x-1].index];
							lines[box[x-1].index] = temp;
							swap_once = true;
							x++;
						}
						else
						{
							bool two = false;
							int t =0, m=0;
							bool minus = false;
							for (int i = 0; i < numbers.size(); ++i)
							{
								if(cfrm[numbers[i]-1]==2)
								{
									two = true;
									t=i;
								}
								if(cfrm[numbers[i]-1]==-1)
								{
									minus = true;
									m=i;
								}
							}
							if(!minus && !two)
							{
								cfrm[conv(isequal)-1] = 1;
							}
							else if(minus && two)
								if(two)
									if(cfrm[conv(isequal)-1]==-1)
									{
										cfrm[conv(isequal)-1] ==2;
										cfrm[numbers[t]-1] =2;
									}
									else if(cfrm[conv(isequal)-1]==1)
										cfrm[numbers[t]-1] =2;
								else if(minus)
									if(cfrm[conv(isequal)-1]==-1)
										cfrm[conv(isequal)-1] ==-1;
									else if(cfrm[conv(isequal)-1]==1)
										cfrm[numbers[m]-1] =1;
							else if(two)
								if(cfrm[conv(isequal)-1] ==1)
									cfrm[numbers[t]-1] =2;
								else if(cfrm[conv(isequal)-1] ==-1)
									cfrm[conv(isequal)-1] =1;
							else if(minus)
								if(cfrm[conv(isequal)-1] ==1)
									cfrm[numbers[t]-1] =1;


							
						}
					}
					else //(3v4’)
					{
						vector<string> negations;
						negations.push_back(s);

					}
				}
			}
			for (int i = 0; i < cfrm.size(); ++i)
			{
				cout << cfrm[i] << " ";
			}
			cout << endl;
			x--;
		}
		//////////////////////// Print the confirm table
		cout << endl;
		cout << endl;
		for (int i = 0; i < cfrm.size(); ++i)
		{
			if(cfrm[i] == 2 || cfrm[i] == -1)
					cout << "x" <<i+1 << ": "<< 0 << endl;
			else
				cout << "x" <<i+1 << ": " <<cfrm[i] << endl;
		}
	}
	else
		cout << "Error 404. File Not Found.\n";
	read.close();
}
