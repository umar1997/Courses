#include <fstream>
#include "sorts.cpp"
#include <time.h>

using namespace std;



// A single pair is stored in a Vector<long>
// You have to return a vector of all pairs.
vector< vector<long> > smartSearch(vector<long> nums, long k)
{   
    vector <vector<long>> final;
    int x= nums.size(); 
    nums= MergeSort(nums);
    for(int y=0;y<x;y++)
    {
        
        int fin = k-nums[y];
        
        bool check = false;
        int i=0;
        int j=x;

        while(1)
        {
            if(i>j)
                break;
            else
            {
                int mid= (j-i)/2 + i;
                if(nums[mid]==fin){
                    check=true;
                    break;
                }
                else if (fin>nums[mid])
                    i=++mid;
                else
                    j=--mid;
            }
        }


        if(check)
        {
            vector <long> a;
            a.push_back(nums[y]);
            a.push_back(fin);
            final.push_back(a);
        }
        

    }
    return final;
}


int main()
{
    vector<long> nums;
    ifstream in("random.txt");
    long n;
    while(in >> n)
        nums.push_back(n);
    in.close();

    long k;
    cout << "Enter the value of K: ";
    cin >> k;
    clock_t start= clock();
    vector< vector<long> > result = smartSearch(nums, k);
    clock_t end= clock();
    for(int i = 0; i < result.size(); i++)
        cout << result[i][0] << ", " << result[i][1] << endl;
    cout<<"TIME FOR SMART SEARCH: "<< (double)(end-start)/CLOCKS_PER_SEC<<"s";
    return 0;
}
