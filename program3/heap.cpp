//Zhengqi Xi
#include "heap.h"
#include "hashTable.h"
#include <vector>
#include <string>
#include <iostream>
#include <climits>
using namespace std;

heap::heap(int capacity){
	mapping = new hashTable(capacity);
	data.resize(capacity+1); // Because we're not using the 0th index
	maxCapacity = capacity;
}

int heap::insert(const string &id, int key, void *pv){
	if ((size+1) > maxCapacity){
		return 1;
	}
	if (mapping->contains(id)){
		return 2;
	}
	++size;
	data[size].id = id;
	data[size].key = key;
	data[size].pData = pv;
	mapping->insert(data[size].id);
	if (size != 1){
		percolateUp(size);
	}		
	return 0;
}


int heap::setKey(const string &id, int key){
	bool exists;
	node* value = static_cast<node*>(mapping->getPointer(id, exists)); //static_cast supposedly better than just (node*)
	if (!exists){
		return 1;
	}
	bool up; //whether to percolate up or down
	int oldKey = value->key;
	value->key = key;
	up = key < oldKey;
	if (up){
		percolateUp(value->pos);
	} else {
		percolateDown(value->pos);
	}
	return 0;	
}

int heap::remove(const string &id, int *key, void *ppData){
	bool exists;
	node* value = static_cast<node*>(mapping->getPointer(id, exists));
	if (exists){
		if (key != nullptr){
			*key = value->key;
		}
		setKey(id, INT_MIN);
		return deleteMin(nullptr, nullptr, ppData);
	}
	return 1;	
}

int heap::deleteMin(string *id, int *key, void *ppData){
	if (size == 0){
		return 1;
	}
	mapping->remove(data[1].id);	
	if (id != nullptr){
		*id = data[1].id;
	}
	if (key != nullptr){
		*key = data[1].key;
	}
	if (ppData != nullptr){
		*(static_cast<void **> (ppData)) = data[1].pData;
	}
	data[1] = data[size];
	--size;
	percolateDown(1);
	return 0;
}

void heap::percolateUp(int posCur){
	node value = data[posCur];
	while (posCur > 1){
		if (value < data[(posCur/2)]){ // Compare against parent
			data[posCur] = data[(posCur/2)];
			data[posCur].pos = posCur;
			if (!mapping->setPointer(data[posCur].id, &data[posCur])){
				cout << "Error, percolate up went wrong" << endl;
				return;
			}
			posCur /=2;
		} else {
			break;
		}
	}
	data[posCur] = value;
	data[posCur].pos = posCur;
	mapping->setPointer(value.id, &data[posCur]);
}

void heap::percolateDown(int posCur){
	node value = data[posCur];
	int smallerKey = 1; // the position of the child node with the smaller key value. Or the position of the child node that exists
	while (posCur < size){
		if ((2*posCur) > size){ // Edge case #1: There are no children, end percolation
			break;
		} else if ((2*posCur + 1) > size){ //Edge case #2: There is no right node, only compare with the left node
			smallerKey = 2*posCur;
		} else {
			smallerKey = (data[2*posCur] > data[2*posCur + 1]) ? (2*posCur + 1) : (2*posCur); //Find the position of the smaller node
		}
		if (value > data[smallerKey]) { //Compare against smaller node
			data[posCur] = data[smallerKey];
			data[posCur].pos = posCur;
			if (!mapping->setPointer(data[posCur].id, &data[posCur])){
				cout << "Error, percolate down went wrong" << endl;
				return;
			}
			posCur = smallerKey;	
		} else {
			break;
		}	
	}
	data[posCur] = value;
	data[posCur].pos = posCur;
	mapping->setPointer(value.id, &data[posCur]);
}
