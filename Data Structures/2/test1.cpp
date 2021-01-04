#include "tree.cpp"
#include "time.h"
int main()
{
	cout<<"Testing Directory Tree!!!\n";
	Tree t("input_test.txt");
	int c;
	vector<string> result;
	string lca;

	int pts=0;
	int success=1;
	int count;

	result = t.Locate("CS 578");
	if(result.size() != 0){
		if (result[result.size()-2] == "Spring'13"){
			pts++;
			cout<<".";
		}
	}

	result = t.Locate("White Collar");
	if(result.size() != 0){
		if (result[result.size()-2] == "Spring'13"){
			pts++;
			cout<<".";
		}
	}

	result = t.Locate("summary-4.docx");
	if(result.size() != 0){
		if (result[result.size()-1] == "C:" && result[result.size()-2] == "Spring'13" && result[result.size()-3] == "CS 678"){
			pts++;
			cout<<".";
		}
	}

	result = t.Locate("s04e02.avi");
	if(result.size() != 0){
		if (result[result.size()-1] == "C:" && result[result.size()-2] == "Spring'13" && result[result.size()-3] == "White Collar"){
			pts++;
			cout<<".";
		}
	}
	
	cout<<endl;
	result = t.Locate("assignment2.txt");
	if(result.size() == 0)
		pts++;
	else
		cout<<"Error: found non existing file\n";

	if(pts != 5){
		cout<<"Error in Locate...\n";
		success = 0;
	}
	else
		cout<<"Locate Successful\n";

	pts = 0;

	
	lca = t.LComAc("s04e01.avi","s04e02.avi");
	if(lca == "Season 4"){
		pts++;
		cout<<".";
	}

	lca = t.LComAc("s04e01.avi","summary-1.docx");
	if(lca == "Spring'13"){
		pts++;
		cout<<".";
	}
	
	lca = t.LComAc("White Collar","Suits Season 2");
	if(lca == "Spring'13"){
		pts++;
		cout<<".";
	}

	cout<<endl;
	if(pts != 3){
		cout<<"Error in Locating Common Ancestor\n";
		success = 0;
	}
	
	pts = 0;
	count = t.countFiles();
	if(count == 9){
		pts++;
		cout<<".";
	}

	if(pts != 1){
		cout<<"Wrong Count\n";
		success = 0;
	} else 
		cout << "Right Count\n";

	if(success)
		cout<<"Tests Successfull\n";
	else
		cout<<"Test not Successfull\n";
}

