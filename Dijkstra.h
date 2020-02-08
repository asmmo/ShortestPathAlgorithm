#pragma once
#include<string>
#include<limits>
#include<algorithm>
#include<unordered_map>
#include"pch.h"

#pragma once
#include<iostream>
using namespace std::string_literals;


struct Vertex
{
	Vertex() = default;
	Vertex(std::string str) :name{ str } , d{ std::numeric_limits<size_t>::max() } {}

	std::vector<Vertex*> adjacencyList{}; // Adjacency list
	bool known{};
	size_t d;
	std::string name{};
	Vertex* path{};

};


class Graph {


	std::unordered_map<std::string, size_t> edgesMap{};
	std::unordered_map<std::string, Vertex*> verticesMap{};
	std::vector<Vertex*> vertices{};

public:

	void insertVertex(Vertex& v)
	{

		vertices.push_back(&v);
		verticesMap.insert(std::make_pair(v.name, &v));

	}

	void insertEdge(const Vertex & v1, const Vertex &v2, size_t capacity) {

		edgesMap.insert(std::make_pair("C"s + v1.name + v2.name, capacity));
	}

	void printPathOf(const Vertex*   v, size_t counter=0)
	{ 
		++counter;
		if (v->path)
		{
			
			printPathOf(v->path, counter);
		}
		std::cout << v->name;
		if (counter != 1) std::cout << " => ";
	}


	void printPaths()
	{
		for (auto vPtr : vertices)
		{
			std::cout << "\n" << vPtr->name << ": ";
			printPathOf(vPtr);
		}

	}


	void dijkstra(Vertex*);


};










/*
***************************************************************************
The running time depends on how the vertices are                          *
manipulated, which we have yet to consider. If we use the obvious         *
algorithm of sequentially scanning the vertices to find the minimum dv,   *
each phase will take O(|V|) time to find the minimum, and thus O(|V|2)    *
time will be spent finding the minimum over the course of the algorithm.  *
The time for updating dw is constant per update, and there is at most one *
update per edge for a total of O(|E|). Thus, the total running time       *
is O(|E|+|V|^2) = O(|V|^2). If the graph is dense, with |E| = O(|V|^2),   *
this algorithm is not only simple but also essentially                    *
optimal, since it runs in time linear in the number of edgesMap.             *

**************************************************************************/


/*--------------Pesudo code----------------*/
/*
void Graph::dijkstra( Vertex s )
{
	for each Vertex v
	{
		v.dist = INFINITY;
		v.known = false;
	}
	s.dist = 0;
	
	while( there is an unknown distance vertex )
	{
		Vertex v = smallest unknown distance vertex;
		v.known = true;
		
		for each Vertex w adjacent to v
			if( !w.known )
			{
				DistType cvw = cost of edge from v to w;

				if( v.dist + cvw < w.dist )
				{
					// Update w
					decrease( w.dist to v.dist + cvw );
					w.path = v;
				}
			}
	}
}

*/


/*Implementation*/
void Graph::dijkstra(Vertex* v)
{
	//Preparation
	for (auto& vertexPtr : vertices) {
		vertexPtr->d = std::numeric_limits<size_t>::max();
		vertexPtr->known = false; std::cout << vertexPtr->name;
	}
	v->d = 0;


	auto cmp{ [](Vertex* left, Vertex* right) {
		return left->d > right->d;
		} };

	std::vector<Vertex*> pQueue{ vertices };
	std::sort(pQueue.begin(), pQueue.end(), cmp);


	//The implementation
	while (!pQueue.empty())
	{
		Vertex* vertexPtr = pQueue.back();
		pQueue.pop_back();
		vertexPtr->known = true;

		for (auto& vertexPtrNeighbour : vertexPtr->adjacencyList) {
			if (!vertexPtrNeighbour->known)
			{
				size_t Cvw = edgesMap["C"s + vertexPtr->name + vertexPtrNeighbour->name];//cost of edge from v to w;

				if (vertexPtr->d + Cvw < vertexPtrNeighbour->d)
				{
					// Update w
					vertexPtrNeighbour->d = vertexPtr->d + Cvw;
					vertexPtrNeighbour->path = vertexPtr;
					std::sort(pQueue.begin(), pQueue.end(), cmp);
				}

			}
		}
	}
}

