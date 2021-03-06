//Zhengqi Xi
#ifndef _HEAP_H
#define _HEAP_H
#include <vector>
#include <string>
#include "hashTable.h"

class heap{
	public:
		heap(int capacity);	
		int insert(const std::string &id, int key, void *pv = nullptr);
		int setKey(const std::string &id, int key);
		int remove(const std::string &id, int *key = nullptr, void *ppData = nullptr);
		int deleteMin(std::string *id = nullptr, int *key = nullptr, void *ppData = nullptr);
	private:
		class node{
			public:
				std::string id = "";
				int key = 0;
				void *pData = nullptr;
				int pos = 0; //Using a function to determine the position feels unncessary when we can just store it without wasting too much space. a million int is only about 4MB
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
		//int getPos(node *pn); will not use as mentioned above. Subject to change 
		int size = 0;
		int maxCapacity;	
};
#endif
