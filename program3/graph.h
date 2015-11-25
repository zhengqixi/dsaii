//Zhengqi Xi
#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <string>
#include <climits>
#include "hashTable.h"
#include <iostream>
class graph {
	public:
		graph();
		void read(std::string &name);
		void dijkstra(std::string &vertex);
		bool contains(std::string &vertex);
	private:
		class node {
			private:
				//Not sure if a triply nested class hiearchy is the best way to go, but it seems logical in my head
				class edge {
					public:
						node* next;
						int cost = 1;
				};
			public:
				bool known = false;
				std::string name = "";
				node* previous = nullptr;
				int distance = INT_MAX;
				std::vector<edge> edgeList;
				//This one should be fine as an inline...
				void insertEdge(node* next, int cost = 1){
					edge newEdge;
					newEdge.next = next;
					newEdge.cost = cost;
					edgeList.push_back(newEdge);
				}
		};
		std::vector<node*> nodeList;
		hashTable* nodeTable;
		void output(node* V1, double difference);
};
#endif
