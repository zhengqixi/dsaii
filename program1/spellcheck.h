#ifndef _SPELLCHECK_H
#define _SPELLCHECK_H
#include "hashTable.h"
class spellCheck {
	public:
		spellCheck();
		bool checkFile();
	private:
		hashTable *dictionary;
		void loadDictionary();
		
};
#endif