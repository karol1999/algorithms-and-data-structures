#pragma once

#ifndef NODE_H_
#define NODE_H_

class Node
{
private:

	Node* next;

	int vertex;
	int vertexBase;

public:

	Node();

	void setNext(Node* newValue);
	Node* getNext();

	void setVertex(int newValue);
	int getVertex();

	void setVertexBase(int newValue);
	int getVertexBase();

};

#endif

