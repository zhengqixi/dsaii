#include "spellCheck.h"
#include "hashTable.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include<ctime>
#include <cctype>
#include <sstream>
#define initSize 50000 //seems like a good size to start, assuming average dictionary
using namespace std;

spellCheck::spellCheck(){
	dictionary = new hashTable(initSize);
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
		convertToLowerCase(entry);
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
	int lineNumber = 1;
	string parse;
	getline(toCheck, parse);
	stringstream parser(parse);
	while (!toCheck.eof()){
		parser >> parse;
		while (!parser.eof()){
			if (parse.size()>20){
				toWrite << "Long word at line " << lineNumber << ", starts: " << parse.substr(0,20) << endl;
			} else if(!dictionary->contains(parse)){
				toWrite << "Unknown word at line " << lineNumber << ": " << parse << endl;
			}
			parse.clear();
			parser >> parse;
		}
		++lineNumber;
		getline(toCheck, parse);
		parser.str(parse);
	}
	toCheck.close();
	toWrite.close();
}

void spellCheck::convertToSpace(fstream &input){
	char check;
	char space = 32;
	while (!input.eof()){
		check = input.peek();
		if (!(check <= 90 && check >= 65) && !(check <= 122 && check >= 97) && check != 45 && check != 34 && check != 39){
			input.put(space);
		} else{
			input.get(check);
		}
	}
}
void spellCheck::convertToLowerCase(string &entry){
	for (int i = 0; i < entry.size(); ++i){
		entry[i] = tolower(entry[i]);
	}
}
//test functions
void spellCheck::printDictionary(){
	dictionary->print();
}
void spellCheck::contains(const string &key){
	if (dictionary->contains(key)){
		cout << "Has key: " << key << endl;
	} else {
		cout << "Does not have: " << key << endl;
	}
}

void spellCheck::remove(const string &key){
	if (dictionary->remove(key)){
		cout << "removed key: " << key << endl;
	} else {
		cout << "Key does not exist: " << key << endl;
	}
}
void spellCheck::insert(const string &key){
	dictionary->insert(key);
}