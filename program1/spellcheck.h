#ifndef _SPELLCHECK_H
#define _SPELLCHECK_H
#include "hashTable.h"
#include <fstream>
class spellCheck {
	public:
		spellCheck();
		void checkFile();
		
		//test functions
		void printDictionary();
		void remove(const std::string &key);
		void contains(const std::string &key);
		void insert(const std::string &key);
		
	private:
		hashTable *dictionary;
		void loadDictionary();
		void convertToSpace(std::fstream &input);
		void convertToLowerCase(std::string &entry);
};
#endif