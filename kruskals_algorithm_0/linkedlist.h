#pragma once

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

#include "node.h"

class LinkedList
{
private:

	Node* head;

public:

	void setHead(Node* newValue);
	Node* getHead();

	void insertNode(int numberOfVertex, int numberOfBaseVertex);

	void print();

	void removeLinkedList();

	int checkHowManyElement(LinkedList** adjacencyList, int v); // DFS

	LinkedList();

	~LinkedList();
};

#endif

