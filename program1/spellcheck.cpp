#include "spellCheck.h"
#include "hashTable.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include<ctime>
#include <cctype>
#define initSize 50000 //seems like a good size to start, assuming average dictionary
using namespace std;
spellCheck::spellCheck(){
	dictionary = new hashTable(initSize);
}
spellCheck::~spellCheck(){
	delete(dictionary);
}
void spellCheck::loadDictionary(){
	cout << "Enter name of dictionary: ";
	string filename;
	cin >> filename;
	ifstream load(filename.c_str());
	if (!load) {
		cerr << "Dictionary not found: " << filename << endl;
		exit(1);
	}
	clock_t t1 = clock();
	string entry;
	load >> entry;
	while (!load.eof()){
		convertToLowerCase(entry); //Convert all letters to lowercase before inserting
		dictionary->insert(entry);
		load >> entry;
	}
	clock_t t2 = clock();
	double difference = ((double)(t2-t1))/CLOCKS_PER_SEC;
	cout << "Total time (in seconds) to load dictionary: " << difference << endl;
	load.close();
}
void spellCheck::checkFile(){
	loadDictionary();
	cout << "Enter name of input file: ";
	string input;
	cin >> input;
	ifstream toCheck(input.c_str());
	if (!toCheck) {
		cerr << "Input file not found: " << input << endl;
		exit(1);
	}
	cout << "Enter name of output file: ";
	string output;
	cin >> output;
	ofstream toWrite;
	toWrite.open(output);
	string line;
	clock_t t1 = clock();
	do {
		getline(toCheck, line); //Get each line of the file, then process it
		processLine(line, toWrite);
	} while (!toCheck.eof());
	clock_t t2 = clock();
	double difference = ((double)(t2-t1))/CLOCKS_PER_SEC;
	cout << "Total time (in seconds) to check document: " << difference << endl;
	toCheck.close();
	toWrite.close();
}
void spellCheck::processLine(string &line, ofstream &toWrite){
	static int linenumber = 0;
	++linenumber;
	convertToLowerCase(line);
	int start;
	string word;
	start = findNotDelim(line, 0);
	bool containsNumber = false;
	for (int i = start; i <= line.size(); ++i){
		if (start == -1){
			break;
		}
		if (line[i]<=57 && line[i]>=48){ //if it has a number, don't check against dictionary
			containsNumber = true;
		}
		if (!((line[i]<=90 && line[i]>=65) || (line[i]<=122 && line[i]>=97) || (line[i]<=57 && line[i]>=48) || line[i] == 45 || line[i] == 92 || line[i] == 39)){
			word = line.substr(start, i-start);
			if (word.size() > 20){
				toWrite << "Long word at line " << linenumber << ", starts: " << word.substr(0,20) << endl;
			} else if (!dictionary->contains(word) && !containsNumber){
				toWrite << "Unknown word at line " << linenumber << ": " << word << endl;
			}
			containsNumber = false;
			i = start = findNotDelim(line, i);
		}
		
	}
}
int spellCheck::findNotDelim(string &line, int start){
	for (int i = start; i < line.size(); ++i){
		if ((line[i]<=90 && line[i]>=65) || (line[i]<=122 && line[i]>=97) || (line[i]<=57 && line[i]>=48) || line[i] == 45 || line[i] == 92 || line[i] == 39){
			return i;
		}
	}
	return -1;
}
void spellCheck::convertToLowerCase(string &entry){
	for (int i = 0; i < entry.size(); ++i){
		entry[i] = tolower(entry[i]);
	}
}