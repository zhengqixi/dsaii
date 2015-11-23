#include "graph.h"
#include "hashTable.h"
#include "heap.h"
#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
using namespace std;

graph::graph(){
	nodeTable = new hashTable(0);
	cout << "Please enter the name of the input file" << endl;
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
	for (int i = 0; i < nodeList.size(); ++i){
		cout << "name of node: " << nodeList[i]->name << endl;
		nodeList[i]->printEdge();
	}
}
