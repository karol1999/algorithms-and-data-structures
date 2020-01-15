// kruskal algorithm, finding minimum spanning tree (subgraph)
// graf nieskierowany, z wagami

#include "linkedlist.h"
#include "node.h"
#include <iostream>

constexpr auto max = 2147483647;

class Edge
{
private:

	int source;
	int destination;
	int weight;

public:

	Edge();

	void setSource(int newValue);
	int getSource();

	void setDestination(int newValue);
	int getDestination();

	void setWeight(int newValue);
	int getWeight();

};

Edge::Edge()
{
	source = -1;
	destination = -1;
	weight = -1;
}

void Edge::setSource(int newValue)
{
	source = newValue;
}

int Edge::getSource()
{
	return source;
}

void Edge::setDestination(int newValue)
{
	destination = newValue;
}

int Edge::getDestination()
{
	return destination;
}

void Edge::setWeight(int newValue)
{
	weight = newValue;
}

int Edge::getWeight()
{
	return weight;
}

class Graph
{
private:

	int v; // number of vertices
	int e; // number of edges
	Edge* edge;

public:

	Graph();

	void setV(int newValue);
	int getV();

	void setE(int newValue);
	int getE();

	void setEdge(Edge* newValue);
	Edge* getEdge();

	void print(int edgeNumber);

};

Graph::Graph()
{
	v = -1;
	e = -1;
	edge = nullptr;
}

void Graph::setV(int newValue)
{
	v = newValue;
}

int Graph::getV()
{
	return v;
}

void Graph::setE(int newValue)
{
	e = newValue;
}

int Graph::getE()
{
	return e;
}

void Graph::setEdge(Edge* newValue)
{
	edge = newValue;
}

Edge* Graph::getEdge()
{
	return edge;
}

void Graph::print(int edgeNumber)
{
	std::cout << " " << edge[edgeNumber].getSource() << " " << edge[edgeNumber].getDestination() << " " << edge[edgeNumber].getWeight() << std::endl;

	return;
}

bool isWorthIt(int source, int destination, Graph* myGraph, int numberOfEdges);
int findClosestEmptyOne(Graph* myGraph, int numberOfEdges);

LinkedList** kruskalMST(Graph* myGraph, int numberOfEdges, int numberOfVertices);
int findParent(int child, int* disjointSubsetArray);
void unionDisjointSubsetArray(int headOfASet2, int headOfASet1, int* disjointSubsetArray);

int main()
{
	int numberOfVertices, numberOfEdges;

	std::cout << "Prosze podaj liczbe wierzcholkow ";
	std::cin >> numberOfVertices;

	std::cout << std::endl;

	std::cout << "Prosze podaj liczbe krawedzi ";
	std::cin >> numberOfEdges;

	std::cout << std::endl;

	Graph* graph = new Graph();

	graph->setV(numberOfVertices);
	graph->setE(numberOfEdges);

	graph->setEdge(new Edge[numberOfEdges]);

	LinkedList** adjacencyList = new LinkedList * [numberOfVertices]; // tworzenie listy s¹siedztwa

	for (int i = 0; i < numberOfVertices; i++)
	{
		adjacencyList[i] = new LinkedList();
	}

	int choice = 0;
	int value = 0;

	for (int i = 0; i < numberOfVertices; i++) // uzupelnienie listy sasiedztwa
	{
		for (int j = 0; j < numberOfVertices; j++)
		{
			std::cout << "Czy wierzcholek o numerze " << i << " ma miec polaczenie z wierzcholkiem o numerze " << j << "?" << std::endl;
			std::cout << "Jezeli TAK wpisz cyfre 1, a jezeli NIE wpisz cyfre 0" << std::endl;
			std::cout << "Twoj wybor to: ";
			std::cin >> choice;

			if (choice == 1)
			{
				adjacencyList[i]->insertNode(j, i);

				// value = adjacencyList[i]->checkHowManyElement(adjacencyList, i);

				std::cout << "Podaj prosze wage polaczenia ";
				std::cin >> choice;

				std::cout << std::endl;

				if (isWorthIt(i, j, graph, numberOfEdges))
				{
					if (findClosestEmptyOne(graph, numberOfEdges) == -1)
					{
						goto end;
					}

					value = findClosestEmptyOne(graph, numberOfEdges);

					graph->getEdge()[value].setSource(i);
					graph->getEdge()[value].setDestination(j);
					graph->getEdge()[value].setWeight(choice);
				}
			}

			std::cout << std::endl;
		}
	}

end:

	std::cout << "WYSWIETLENIE LISTY SASIEDZTWA" << std::endl << std::endl;

	for (int i = 0; i < numberOfVertices; i++) // wyswietlenie listy sasiedztwa
	{
		adjacencyList[i]->print();
		std::cout << std::endl;
	}

	std::cout << "WYSWIETLENIE POLACZEN GRAFU" << std::endl << std::endl;

	std::cout << "source" << " " << "destination" << " " << "weight" << std::endl;

	for (int i = 0; i < numberOfEdges; i++) // wyswietlenie krawêdzie (source, destination, weight)
	{
		std::cout << "Numer krawedzi: " << i << " ";
		graph->print(i);
	}

	std::cout << "Kruskal's minimum spanning tree " << std::endl;

	LinkedList** adjacencyListOfKruskalsMST = kruskalMST(graph, numberOfEdges, numberOfVertices);

	for (int i = 0; i < numberOfVertices - 1; i++) // wyswietlenie listy sasiedztwa
	{
		adjacencyListOfKruskalsMST[i]->print();
		std::cout << std::endl;
	}

	// usuwanie zaalokowanych struktur

	//for (int i = 0; i < numberOfVertices; ++i)
	//{
		//delete[] adjacencyList[i];
	//}

	//delete[] adjacencyList;

	//for (int i = 0; i < numberOfVertices - 1; ++i)
	//{
		//delete[] adjacencyListOfKruskalsMST[i];
	//}

	//delete[] adjacencyListOfKruskalsMST;

	delete graph;

	return 0;
}

bool isWorthIt(int source, int destination, Graph* myGraph, int numberOfEdges) // czy ju¿ nie ma takiego po³¹czenia (graf nieskierowany)
{
	for (int i = 0; i < numberOfEdges; i++)
	{
		if ((myGraph->getEdge()[i].getSource() == source) && (myGraph->getEdge()[i].getDestination() == destination))
		{
			return false;
		}
		else if ((myGraph->getEdge()[i].getSource() == destination) && (myGraph->getEdge()[i].getDestination() == source))
		{
			return false;
		}
	}

	return true;
}

int findClosestEmptyOne(Graph* myGraph, int numberOfEdges) // znajdujemy najbli¿szy mo¿liwy do w³o¿enia
{
	for (int i = 0; i < numberOfEdges; i++)
	{
		if ((myGraph->getEdge()[i].getSource() == -1) && (myGraph->getEdge()[i].getDestination() == -1))
		{
			return i;
		}
	}

	return -1; // there is no empty space
}

LinkedList** kruskalMST(Graph* myGraph, int numberOfEdges, int numberOfVertices)
{
	int min = max;

	int child1, child2, iteratorForIncludedArray;

	bool* included = new bool[numberOfEdges];

	for (int i = 0; i < numberOfEdges; i++)
	{
		included[i] = false;
	}

	int* disjointSubsetArray = new int[numberOfVertices];

	for (int i = 0; i < numberOfVertices; i++)
	{
		disjointSubsetArray[i] = -1;
	}

	LinkedList** adjacencyListOfKruskalsMST = new LinkedList * [numberOfVertices - 1]; // tworzenie listy s¹siedztwa

	for (int i = 0; i < numberOfVertices - 1; i++)
	{
		adjacencyListOfKruskalsMST[i] = new LinkedList();
	}

	int i = 0;
	int flag = 0;

	while (i < numberOfEdges - 1) // numberOfVertices - 1
	{
		min = max;

		for (int j = 0; j < numberOfEdges; j++)
		{
			if (included[j] == false && myGraph->getEdge()[j].getWeight() < min)
			{
				min = myGraph->getEdge()[j].getWeight();

				iteratorForIncludedArray = j; // tak to byœmy zgubili dla której iteracji znaleŸliœmy min

				child1 = myGraph->getEdge()[j].getSource();
				child2 = myGraph->getEdge()[j].getDestination();
			}
		}

		if (findParent(child1, disjointSubsetArray) != findParent(child2, disjointSubsetArray)) // nale¿¹ do innych setów (nie maj¹ wspólnego rodzica)
		{
			adjacencyListOfKruskalsMST[child1]->insertNode(child2, child1); // wtedy gdy nale¿¹ do innych setów, mo¿emy z nich zrobiæ minimalne drzewo rozpinaj¹ce (subgrafa)

			unionDisjointSubsetArray(findParent(child1, disjointSubsetArray), findParent(child2, disjointSubsetArray), disjointSubsetArray);
			i++;
		}

		included[iteratorForIncludedArray] = true;

		for (int i = 0; i < numberOfEdges; i++)
		{
			if (included[i] == false)
			{
				flag = 0;
				break;
			}
			else
			{
				flag++;
			}
		}

		if (flag == numberOfEdges)
		{
			delete[] included;
			delete[] disjointSubsetArray;

			return adjacencyListOfKruskalsMST;
		}

		flag = 0;

	}

	delete[] included;
	delete[] disjointSubsetArray;

	return adjacencyListOfKruskalsMST;
}

int findParent(int child, int* disjointSubsetArray)
{
	int temporary = child;

	while (disjointSubsetArray[temporary] > 0) // means it belongs to someone, it isnt in itself root (parent)
	{
		temporary = disjointSubsetArray[temporary];
	}

	return temporary; // return parent
}

void unionDisjointSubsetArray(int headOfASet2, int headOfASet1, int* disjointSubsetArray)
{
	if (disjointSubsetArray[headOfASet2] < disjointSubsetArray[headOfASet1]) // pierwotnie disjointSubsetArray[headOfASet2] mia³ wiecej elementow pod sob¹ wiêc on zosta³ rootem nowego subgrafu
	{
		disjointSubsetArray[headOfASet2] = disjointSubsetArray[headOfASet2] + disjointSubsetArray[headOfASet1];
		disjointSubsetArray[headOfASet1] = headOfASet2; // teraz jego ojcem bedzie headOfASet2
	}
	else // tutaj jest na odwrót po prostu
	{
		disjointSubsetArray[headOfASet1] = disjointSubsetArray[headOfASet2] + disjointSubsetArray[headOfASet1];
		disjointSubsetArray[headOfASet2] = headOfASet1;
	}
}