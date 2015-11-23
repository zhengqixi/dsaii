#include "graph.h"
#include "hashTable.h"
#include "heap.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <stack>
using namespace std;

graph::graph(){
	nodeTable = new hashTable(0);
	cout << "Please enter the name of the input file: ";
	string name;
	cin >> name;
	ifstream readIn(name.c_str());
	string node1, node2;
	int distance;
	while (!readIn.eof()){
		readIn >> node1 >> node2 >> distance;
		if (!nodeTable->contains(node1)){
			node* newNode = new node();
			newNode->name = node1;
			nodeTable->insert(node1, newNode);
			nodeList.push_back(newNode);
		}
		if (!nodeTable->contains(node2)){
			node* newNode = new node();
			newNode->name = node2;
			nodeTable->insert(node2, newNode);
			nodeList.push_back(newNode);
		}
		bool existsV1;
		node* V1 = static_cast<node*>(nodeTable->getPointer(node1, existsV1));
		bool existsV2;
		node* V2 = static_cast<node*>(nodeTable->getPointer(node2, existsV2));
		if (existsV1 && existsV2){
			V1->insertEdge(V2, distance);
		} else {
			cerr << "Catastrophic error!" ;
			exit(1);
		}
	}
	readIn.close();
}
void graph::dijkstra(){
	if (nodeList.empty()){
		cout << "Give up! Go home! You're drunk!" << endl;
		return;
	}
	string vertex;
	while(1){
		cout << "Please enter a starting node: " ;
		cin >> vertex;
		if (nodeTable->contains(vertex)){
			break;
		}
	}
	bool existsV1;
	node* V1 = static_cast<node*>(nodeTable->getPointer(vertex, existsV1));
	if (!existsV1){
		cerr << "Catastrophic error!" ;
		exit(1);
	}
	V1->distance = 0;
	V1->previous = V1;
	heap* queue = new heap(nodeList.size());
	for (int i = 0; i < nodeList.size(); ++i){
		queue->insert(nodeList[i]->name, nodeList[i]->distance, &nodeList[i]);
	}	
	int distance;
	node* nextVertex;
	while (queue->deleteMin(&vertex, &distance, &nextVertex) == 0){
		bool b;
		nextVertex = static_cast<node*>(nodeTable->getPointer(vertex, b)); //Janky workaround that needs fixing
		nextVertex->known = true;
		if (nextVertex->previous == nullptr){
			continue;
		}
		for(int i = 0; i < nextVertex->edgeList.size(); ++i){
	 		if (!nextVertex->edgeList[i].next->known){
				int newDistance = nextVertex->edgeList[i].cost + distance; //Possibly risky with overflow involved, but shouldn't be an issue since visited nodes will probably be significantly less than INT_MAX
				if (newDistance >= nextVertex->edgeList[i].next->distance){
					continue;
				}	
				nextVertex->edgeList[i].next->distance = newDistance;
				queue->setKey(nextVertex->edgeList[i].next->name, nextVertex->edgeList[i].next->distance);
				nextVertex->edgeList[i].next->previous = nextVertex;
			}
		}
	}
	string output;
	cout << "Please enter name of the output file: ";
	cin >> output;
	ofstream readOut(output.c_str());
	for (int i = 0; i < nodeList.size(); ++i){
		readOut << nodeList[i]->name << ": ";
		if (nodeList[i]->previous == nullptr){
			readOut << "NO PATH" << endl;
		} else {
			readOut << nodeList[i]->distance << " ";
			stack<string> printStack;
			if (nodeList[i] != V1){
				printStack.push(nodeList[i]->name);
			}
			node* traceBack = nodeList[i]->previous;
			while (traceBack != V1){
				printStack.push(traceBack->name);
				traceBack = traceBack->previous;
			}
			readOut << "[" << V1->name;
			while (!printStack.empty()){
				readOut << ", " << printStack.top();
				printStack.pop();
			}
			readOut << "]" << endl;
		}
	}
}
