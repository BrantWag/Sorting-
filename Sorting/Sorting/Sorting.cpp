//Brant Wagner
//4-6-19
//Sorting Project 
//See documenation for further referance 

#include "stdafx.h"
#include "DoubleLL.h"
#include <iostream>
#include <time.h>
#include <cstdio>

using namespace std;

//Insert Node in List
void insert(DoublyLinkedList<int> listy, int val)
{
	listy.insertNode(val);
}

//Find Node in List
void lookup(DoublyLinkedList<int> listy, int val)
{
	if (listy.find(val) != nullptr)
	{
		auto foundNode = *listy.find(val);
		cout << "Found: " << foundNode.get_Data() << endl;
	}
	else
	{
		cout << "Not found" << endl;
	}
}

//Delete Node in List
void destroy(DoublyLinkedList<int> listy, int val)
{
	listy.deleteNode(val);
}

//Display all nodes in list
void display(DoublyLinkedList<int> listy)
{
	listy.displayList();
}

//Sort Bubble Sort
void sortWithBubble(DoublyLinkedList<int> listy)
{
	long double duration;
	clock_t start = clock();
	listy.bubbleSort();
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;

	cout << "This took: " << duration << " seconds to complete" << endl;
}

//Sort Selection Sort
void sortWithSelection(DoublyLinkedList<int> listy)
{
	long double duration;
	clock_t start = clock();
	listy.selectionSort();
	duration = (clock() - start) / (double)CLOCKS_PER_SEC;

	cout << "This took: " << duration << " seconds to complete" << endl;
}

//Automated Suite
void automatedTest()
{
	cout << "Bubble Sort" << endl;
	int unsortedInts[10] = { 0,50,20,40,10,60,30,80,70,90 };
	DoublyLinkedList<int> list_1;
	for (int i = 0; i < sizeof(unsortedInts) / sizeof(int); i++)
	{
		list_1.insertNode(unsortedInts[i]);
	}
	cout << "List to Sort: " << endl;
	list_1.displayList();
	cout << "Sorted List: " << endl;
	list_1.bubbleSort();
	list_1.displayList();

	cout << "Selection Sort" << endl;
	DoublyLinkedList<int> list_2;
	for (int i = 0; i < sizeof(unsortedInts) / sizeof(int); i++)
	{
		list_2.insertNode(unsortedInts[i]);
	}
	cout << "List to Sort: " << endl;
	list_2.displayList();
	cout << "Sorted List: " << endl;
	list_2.selectionSort();
	list_2.displayList();
}

//Simply Display Menu
void displayMenu()
{
	cout << "Menu Options:" << endl;
	cout << "1. Insert Node in List" << endl;
	cout << "2. Lookup Node in List" << endl;
	cout << "3. Delete Node in List" << endl;
	cout << "4. Sort List (Bubble Sort)" << endl;
	cout << "5. Sort List (Selection Sort)" << endl;
	cout << "6. Display List" << endl;
	cout << "7. Complete Automated Suite" << endl;
	cout << "99. Exit Program" << endl;
}

//Display a welcome screen with a brief introduction to the program
void displayStart()
{
	cout << "Welcome" << endl;
	cout << "This is a templated linked list" << endl;
	cout << "The default table is of int type" << endl;
	system("pause");
}

int main()
{
	//variables
	int choice;
	int value;
	DoublyLinkedList<int> dlList;

	displayStart();

	//Main program loop
	do
	{
		displayMenu();
		cout << "Please select an option" << endl;
		cin >> choice;
		switch (choice)
		{
		case 1:
		{
			cout << "Choose a value to insert" << endl;
			cin >> value;
			cout << endl;
			insert(dlList, value);
			break;
		}
		case 2:
		{
			cout << "What node would you like to look up?" << endl;
			cin >> value;
			cout << endl;
			lookup(dlList, value);
			break;
		}
		case 3:
		{
			cout << "What node would you like to delete?" << endl;
			cin >> value;
			cout << endl;
			destroy(dlList, value);
			break;
		}
		case 4:
		{
			sortWithBubble(dlList);
			break;
		}
		case 5:
		{
			sortWithSelection(dlList);
			break;
		}
		case 6:
		{
			display(dlList);
			break;
		}
		case 7:
		{
			automatedTest();
			break;
		}
		case 99:
		{
			cout << "Exiting Program" << endl;
			break;
		}
		default:
		{
			cout << "Invalid option selected" << endl;
			cout << "Please select a valid option from the menu" << endl;
			break;
		}
		}
		system("pause");
		system("cls");
	} while (choice != 99);
}

