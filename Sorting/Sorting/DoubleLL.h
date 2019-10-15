#pragma once
//Brant Wagner
//4-6-19
#include "stdafx.h"
#include <memory>
#include <iostream>

using namespace std;

//Templated class used to create a generic class
//This class is a node, holds and sets value 
template <typename genericType>
class Node
{
private:
	genericType data;
	shared_ptr <Node<genericType>> next_Node = nullptr;
	shared_ptr <Node<genericType>> previous_Node = nullptr;
	

public:
	//Constructors
	Node()
	{
		data = NULL;
	}
	Node(genericType newData)
	{
		data = newData;
	}
	Node(genericType newData, shared_ptr<Node> next, shared_ptr<Node> prev)
	{
		data = newData;
		next_Node = next;
		previous_Node = prev;
	}
	//Deconstructors
	~Node()
	{
		
		next_Node = nullptr;
		previous_Node = nullptr;
	}

	//Methods
	genericType get_Data()
	{
		return data;
	}

	//Change/set data in the node
	void set_Data(genericType newData)
	{
		data = newData;
	}

	//Get nrct node in list 
	shared_ptr<Node> get_Next()
	{
		return next_Node;
	}

	//Set the node next in the list
	void set_Next(shared_ptr<Node> next)
	{
		this->next_Node = next;
	}

	//Get the node previous to this 
	shared_ptr<Node> get_Prev()
	{
		return previous_Node;
	}

	//Set the node previous to this node
	void set_Prev(shared_ptr<Node> prev)
	{
		this->previous_Node = prev;
	}
};

//Templated class used to create a generic class
//Will find, insert, delete and print information about the nodes within it. See Methods.
//This class will also maintain sentinel nodes
template <typename genericType>
class DoublyLinkedList
{
private:
	shared_ptr<Node<genericType>> head = nullptr;
	shared_ptr<Node<genericType>> tail = nullptr;

public:
	//Constructor
	DoublyLinkedList()
	{
		//create head as shared pointer
		head = make_shared<Node<genericType>>();
		head->set_Data(NULL);
		head->set_Next(tail);
		head->set_Prev(nullptr);
		//create tail as shared pointer
		tail = make_shared<Node<genericType>>();
		tail->set_Data(NULL);
		tail->set_Next(nullptr);
		tail->set_Prev(head);
	}

	//Methods
	//Find data in list by looping through list
	shared_ptr<Node<genericType>> find(genericType dataToFind)
	{
		auto currentNode = head;
		while (currentNode->get_Data() != dataToFind)
		{
			currentNode = currentNode->get_Next();
			//If currentNode == tail then node wasn't found, so return nullptr
			if (currentNode == tail)
			{
				return nullptr;
			}
		}
		//return currentNode (smartpointer)
		return currentNode;
	}

	//Insert node into the list
	void insertNode(genericType newData)
	{
		//Create a new node
		shared_ptr <Node<genericType>> nodeToInsert = make_shared<Node<genericType>>();
		nodeToInsert->set_Data(newData);
		//Set previous of new node to the previous of tail
		nodeToInsert->set_Prev(tail->get_Prev());
		//Set next of new node to tail
		nodeToInsert->set_Next(tail);
		//Set previous of this node's next node to this node
		nodeToInsert->get_Next()->set_Prev(nodeToInsert);
		//Set next of this node's previous node to this node
		nodeToInsert->get_Prev()->set_Next(nodeToInsert);
	}

	//Delete a node by removing its previous and next pointers
	void deleteNode(genericType dataToDelete)
	{
		auto nodeToDeletePtr = this->find(dataToDelete);
		if (nodeToDeletePtr == nullptr)
		{
			cout << "Error: Cannot Delete, Node Not Found" << endl;
		}
		if (nodeToDeletePtr == head)
		{
			cout << "Error: Cannot Delete Head Sentinel Node" << endl;
		}
		else if (nodeToDeletePtr == tail)
		{
			cout << "Cannot Delete Tail Sentinel Node" << endl;
		}
		else
		{
			auto nodeToDelete = *nodeToDeletePtr;
			//set this nodes next's previous to this nodes previous
			nodeToDelete.get_Next()->set_Prev(nodeToDelete.get_Prev());
			//set this nodes previous's next to this nodes next
			nodeToDelete.get_Prev()->set_Next(nodeToDelete.get_Next());
			//set this node's next to a null ptr
			nodeToDelete.set_Next(nullptr);
			//set this node's previous to a null ptr
			nodeToDelete.set_Prev(nullptr);
			//Delete the pointers
			nodeToDeletePtr.reset();
		}
	}

	//Display all data in the list by looping through and printing all data to the console
	void displayList()
	{
		auto node1 = head->get_Next();
		while (node1 != tail)
		{
			//print the data
			cout << node1->get_Data() << endl;
			//et node1 to next node in list
			node1 = node1->get_Next();
		}
	}

	//Sort the linked list using bubble sort
	void bubbleSort()
	{
		//variable used to drop out of loop
		bool swapped = true;
		//node to consider in the checks
		auto currentNode = head->get_Next();
		//if currentNode is tail at this point then the loop is empty
		if (currentNode == tail) return;
		do
		{
			//set swapped to false
			swapped = false;
			while (currentNode != tail)
			{
				//check if our data is greater than the nextNodes data
				if (currentNode->get_Data() > currentNode->get_Next()->get_Data() && currentNode->get_Next() != tail)
				{
					//if it is swap forward
					swap(currentNode, currentNode->get_Next());
					swapped = true;
				}
				else
				{
					currentNode = currentNode->get_Next();
				}
			}
			currentNode = head->get_Next();
		} while (swapped != false);
	}

	// Sort the linked list using selection sort
	void selectionSort()
	{
		//current threshhold node
		auto currentNode = head->get_Next();
		//minimum value found
		auto minNode = currentNode;
		//current node to use as iterable
		auto iterNode = currentNode;
		//if currentNode is tail at this point then the loop is empty
		if (currentNode == tail) return;
		do
		{
			//while we haven't searched the whole list
			while (iterNode != tail)
			{
				//if the current minimum node's data is greater than the iterable's data
				if (minNode->get_Data() > iterNode->get_Data())
				{
					//set minimum to the iterable
					minNode = iterNode;
				}
				iterNode = iterNode->get_Next();
			}
			//perform swap
			swap(currentNode, minNode);
			//set the search threshhold to the next value
			currentNode = currentNode->get_Next();
			//reset the search variables to the new threshhold
			minNode = currentNode;
			iterNode = currentNode;
		} while (currentNode != tail);
	}


	//Swap the data in the two nodes
	void swap(shared_ptr<Node<genericType>> current, shared_ptr<Node<genericType>> next)
	{
		Node<genericType> temp;
		temp.set_Data(current->get_Data());
		current->set_Data(next->get_Data());
		next->set_Data(temp.get_Data());
	}
};