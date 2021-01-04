#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>

using namespace std;

struct node
{
	int Name;
	double Length;
	double Probability;
	double Ratio;
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
	read.open("q42.txt");
	if(read.is_open())
	{
		int n;
		string loop_line;
		getline(read, loop_line);
		loop_line.erase(remove(loop_line.begin(), loop_line.end(), ' '),loop_line.end());
		n = static_cast<int>(convd(loop_line.substr(1)));
		
		vector<double> len;
		vector<double> pr;

		vector<node> racks;
		///////////////////////////
		string line1;
		int a;
		getline(read, line1);
		line1 = line1.substr(1);
		line1.erase(remove(line1.begin(), line1.end(), ' '),line1.end());

		stringstream token(line1);
		string tab;

		while(getline(token,tab,','))
		{
			a=convd(tab);
			len.push_back(a);
		}
		///////////////////////////
		string line2;
		double b;
		getline(read, line2);
		line2 = line2.substr(1);
		line2.erase(remove(line2.begin(), line2.end(), ' '),line2.end());

		stringstream token2(line2);
		string tab2;

		while(getline(token2,tab2,','))
		{
			b=convd(tab2);
			pr.push_back(b);
		}
		for(int i =0;i<n; i++)
		{
			node temp_rack;
			temp_rack.Name = i+1;
			temp_rack.Length = len[i];
			temp_rack.Probability = pr[i];
			temp_rack.Ratio = pr[i]/len[i];
			racks.push_back(temp_rack);
		}
		///////////////////////////
		cout << "L ";
		for(int i=0;i<racks.size();i++)
		{
			cout << len[i] << " ";
		}
		cout << endl;
		cout << "p ";
		for(int i=0;i<racks.size();i++)
		{
			cout << pr[i] << " ";
		}
		cout << endl;
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		// Sorting the Ratios
		for (int k = 0; k < racks.size()-1; k++) 
		{ 
	        // Sorting the vector col.
	    	int min = k; 
	    	for (int j = k+1; j < racks.size(); j++) 
	      		if (racks[j].Ratio > racks[min].Ratio) 
	        		min = j; 

	    	int tempN = racks[min].Name;
	    	double tempL = racks[min].Length;
	    	double tempP = racks[min].Probability;
	    	double tempR = racks[min].Ratio;
	    	racks[min].Name = racks[k].Name;
	    	racks[min].Length = racks[k].Length;
	    	racks[min].Probability = racks[k].Probability;
	    	racks[min].Ratio = racks[k].Ratio;
	    	racks[k].Name = tempN;
	    	racks[k].Length = tempL;
	    	racks[k].Probability = tempP;
	    	racks[k].Ratio = tempR;
		}
		double sum =0;
		double time = 0;
		for(int i=0;i<racks.size();i++)
		{
			sum = sum + racks[i].Length;
			time = time + racks[i].Probability*sum;
		}
		cout << endl;
		cout << "Ordering: ";
		for(int i=0;i<racks.size();i++)
		{
			if(i==racks.size()-1)
				cout << "Rack " << racks[i].Name;
			else
				cout << "Rack " << racks[i].Name << ", ";

		}
		cout << endl;
		cout << "Expected Time: " << time << endl;
	}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	else
		cout << "Error 404 File not found!" << endl;
	read.close();
}