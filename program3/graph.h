#ifndef GRAPH_H
#define GRAPH_H
#include <vector>
#include <string>
#include <climits>
#include "hashtable.h"
class graph {
	public:
		graph(std::string name);
		void dijkstra();
	private:
		class node {
			public:
				bool known = false;
				std::string name = "";
				node* previous = nullptr;
				int distance = INT_MAX;
				class edge {
					node* next;
					int cost = 1;
				}
				std::vector<edge> edgeList;
		}
		std::vector<node*> nodesList;
		hashTable* nodesTable;

#endif
