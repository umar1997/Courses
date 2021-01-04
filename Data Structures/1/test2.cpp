#include "MySortedSet.cpp"
#include <iostream>
#include <string>
#include <assert.h>
using namespace std;



int main()
{
	int score = 0;
	MySortedSet<int>* S1 = new MySortedSet<int>();
	MySortedSet<int>* S2 = new MySortedSet<int>();
	MySortedSet<int>* SEmpty = new MySortedSet<int>();
	cout<<"Starting Tests"<<endl;


//**************************isEmpty***************************
	cout<<"Testing isEmpty"<<endl; //total points = 2

	if (S1->isEmpty()==1)
		score += 2;

	if(score==2)
		cout<<"All Tests Passed!"<<endl;

	cout<<"Points: "<<score<<endl;

//************************Insert******************************
	cout<<"Testing Insert"<<endl; //total points = 10

	int correctinsert = 0;
	for (int i=1; i<10; ++i)
	{
		S1->insert(i);
		S2->insert(i);

	}

	ListItem<int>* head = S1->getListHead();
	int tmp = 1;
	while(head!=NULL)
	{
		if (head->value == tmp)
			correctinsert ++;
		head = head->next;
		tmp++;
	}

	if(S1->insert(5) == 0)
	{
		correctinsert++;
	}

	if(correctinsert <=0)
		score += 0;
	else
	{
		score += correctinsert;
	}

	if(correctinsert==10)
		cout<<"All Tests Passed! "<<endl;

	cout<<"Points: "<<correctinsert<<endl;

//*************************isMember*********************************

	cout<<"Testing isMember"<<endl; //total points = 3
	int correctmember = 0;
	int tmp2 = S1->isMember(5);
	if(tmp2 == 1)
	{
		score++;
		correctmember +=1;
	}
	tmp2 = S1->isMember(14);
	if(tmp2 == 0)
	{
		score+=2;
		correctmember+=2;
	}

	if(correctmember==3)
	{
		cout<<"All Tests Passed!"<<endl;
	}
	cout<<"Points: "<<correctmember<<endl;
//********************************isEqual*****************************
	cout<<"Testing isEqual"<<endl; //total points = 5
	int correctequal = 0;
	if(S1->isEqual(S2)==1)
	{
		score += 2;
		correctequal = 2;
	}

	S2->deleteEle(3);
	if(S1->isEqual(S2)==0)
	{
		score += 3;
		correctequal += 3;
	}

	if (correctequal==5)
		cout<<"All Tests Passed!"<<endl;
	cout<<"Points: "<<correctequal<<endl;

//*****************************isSubset*********************************
	cout<<"Testing isSubset"<<endl; //total points = 10

	int correctsubset = 0;
	if((S1->isSubset(S2))==1)
	{
		correctsubset += 5;
		score+=5;
	}

	S2->insert(16);

	if((S1->isSubset(S2)) == 0)
	{
		correctsubset += 5;
		score+=5;
	}

	if(correctsubset==10)
		cout<<"All Tests Passed!"<<endl;

	cout<<"Points: "<<correctsubset<<endl;

//*****************************Union************************************
	cout<<"Testing Union"<<endl; //total points = 20 --> AU0 = A; AUA = A; AUB
	int correctunion = 0;
	MySortedSet<int>* resultU = new MySortedSet<int>();

	for (int i=1;i<10;i++)
		resultU->insert(i);
	resultU->insert(16);

	if (S1->isEqual((S1->setUnion(SEmpty)))==1)
		correctunion += 5;

	if (S1->isEqual(S1->setUnion(S1))==1)
		correctunion += 5;

	MySortedSet<int>* resUnion = S1->setUnion(S2);

	if (resultU->isEqual(resUnion)==1)
		correctunion += 5;

	score += correctunion;

	if (correctunion==15)
		cout<<"All Tests Passed!"<<endl;

	cout<<"Points: "<<correctunion<<endl;

//*****************************Intersection********************************

	cout<<"Testing Intersection"<<endl; //A^0 = 0
	int correctintersect = 0;
	MySortedSet<int>* R1 = S1->setIntersection(SEmpty);
	MySortedSet<int>* resultI = new MySortedSet<int>();

	resultI->insert(1);
	resultI->insert(2);
	resultI->insert(4);
	resultI->insert(5);
	resultI->insert(6);
	resultI->insert(7);
	resultI->insert(8);
	resultI->insert(9);


	if (R1->isEmpty()==1)
		correctintersect += 5;

	if (S1->isEqual(S1->setIntersection(S1))==1)
		correctintersect += 5;

	MySortedSet<int>* resIntersect = S1->setIntersection(S2);
	if (resultI->isEqual(resIntersect)==1)
		correctintersect += 5;

	score += correctintersect;

	if (correctintersect==15)
		cout<<"All Tests Passed!"<<endl;

	cout<<"Points: "<<correctintersect<<endl;

//**************************Set Difference*********************************
	cout<<"Testing Set Difference"<<endl;
	int correctdiff = 0;
	MySortedSet<int>* resultDiff = new MySortedSet<int>();

	resultDiff->insert(3);

	MySortedSet<int>* resDiff = S1->setDifference(S2);

	if ((resultDiff->isEqual(resDiff))==1)
		correctdiff += 5;

	if (correctdiff == 5)
		cout<<"All Tests Passed!"<<endl;

	score += correctdiff;
	cout<<"Points: "<<correctdiff<<endl;

	cout<<"Total = "<<score<<endl;



}
