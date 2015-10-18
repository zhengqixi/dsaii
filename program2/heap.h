#ifndef _HEAP_H
#define _HEAP_H
#include <vector>
#include <string>
#include "hashTable.h"

class heap{
	public:
		heap(int capacity);	
		int insert(const std::string &id, int key, void *pv = nullptr);
		int setKey(const std::string &id, int key, void *pv = nullptr);
		int remove(const std::string &id, int *key = nullptr, void *pv = nullptr);
		int deleteMin(const std::string *id, int *key = nullptr, void *pv = nullptr);
	private:
		class node{
			public:
				std::string id = "";
				int key;
				void *pData = nullptr;
				bool operator < (const node &b){
					return key < b.key;
				}
				bool operator > (const node &b){
					return key > b.key;
				}
		};
		hashTable *mapping;
		std::vector<node> data;
		void percolateUp(int posCur);
		void percolateDown(int posCur);
		int getPos(node *pn);
		int size = 0;
		int maxCapacity;	
};
#endif
