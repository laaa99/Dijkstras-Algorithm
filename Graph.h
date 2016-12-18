/*
Name: Lucy Tran
Date: 11 - 30 - 16
Header File : Graph
MA6 : Dijkstra's Algorithm

Edited computeShortestPath (dijkstra's algorithm)

A graph contains an unordered map of vertices (key = id of vertex).
*/

#ifndef GRAPH_H
#define GRAPH_H
#include <unordered_map>
#include <queue>
#include <functional>

#include "Vertex.h"
using namespace std;
class Graph
{
	unordered_map<int, Vertex> _vertices;

public:

	void addVertex(Vertex vertex)
	{
		_vertices[vertex.getId()] = vertex;
	}

	//Returns a map of distances indexed by vertices : distances = shortest path between *start and other vertices
	unordered_map<Vertex, int> computeShortestPath(Vertex *start)
	{
		//holds known distances
		unordered_map<Vertex, int> distances;
		//cout << "something: " << distances[*start] << endl; ALL ARE SET TO 0

		//underlying heap
		priority_queue<Vertex, vector<Vertex>, PathWeightComparer> dijkstra_queue{};

		//reset start's path weight
		start->setPathWeight(0);

		//make sure that the starting vertex is in the graph
		if (_vertices[start->getId()] == *start) {

			//push on starting vertex
			dijkstra_queue.push(*start);

			//while queue not empty
			while (!dijkstra_queue.empty()) {

				//View the top of heap and delete
				Vertex vertex = dijkstra_queue.top();
				dijkstra_queue.pop();

				//get edges of vertex
				unordered_map<Vertex *, int> edges = vertex.getEdges();
				
				//for each Vertex "other" adjacent to the Vertex "vertex" (bucket contains ptr to vertex and edge weight)
				for (auto &bucket : edges) {

					 //Initializations
					int weight = bucket.second; //weight of edge between "other" and "vertex"
					int vertexDistance = distances[vertex]; //distance between *start and "vertex"
					int newDistance = vertexDistance + weight; //distance of "other" to "vertex"
					Vertex other = *(bucket.first); //vertex adjacent to "vertex"

					//Top of heap not known (in distances)?
					if (distances[other] == 0) {

						//make known
						distances[other] = newDistance; //weight of edge added to distance
						other.setPathWeight(distances[other]); //setting path weight

						//push on outgoing edges
						dijkstra_queue.push(other); 
					}

					//Top of heap known (in distance)
					else {
						//if shorter path found
						if (newDistance < distances[other]) {
							distances[other] = newDistance; //weight of edge added to distance
						}
					}
				}
			}
		}

		return distances;
	}
};

#endif
