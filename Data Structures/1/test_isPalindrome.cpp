#include "LinkedList.cpp"
#include <iostream>
#include <string>
using namespace std; 

int main()
{
	int score = 0;
	LinkedList<int> l;
	cout << "Starting test 1" << endl;

	l.insertAtHead(1);
	l.insertAtHead(2);
	l.insertAtHead(2);
	l.insertAtHead(1);

	if(l.isPalindrome() == 1){
		cout << "Test 1 Passed" << endl;
		score += 10;
	}
	else
	{
		cout << "Test 1 failed" << endl;
	}

	
	LinkedList<int> l1;
	cout << "Starting test 2" << endl;

	l1.insertAtHead(1);
	l1.insertAtHead(2);
	l1.insertAtHead(3);
	l1.insertAtHead(4);

	if(l1.isPalindrome() == 0){
		cout << "Test Passed" << endl;
		score += 10;

	}
	else
	{
		cout << "Test failed" << endl;
	}


    LinkedList<int> l2;
	cout << "Starting test 3" << endl;


	if(l2.isPalindrome() == 0){
		cout << "Test Passed" << endl;
		score += 10;

	}
	else
	{
		cout << "Test failed" << endl;
	}


	LinkedList<int> l3;
	cout << "Starting test 4" << endl;

	l3.insertAtHead(1);
	l3.insertAtHead(2);
	l3.insertAtHead(3);
	l3.insertAtHead(2);
	l3.insertAtHead(1);

	if(l3.isPalindrome() == 1){
		cout << "Test Passed" << endl;
		score += 10;

	}
	else
	{
		cout << "Test failed" << endl;
	}

	cout << "you scored "  << score << "/40"<< endl;

	if (score == 40) {
		cout << "Overall Test Successful" << endl;
	} else {
		cout << "Overall Test Failed" << endl;	
	}

	return 0;


}
