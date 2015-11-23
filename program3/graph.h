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
		void dijkstra();
	private:
		class node {
			private:
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
				void insertEdge(node* next, int cost = 1){
					edge newEdge;
					newEdge.next = next;
					newEdge.cost = cost;
					edgeList.push_back(newEdge);
				}
				void printEdge(){
					for (int i = 0; i < edgeList.size(); ++i){
						std::cout << name << " Links to " << edgeList[i].next->name << " at cost " << edgeList[i].cost << std::endl;
					}	
				}
		};
		std::vector<node*> nodeList;
		hashTable* nodeTable;
};
#endif
