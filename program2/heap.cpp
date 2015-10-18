#include "heap.h"
#include "hashTable.h"
#include <vector>
#include <string>
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
	node temp;
	temp.id = id;
	temp.key = key;
	temp.pData = pv;
	data[size] = temp;
	mapping->insert(id, &data[size]);
	if (size != 1){
		percolateUp(size);
	}		
	return 0;
}

void heap::percolateUp(int posCur){
	node value = data[posCur];
	while (posCur >= 1){
		if (value < data[(posCur/2)]){
			data[posCur] = data[(posCur/2)];
			posCur /=2;
		} else {
			break;
		}
	}
	data[posCur] = value;
}

void heap::percolateDown(int posCur){

