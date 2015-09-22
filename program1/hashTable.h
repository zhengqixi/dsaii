#ifndef _HASHTABLE_H
#define _HASHTABLE_H
#include <vector>
#include <string>
class hashTable {
 public:
	hashTable(int size);
	bool insert(const std::string &key, void *pv = NULL);
	bool contains(const std::string &key);
	void *getPointer(const std::string &key, bool *b = NULL); //Not yet implemented
	bool setPointer(const std::string &key, void *pv); //Not yet implemented
	bool remove(const std::string &key);
 private:
	class hashItem {
	public: //Default values set. C++11 feature
		std::string key = "";
		bool isOccupied = false;
		bool isDeleted = true;
		void *pv = NULL;
	};
	int capacity = 0; // The current capacity of the hash table.
	int filled = 0; // Number of occupied items in the table.
	std::vector<hashItem> data; //Vector that stores the data
	unsigned int hash(const std::string &key);
	int findPos(const std::string &key);
	bool rehash();
	static int getPrime(int size);
};

#endif
 
