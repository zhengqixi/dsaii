//Zhengqi Xi
#ifndef _HASHTABLE_H
#define _HASHTABLE_H
#include <vector>
#include <string>
class hashTable {
 public:
	hashTable(int size);
	
	bool insert(const std::string &key, void *pv = nullptr); 
	
	bool contains(const std::string &key);
	
	void *getPointer(const std::string &key, bool &b);
	
	bool setPointer(const std::string &key, void *pv);
	
	bool remove(const std::string &key);
	
 private:
	class hashItem {
		public: //Default values set. C++11 feature
			std::string key = "";
			bool isOccupied = false;
			bool isDeleted = true;
			void *pv = nullptr; //nullptr because C++11. 
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
 
