#include <iostream>
#include "linkedlist.h"

LinkedList::LinkedList()
{
	head = nullptr;
}

void LinkedList::insertNode(int numberOfVertex, int numberOfBaseVertex)
{
	if (head == nullptr)
	{
		Node* temp = new Node();
		head = temp;
		temp->setVertex(numberOfVertex);
		temp->setVertexBase(numberOfBaseVertex);

		return;
	}
	else
	{
		Node* temp = new Node();
		Node* temp2 = head;

		while (temp2->getNext() != nullptr)
		{
			temp2 = temp2->getNext();
		}

		temp2->setNext(temp);
		temp->setVertex(numberOfVertex);
		temp->setVertexBase(numberOfBaseVertex);
		temp->setNext(nullptr);

	}
}

void LinkedList::print()
{
	if (head == nullptr)
	{
		std::cout << "Lista jest pusta";

		return;
	}
	else
	{
		Node* temp = head;

		std::cout << temp->getVertex() << " " << temp->getVertexBase();

		std::cout << std::endl;

		while (temp->getNext() != nullptr)
		{
			temp = temp->getNext();

			std::cout << temp->getVertex() << " " << temp->getVertexBase();

			std::cout << std::endl;
		}
	}
}

LinkedList::~LinkedList()
{
	if (head != nullptr)
	{
		removeLinkedList();
	}
	else
	{
		std::cout << "Lista jest pusta" << std::endl;
	}
}

void LinkedList::removeLinkedList()
{
	Node* temp = head;
	Node* temp2 = head;

	while (temp->getNext() != nullptr)
	{
		temp = temp->getNext();
	}

	while (temp2->getNext()->getNext() != nullptr)
	{
		temp2 = temp2->getNext();
	}

	delete temp;
	temp2->setNext(nullptr);
}

void LinkedList::setHead(Node* newValue)
{
	head = newValue;
}

Node* LinkedList::getHead()
{
	return head;
}

int LinkedList::checkHowManyElement(LinkedList** adjacencyList, int v)
{
	Node* temp = adjacencyList[v]->getHead();

	int howManyElements = 1;

	while (temp->getNext() != nullptr)
	{
		temp = temp->getNext();
		howManyElements++;
	}

	return howManyElements;
}