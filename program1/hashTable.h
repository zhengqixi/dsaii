#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <vector>
#include <string>

class hashTable {

 public:

	hashTable(long size);

	bool insert(const std::string &key, void *pv = NULL);

	bool contains(const std::string &key);

	void *getPointer(const std::string &key, bool *b = NULL);

	bool setPointer(const std::string &key, void *pv);

	bool remove(const std::string &key);

	//test functions
	void print();
	
 private:

	class hashItem {
	public:
		std::string key = "";
		bool isOccupied = false;
		bool isDeleted = true;
		void *pv = NULL;
	};

	long capacity = 0; // The current capacity of the hash table.
	long filled = 0; // Number of occupied items in the table.

	std::vector<hashItem> data;

	long hash(const std::string &key);

	long findPos(const std::string &key);

	bool rehash();

	static long getPrime(long size);
};

#endif
 
