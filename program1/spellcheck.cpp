#include "spellCheck.h"
#include "hashTable.h"
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <cstdlib>
#include<ctime>
#define initSize 20 //seems like a good size to start, assuming average dictionary
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
	if (load.eof()) {
		cerr << "Dictionary is empty" << endl;
		exit(1);
	}
	clock_t t1 = clock();
	string entry;
	load >> entry;
	while (!load.eof()){
		dictionary->insert(entry);
		load >> entry;
	}
	clock_t t2 = clock();
	double difference = ((double)(t2-t1))/CLOCKS_PER_SEC;
	cout << "Total time (in seconds) to load dictionary: " << difference << endl;
}

bool spellCheck::checkFile(){
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