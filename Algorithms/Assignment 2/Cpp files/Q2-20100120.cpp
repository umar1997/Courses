#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>

using namespace std;

struct node
{
	string Name;
	double Distance;
	double Total_Dist;
	double Litres;
};

double convd(string s)
{
	stringstream converter(s);
	double x;
	converter >> x;
	return x;
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int main()
{

	/*FILE READING*/
	ifstream read;
	read.open("q2.txt");
	if(read.is_open())
	{
		int n;
		double R, F, loop_no;
		double T, benchMark;

		string litres, c_Rate, f_Rate, loop_line;
		getline(read, litres);
		litres.erase(remove(litres.begin(), litres.end(), ' '),litres.end());
		T = convd(litres.substr(1));
		getline(read, c_Rate);
		c_Rate.erase(remove(c_Rate.begin(), c_Rate.end(), ' '),c_Rate.end());
		R = convd(c_Rate.substr(1));
		getline(read, f_Rate);
		f_Rate.erase(remove(f_Rate.begin(), f_Rate.end(), ' '),f_Rate.end());
		F = convd(f_Rate.substr(1));
		getline(read, loop_line);
		loop_line.erase(remove(loop_line.begin(), loop_line.end(), ' '),loop_line.end());
		n = static_cast<int>(convd(loop_line.substr(1)));

		//cout << T << " " << R << " " << F << " " << n << endl;

		/* ARRAY OF STRUCTS*/
		n=n+2;
		node station[n];
		station[0].Name = "O";
		station[0].Total_Dist = 0;
		station[0].Distance = 0;
		station[0].Litres = 0;
		int c=1;
		double dist, weight = 0;
		while(!read.eof())
		{
			string s, a;
			getline(read, s);
			int space = s.find(" ");
			a = s.substr(0,space);
			station[c].Name = a;
			station[c].Total_Dist = convd(s.substr(space+1));
			station[c].Distance = convd(s.substr(space+1)) - station[c-1].Total_Dist;
			station[c].Litres = station[c].Distance * R;
			c++;
		}

		for(int j=0;j<n;j++)
		{
			cout << station[j].Name << " "  << station[j].Total_Dist << " " << station[j].Distance << " " << station[j].Litres << endl;
		}
		cout << "T: " << T << " R: " << R << " F: " << F << endl << endl;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		double mins = 0;
		benchMark = T/R;
		double curr_T = T;
		if(T < benchMark)
		{
			cout << mins << " minutes." << endl;
		}
		else
		{
			c=1;
			while(1)
			{
				double cmp_litres = station[c].Litres;
				curr_T -= station[c].Litres;
				if(station[c+1].Litres < curr_T)
				{
					c++;
				}
				else
				{
					double km_Left = station[n-1].Total_Dist - station[c].Total_Dist;
					if(km_Left > benchMark)
					{
						mins = mins + ((T-curr_T)/F);
						curr_T = T;
						cout << station[c].Name << " " << station[c].Total_Dist << " (" << mins << ")" << ", ";
						c++;
					}
					else
					{
						double rem_Litres = km_Left*R;
						rem_Litres= rem_Litres - curr_T;
						mins = mins + (rem_Litres/F);
						cout << station[c].Name << " " << station[c].Total_Dist << " (" << mins << ")" << endl;
						break;
					}
				}

			}
			cout << mins << " minutes." << endl;
			
		}
		

	}
	else
		cout << "Error 404 File not found!" << endl;
	read.close();

	return 0;
}