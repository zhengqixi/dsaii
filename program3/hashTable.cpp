//Zhengqi
#include "hashTable.h"
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#define loadFactor 0.5 //in case we want to change the load factor
using namespace std;

hashTable::hashTable(int size){
	capacity = getPrime(size);
	data.resize(capacity); //Planned to use a try catch but don't think it'll fail after some consideration
}

int hashTable::getPrime(int size){
	static vector<int> primes = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 
	196613, 393241, 786433, 1572869, 3145739, 786433, 1572869, 3145739, 6291469, 12582917,  25165843, 
	50331653,  100663319, 201326611, 402653189, 805306457, 1610612741}; //may as well keep the lower primes, doesn't really hurt.
	static int i = 0; //Just increment i next time we need it
	if (i == 0){
		while (i < primes.size()){
			if (primes[i]*loadFactor > size){ // ensure a good ratio for hashing
				return primes[i];
			}
			++i;
		}
	}
	return (i == primes.size()) ? primes[i] : primes[++i];
}

bool hashTable::insert(const string &key, void *pv ){
	if (key.compare("") == 0){
		return false;
	}
	int pos = hash(key);
	while (data[pos].isOccupied && pos < data.capacity()){
		if (data[pos].key.compare(key) == 0 && !data[pos].isDeleted){
			return false;
		} else if (data[pos].key.compare(key) == 0 && data[pos].isDeleted){
			--filled;
			break;
		}
		++pos;
		if (pos == data.capacity()){
			pos = 0;
		}
	}
	data[pos].isOccupied = true;
	data[pos].isDeleted = false;
	data[pos].key = key;
	data[pos].pv = pv;
	filled++;
	if (((float)filled/(float)capacity) > loadFactor){
		return rehash();
	}
	return true;
}

bool hashTable::rehash(){
	capacity = getPrime(capacity);
	vector<hashItem> temp = data;
	for (int i = 0; i < data.size(); ++i){
		data[i].isOccupied = false; //faster than clear(). Lazy clearing
		data[i].isDeleted = true;
	}
	data.resize(capacity);
	if (data.size() != capacity){
		return false;
	}
	filled = 0;
	for (int i = 0; i < temp.size(); ++i){ //Probably not most efficent way, but saves me a few lines of code since I can reuse insert
		if (!temp[i].isDeleted){
			insert(temp[i].key, temp[i].pv);
		}
	}
	return true;
}

int hashTable::findPos(const string &key){
	int pos = hash(key);
	if (data[pos].key.compare(key) == 0 && !data[pos].isDeleted){ 
		return pos;
	} else {
		while (data[pos].isOccupied && pos < data.capacity()){
			if (data[pos].key.compare(key) == 0 && !data[pos].isDeleted){
				break;
			}
			++pos;
			if (pos == data.capacity()){
				pos = 0;
			}
		}
	}
	return (data[pos].key.compare(key) == 0 && !data[pos].isDeleted) ? pos : -1;
}

bool hashTable::remove(const string &key){
	int pos = findPos(key);
	if (pos == -1){
		return false;
	} else {
		data[pos].isDeleted = true;
		data[pos].key = "";
		return true;
	}
}

bool hashTable::contains(const string &key){
	return (findPos(key) != -1);
}

unsigned int hashTable::hash(const string &key){
	//Hash function found on:http://stackoverflow.com/questions/98153/whats-the-best-hashing-algorithm-to-use-on-a-stl-string-when-using-hash-map, provided by user George V. Reilly and Paul Larson
	unsigned int pos = capacity;
	const char *s = key.c_str();
	while (*s){
		pos *= 101;
		pos += (*s++);
	}
	return pos%capacity;
}

void* hashTable::getPointer(const string &key, bool &b){
	int pos = findPos(key);
	if (pos != -1){
		b = true;
		return data[pos].pv;
	} else{
		b = false;
		return nullptr;
	}
}

bool hashTable::setPointer(const string &key, void *pv){
	int pos = findPos(key);
	if (pos != -1){
		data[pos].pv = pv;
		return true;
	} else {
		return false;
	}
}

