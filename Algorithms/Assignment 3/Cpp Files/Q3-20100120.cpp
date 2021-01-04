/*

A divide and conquer algorithm is used. 

	1. The base case is 2x2 because then we can manually insert the L shape.
	2. In the recursive case, we will only handle one condition and leave the rest to recursion.
	3. The easist case to handle is to split the 8x8 board into 4 4x4 boxes. Then find which box the hole is.
	Add the L shape such that all other 3 quadrants have one alphabet in it.
	4. Give 4 recursive calls for each quadrant and recursion does the rest. 

	Running time is O(n^2) since we traverse entire 2D array.
	Reccurence relation: T(n) = 4T(n/2) + O(1).

*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <iomanip>

using namespace std;

int N;
int X;
int Y;
bool check = true;
bool index_incr_check = false;
vector<string> chars;
int index = 3;

void print(string **arr, int n)
{
	n =N;
	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			cout << setw(2) << arr[i][j] << " ";
		}
		cout << endl;
	}
}

void check_quadrant(string **arr,int T, int L, int R, int B, int count)
{
	if(Y>=L && Y<=L+((R-L)/2) && X>=T && X<=T+((B-T)/2)) // Top left quadrant
	{
		if(count == 4)
		{
		}
		else
		{
			//cout << "Top left" << endl;
			arr[T+((B-T)/2)][L+((R+1)-L)/2] = chars[chars.size()-1]; // the one on the top right
			arr[T+((B+1)-T)/2][L+((R-L)/2)] = chars[chars.size()-1]; // the one on the bottom left
			arr[T+((B+1)-T)/2][L+((R+1)-L)/2] = chars[chars.size()-1]; // the one on the bottom right
			chars.pop_back();
			index++;
			check_quadrant(arr, T, L, L+((R-L)/2), T+((B-T)/2), count/4);
		}
		return;

	}
	else if(Y>=L+((R+1)-L)/2 && Y<=R && X>=T && X<=T+((B-T)/2)) // Top right quadrant
	{
		if(count == 4)
		{
		}
		else
		{
			//cout << "Top right" << endl;
			arr[T+((B-T)/2)][L+((R-L)/2)] = chars[chars.size()-1]; // the one on the top left
			arr[T+((B+1)-T)/2][L+((R-L)/2)] = chars[chars.size()-1]; // the one on the bottom left
			arr[T+((B+1)-T)/2][L+((R+1)-L)/2] = chars[chars.size()-1]; // the one on the bottom right
			chars.pop_back();
			index++;
			check_quadrant(arr, T, L+((R+1)-L)/2, R, T+((B-T)/2), count/4);
		}
	}
	else if(Y>=L && Y<=L+((R-L)/2) && X>=T+((B+1)-T)/2 && X<=B) // Bottom left quadrant
	{
		if(count == 4)
		{
		}
		else
		{
			//cout << "Bottom left" << endl;
			arr[T+((B-T)/2)][L+((R-L)/2)] = chars[chars.size()-1]; // the one on the top left
			arr[T+((B-T)/2)][L+((R+1)-L)/2] = chars[chars.size()-1];// the one on the top right
			arr[T+((B+1)-T)/2][L+((R+1)-L)/2] = chars[chars.size()-1]; // the one on the bottom right
			chars.pop_back();
			index++;
			check_quadrant(arr, T+((B+1)-T)/2, L, L+((R-L)/2), B, count/4);
		}
	}
	else if(Y>=L+((R+1)-L)/2  &&  Y<=R  &&  X>=T+((B+1)-T)/2  &&  X<=B) // Bottom right quadrant
	{
		if(count == 4)
		{
		}
		else
		{
			//cout << "Bottom right" << endl;
			arr[T+((B-T)/2)][L+((R-L)/2)] = chars[chars.size()-1]; // the one on the top left
			arr[T+((B+1)-T)/2][L+((R-L)/2)] = chars[chars.size()-1]; // the one on the bottom left
			arr[T+((B-T)/2)][L+((R+1)-L)/2] = chars[chars.size()-1];// the one on the top right
			chars.pop_back();
			index++;
			check_quadrant(arr, T+((B+1)-T)/2, L+((R+1)-L)/2, R, B, count/4);
		}

	}
}

void fill(string **arr, int T, int L, int R, int B, int x)
{
	//cout << "T: " << T << " L: " << L << " R: " << R << " B: " << B << " Index: "<< index << endl;
	if(arr[T][L]=="a" || arr[T][R]=="a" || arr[B][L]=="a" || arr[B][R] =="a") // Handles the box with the empty space
	{
		if(X==T)
		{
			if(Y==L)
			{
				arr[T][R]="b";
				arr[B][L]="b";
				arr[B][R]="b";
			}
			else if(Y==R)
			{
				arr[T][L]="b";
				arr[B][L]="b";
				arr[B][R]="b";
			}
		}
		else if(X==B)
		{
			if(Y==L)
			{
				arr[T][L]="b";
				arr[T][R]="b";
				arr[B][R]="b";
			}
			else if(Y==R)
			{
				arr[T][L]="b";
				arr[T][R]="b";
				arr[B][L]="b";
			}
		}
	}
	else if(arr[T][L]=="-" && arr[T][R]=="-" && arr[B][L]=="-" && arr[B][R] =="-") //is completely empty then the x direction will come into play
	{
		if(x==1) // Looking at top left
		{
			arr[T][L]= chars[chars.size()-1];
			arr[T][R]= chars[chars.size()-1];
			arr[B][L]= chars[chars.size()-1];
		}
		else if(x==2) // Looking at top right
		{
			arr[T][L]= chars[chars.size()-1];
			arr[T][R]= chars[chars.size()-1];
			arr[B][R]= chars[chars.size()-1];
		}
		else if(x==3) // Looking at bottom left
		{
			arr[T][L]= chars[chars.size()-1];
			arr[B][R]= chars[chars.size()-1];
			arr[B][L]= chars[chars.size()-1];
		}
		else if(x==4) // Looking at bottom right
		{
			arr[T][R]= chars[chars.size()-1];
			arr[B][L]= chars[chars.size()-1];
			arr[B][R]= chars[chars.size()-1];
		}
		index++;
		chars.pop_back();
	}
	else if(arr[T][L]!="-" || arr[T][R]!="-" || arr[B][L]!="-" || arr[B][R] !="-")  //has one dabba filled in it
	{
		if(arr[T][L]!="-" && arr[T][R]=="-" && arr[B][L]=="-" && arr[B][R] =="-")
		{
			arr[T][R] = chars[chars.size()-1];
			arr[B][L] = chars[chars.size()-1];
			arr[B][R] = chars[chars.size()-1];
		}
		else if(arr[T][L]=="-" && arr[T][R]!="-" && arr[B][L]=="-" && arr[B][R] =="-")
		{
			arr[T][L] = chars[chars.size()-1];
			arr[B][L] = chars[chars.size()-1];
			arr[B][R] = chars[chars.size()-1];
		}
		else if(arr[T][L]=="-" && arr[T][R]=="-" && arr[B][L]!="-" && arr[B][R] =="-")
		{
			arr[T][L] = chars[chars.size()-1];
			arr[T][R] = chars[chars.size()-1];
			arr[B][R] = chars[chars.size()-1];
		}
		else if(arr[T][L]=="-" && arr[T][R]=="-" && arr[B][L]=="-" && arr[B][R] !="-")
		{
			arr[T][L] = chars[chars.size()-1];
			arr[T][R] = chars[chars.size()-1];
			arr[B][L] = chars[chars.size()-1];
		}
		chars.pop_back();
		index++;
	}
}

void fill_rest(string **arr, int T, int L, int R, int B) 						/////////////////////////////////////////////////////
{
	for(int i=T;i<B;i++)
	{
		for(int j=L;j<R;j++)
		{
			if(arr[i][j]=="-")
			{
				arr[i][j]=chars[chars.size()-1];
				
			}
		}
	}
	chars.pop_back();
}
void boxes(string **arr, int T, int L, int R, int B, int count, int x)
{
	/* count is the number of boxes in our array
	x tells which direction we took
	index tells the number we are putting in the boxes*/
	/*print(arr, N);
	cout << endl;*/
	if(check)
		check_quadrant(arr,T,L,R,B,count);
	check = false;
	if(count==4)
	{
		if(x==1) // Looking at top left
			fill(arr,T,L,R,B,1);
		else if(x==2) // Looking at top right
			fill(arr,T,L,R,B,2);
		else if(x==3) // Looking at bottom left
			fill(arr,T,L,R,B,3);
		else if(x==4) // Looking at bottom right
			fill(arr,T,L,R,B,4);
	}
	else
	{

		boxes(arr, T, L, L+((R-L)/2), T+((B-T)/2), count/4, 1); // Top Left
		boxes(arr, T, L+((R+1)-L)/2, R, T+((B-T)/2), count/4, 2); // Top Right
		boxes(arr, T+((B+1)-T)/2, L, L+((R-L)/2), B, count/4, 3); // Bottom Left
		boxes(arr, T+((B+1)-T)/2, L+((R+1)-L)/2, R, B, count/4, 4); // Bottom Right
		if(count==16)																/////////////////////////////////////////////////
			fill_rest(arr, T, L, R, B);												////////////////////////////////////////////////

	}
	return;
}


int main()
{
	int i = 0;
	string s = "zyxwvutsrqponmlkjihgfedc.";
	string c = "";
	while(c!="c")
	{
		c = s.substr(i,1);
		chars.push_back(c);
		i++;
	}





	int n, x, y;
	cout << "Enter n (nxn): ";
	cin >> n;
	cout << "(Row #, Col #): ";
	cin >> x >> y;
	X = x;
	Y = y;
	N = n;
	string **arr;
	arr = new string*[n];
	for (int i = 0; i < n; ++i)
	{
		arr[i]=new string[n];
	}

	for (int i = 0; i < n; ++i)
	{
		for (int j = 0; j < n; ++j)
		{
			arr[i][j] = "-";
		}
	}
	arr[X][Y] = "a";
	int count = n*n;
	cout << endl;
	boxes(arr, 0 , 0 , n-1, n-1, count, 0);
	arr[X][Y] = "?";
	print(arr, n);
}
