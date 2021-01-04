#include <cstdio>
#include <signal.h>
#include <iostream>
#include <string>
#include <vector>
#include "LinkedList.cpp"
using namespace std;

int testno;
int totpoints;
int lastpoints;
int lasttotpoints;
int points;

vector<int> GenerateRandom();

void test_list_init()
{
    lasttotpoints = 0;

    LinkedList<int> a;
    cout << ".";

    LinkedList<string> b;
    cout << ".";

    LinkedList<LinkedList<int> > c;
    cout << ".";
}

void test_list_insert_head()
{
    lasttotpoints = 5;

    LinkedList<int> l;
    for (int i = 0; i < 25000; i++)
    {
        l.insertAtHead(i);
        ListItem<int> *tmp = l.getHead();
        int k = i;
        while (tmp != NULL)
        {
            if (tmp->value != k)
                int a = 1/0;
            k--;
            tmp = tmp->next;
        }
    }
    cout << ".";

    lastpoints += 5;
}

void test_list_insert_tail()
{
    lasttotpoints = 10;

    LinkedList<int> l;
    for (int i = 0; i < 25000; i++)
    {
        l.insertAtTail(i);
        ListItem<int> *tmp = l.getTail();
        int k = i;
        while (tmp != NULL)
        {
            if (tmp->value != k)
                int a = 1/0;
            k--;
            tmp = tmp->prev;
        }
    }
    cout << ".";

    lastpoints += 10;
}

void test_list_insert_after()
{
    lasttotpoints = 10;

    LinkedList<int> l;
    l.insertAtHead(0);
    for (int i = 1; i < 25000; i++)
    {
        l.insertAfter(i, i-1);
        ListItem<int> *tmp = l.searchFor(i);
        if (tmp->next != NULL || tmp->prev->value != (i-1) || tmp->value != i)
            int a = 1/0;
	}
    cout << ".";

    lastpoints += 10;
}

void test_list_insert_sorted()
{
    lasttotpoints = 10;

    LinkedList<int> l;
    vector<int> nums = GenerateRandom();

	ListItem<int>* tmp;
	int length;

    for (int i = 0; i < 25000; i++)
    {
        l.insertSorted(nums[i]);
        length = l.length();
        tmp = l.getHead();
        // Checking if still sorted
        for(int j = 0; j < length-1; j++)
        {
			if(tmp->value > tmp->next->value)
				int a = 1/0;
			tmp = tmp->next;
        }
	}
	length = l.length();
	if(length != 25000)
		int a = 1/0;

    cout << ".";

    lastpoints += 10;
}

void test_delete()
{
    lasttotpoints = 20;

    // Insert some items
    LinkedList<int> l;
    for (int i = 0; i < 25000; i++)
    {
        l.insertAtHead(i);
    }

    // Delete the head a few times
    for (int i = 0; i < 50; i++)
        l.deleteHead();

	int length = l.length();
	if(length != 24950)
		int a = 1/0;

    cout << ".";
    lastpoints += 5;

    // Delete most of the items in the list
    while (l.length() > 50)
    {
        ListItem<int> *tmp = l.getHead();
        if (tmp != NULL)
            l.deleteElement(tmp->value);
        tmp = l.getTail();
        if (tmp != NULL)
            l.deleteElement(tmp->value);
	}
    lastpoints += 10;
    cout << ".";

    // Delete the tail till we're done
    int max = l.length();
    for (int i = 0; i < max; i++)
        l.deleteTail();
	cout << ".";
    lastpoints += 5;
}

void test_copy()
{
    lasttotpoints = 5;

    LinkedList<int> l;
    for (int i = 0; i < 25000; i++)
    {
        l.insertAtHead(i);
    }
    LinkedList<int> l2(l);
    LinkedList<int> l3;
    for (int i = 0; i < 25000; i++)
    {
        l3.insertAtHead(i);
        l.deleteHead();
    }

    ListItem<int> *tmp = l2.getHead();
    int k = 24999;
    while (tmp != NULL)
    {
        if (tmp->value != k)
            int a = 1/0;
        k--;
        tmp = tmp->next;
    }
    if (k != -1)
        int a = 1/0;

    cout << ".";

    lastpoints += 5;
}

void test_search()
{
    lasttotpoints = 10;

    // Insert some items
    LinkedList<int> l;
    for (int i = 0; i < 25000; i++)
    {
        l.insertAtHead(i);
    }

    ListItem<int> *tmp;
	//Search for values that are present
	for(int i = 0; i < 25000; i++)
	{
		tmp = l.searchFor(i);
		if(tmp->value != i)
			int a = 1/0;
	}
	cout << ".";
	lastpoints += 5;

	//Search for values that are NOT present
	for(int i = 25000; i < 50000; i++)
	{
		tmp = l.searchFor(i);
		if(tmp != NULL)
			int a = 1/0;
	}
	cout << ".";
	lastpoints += 5;
}

void test_reverse()
{
    lasttotpoints = 10;

    // Insert some items
    LinkedList<int> l;
    for (int i = 0; i < 1000; i++)
    {
        l.insertAtHead(i);
    }

    //Reverse the list
    l.reverse();
    ListItem<int> *tmp = l.getHead();

    for(int i = 0; i < 1000; i++)
    {
        if(tmp->value != i)
            int a = 1/0;
        tmp = tmp->next;
    }
    cout << ".";
    lastpoints += 10;
}

void test_parity()
{
    lasttotpoints = 10;

    // Insert some items
    LinkedList<int> l;
    for (int i = 0; i < 1000; i++)
    {
        l.insertAtTail(i);
    }

    //ParityArrange the list
    l.parityArrangement();
    ListItem<int> *tmp = l.getHead();
    int length = l.length();
    int index = 0;

    for(int i = 0; i < length; i++)
    {
        if(tmp->value != index)
            int a = 1/0;
        tmp = tmp->next;
        index += 2;
        if (index >= length) {index = 1;}
    }
    cout << ".";
    lastpoints += 10;
}

// Test case dispatcher
void dispatcher()
{
    while (true)
    {
        lastpoints = 0;
        lasttotpoints = 0;
        switch (testno)
        {
            case 0:
                {
                    cout << "Testing LinkedList Initialization ";
                    test_list_init();
                }
                break;
            case 1:
                {
                    cout << "Testing Insertion at Head ";
                    test_list_insert_head();
                }
                break;
            case 2:
                {
                    cout << "Testing Insertion at Tail ";
                    test_list_insert_tail();
                }
                break;
            case 3:
                {
                    cout << "Testing Insertion After ";
                    test_list_insert_after();
                }
                break;
			case 4:
				{
                    cout << "Testing Sorted Insertion ";
                    test_list_insert_sorted();
				}
				break;
            case 5:
                {
                    cout << "Testing Delete ";
                    test_delete();
                }
                break;
            case 6:
                {
                    cout << "Testing Copy ";
                    test_copy();
                }
                break;
			case 7:
				{
                    cout << "Testing Search ";
                    test_search();
				}
				break;
            case 8:
                {
                    cout << "Testing Reverse ";
                    test_reverse();
                }
                break;
            case 9:
                {
                    cout << "Testing ParityArrangement ";
                    test_parity();
                }
                break;
            default:
                {
                    cout << "Total Points: " << points << " / " << totpoints << endl << endl;
                    exit(0);
                }
        }
        cout << " Passed! " << lastpoints << " / " << lasttotpoints << endl;
        testno++;
        points += lastpoints;
        totpoints += lasttotpoints;
    }
}

// Signal handler for exceptions
void signal_handler(int signum)
{
    cout << " Failed! " << lastpoints << " / " << lasttotpoints << endl;

    testno++;
    points += lastpoints;
    totpoints += lasttotpoints;

    signal(SIGSEGV, signal_handler);
    signal(SIGFPE, signal_handler);
    dispatcher();
}

int main()
{
    // Set signal handlers
    signal(SIGSEGV, signal_handler);
    signal(SIGFPE, signal_handler);

    cout << "Starting Tests" << endl;

    testno = 0;
    points = 0;
    totpoints = 0;
    dispatcher();
}

// Just some friendly number theory :)
vector<int> GenerateRandom()
{
	vector <int> nums;
	int residue;
	for(int k=0; k<25000; k++)
	{
		residue = (k*31)%3571;
		nums.push_back(residue);
	}
	return nums;
}
