#include <iostream>
#include "tree.cpp"

using namespace std;

int main(){
	cout<<"Testing Bonus Part!!!\n";
	Tree t("input_bonus.txt");
	t.moveFolder("C:","Suits Season 2"); // moving root case // Tree should not change 
	t.moveFolder("CS 678","summary-1.docx"); // moving ancestor case // tree should not change
	t.moveFolder("Suits Season 2","CS 678"); 
	t.moveFolder("White Collar","summary-1.docx");

	int pts = 0;
	vector<string> result;
	result = t.Locate("s04e01.avi");

	if(result.size() == 6){
		if (result[1] == "White Collar"){
			pts++;
			cout<<".";
		}
		if (result[2] == "summary-1.docx"){
			pts++;
			cout<<".";
		}
		if (result[3] == "CS 678"){
			pts++;
			cout<<".";
		}
		if (result[4] == "Spring'13"){
			pts++;
			cout<<".";
		}
		if (result[5] == "C:"){
			pts++;
			cout<<".";
		}
	}


	result = t.Locate("episode1.avi");

	if(result.size() == 5){
		if (result[0] == "episode1.avi"){
			pts++;
			cout<<".";
		}
		if (result[1] == "Suits Season 2"){
			pts++;
			cout<<".";
		}
		if (result[2] == "CS 678"){
			pts++;
			cout<<".";
		}
		if (result[3] == "Spring'13"){
			pts++;
			cout<<".";
		}
		if (result[4] == "C:"){
			pts++;
			cout<<".";
		}
	}



	cout << "\nSCORE = " << pts << "/" << "10" << endl;




	return 0;
}