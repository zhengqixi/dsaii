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
	clock_t t1 = clock();
	string entry;
	load >> entry;
	while (!entry.empty()){
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