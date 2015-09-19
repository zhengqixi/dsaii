#ifndef _SPELLCHECK_H
#define _SPELLCHECK_H
#include "hashTable.h"
class spellCheck {
	public:
		spellCheck();
		bool checkFile();
		
		//test functions
		void printDictionary();
		void remove(const std::string &key);
		void contains(const std::string &key);
		void insert(const std::string &key);
		
	private:
		hashTable *dictionary;
		void loadDictionary();
		
};
#endif