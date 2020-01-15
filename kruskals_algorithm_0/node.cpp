#include "node.h"

Node::Node()
{
	next = nullptr;
	vertex = -1;
	vertexBase = -1;
}

void Node::setNext(Node* newValue)
{
	next = newValue;
}

Node* Node::getNext()
{
	return next;
}

void Node::setVertex(int newValue)
{
	vertex = newValue;
}

int Node::getVertex()
{
	return vertex;
}

void Node::setVertexBase(int newValue)
{
	vertexBase = newValue;
}

int Node::getVertexBase()
{
	return vertexBase;
}

