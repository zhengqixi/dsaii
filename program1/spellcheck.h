#ifndef _SPELLCHECK_H
#define _SPELLCHECK_H
#include "hashTable.h"
#include <fstream>
class spellCheck {
	public:
		spellCheck();
		~spellCheck();
		void checkFile(); //Actual function to use for file checking
	private:
		hashTable *dictionary;
		void loadDictionary();
		void processLine(std::string &line, std::ofstream &toWrite); //Process each line of file to be checked
		int findNotDelim(std::string &line, int start); //gets entry to the next character that starts a valid word, in case of multiple whitespaces
		void convertToLowerCase(std::string &entry); //Converts everything to lower case, so that the spellchecker isn't case sensitive
};
#endif