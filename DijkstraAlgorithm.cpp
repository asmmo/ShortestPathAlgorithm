#include"pch.h"
#include"Dijkstra.h"


int main() {

	Vertex v1("v1"s);
	Vertex v2("v2"s);
	Vertex v3("v3"s);
	Vertex v4("v4"s);
	Vertex v5("v5"s);
	Vertex v6("v6"s);
	Vertex v7("v7"s);

	v1.adjacencyList = { &v2, &v4 };
	v2.adjacencyList = { &v4, &v5 };
	v3.adjacencyList = { &v1, &v6 };
	v4.adjacencyList = { &v3, &v6, &v7, &v5 };
	v5.adjacencyList = { &v7 };
	v7.adjacencyList = { &v6 };

	Graph g;

	g.insertVertex(v1);
	g.insertVertex(v2);
	g.insertVertex(v3);
	g.insertVertex(v4);
	g.insertVertex(v5);
	g.insertVertex(v6);
	g.insertVertex(v7);

	g.insertEdge(v1, v2, 2);
	g.insertEdge(v1, v4, 1);
	g.insertEdge(v2, v4, 3);
	g.insertEdge(v2, v5, 10);
	g.insertEdge(v3, v1, 4);
	g.insertEdge(v3, v6, 5);
	g.insertEdge(v4, v3, 2);
	g.insertEdge(v4, v6, 8);
	g.insertEdge(v4, v7, 4);
	g.insertEdge(v4, v5, 2);
	g.insertEdge(v5, v7, 6);
	g.insertEdge(v7, v6, 1);

	g.dijkstra(&v1);
	g.printPaths();

}