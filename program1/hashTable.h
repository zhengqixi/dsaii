#ifndef _HASHTABLE_H
#define _HASHTABLE_H

#include <vector>
#include <string>

class hashTable {

 public:

	// The constructor initializes the hash table.
	// Uses getPrime to choose a prime number at least as large as
	// the specified size for the initial size of the hash table.
	hashTable(long size);

	// Insert the specified key into the hash table.
	// If an optional pointer is provided,
	// associate that pointer with the key.
	// Returns true on success,
	// false if rehash fails.
	bool insert(const std::string &key, void *pv = NULL);

	// Check if the specified key is in the hash table.
	// If so, return true; otherwise, return false.
	bool contains(const std::string &key);

	// Get the pointer associated with the specified key.
	// If the key does not exist in the hash table, return NULL.
	// If an optional pointer to a bool is provided,
	// set the bool to true if the key is in the hash table,
	// and set the bool to false otherwise.
	void *getPointer(const std::string &key, bool *b = NULL);

	// Set the pointer associated with the specified key.
	// Returns true on success,
	// false if the key does not exist in the hash table.
	bool setPointer(const std::string &key, void *pv);

	// Delete the item with the specified key.
	// Returns true on success,
	// false if the specified key is not in the hash table.
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

	std::vector<hashItem> data; // The actual entries are here.

	// The hash function.
	long hash(const std::string &key);

	// Search for an item with the specified key.
	//returns -1 if not found
	long findPos(const std::string &key);

	// The rehash function; makes the hash table bigger.
	// Returns true on success, false if memory allocation fails.
	bool rehash();

	// Return a prime number at least as large as size.
	// Uses a precomputed sequence of selected prime numbers.
	static long getPrime(long size);
};

#endif //_HASH_H
 
