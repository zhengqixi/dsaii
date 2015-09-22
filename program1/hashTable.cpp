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
	int pos = hash(key);
	if (!data[pos].isDeleted){ //Linear probe
		while (pos < data.capacity() && !data[pos].isDeleted ){ //Check position first so you don't go out of bounds. && will automatically evaluate false if pos == capacity
			++pos;
		}
		if (pos == data.capacity()){ //Wrapped to the beginning
			pos = 0;
			while(!data[pos].isDeleted){
				++pos;
			}
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
	for (int i = 0; i < data.capacity(); ++i){
		data[i].isOccupied = false; //faster than clear(). Lazy clearing
		data[i].isDeleted = true;
	}
	data.resize(capacity);
	filled = 0;
	for (int i = 0; i < temp.capacity(); ++i){ //Probably not most efficent way, but saves me a few lines of code since I can reuse insert
		if (!temp[i].isDeleted){
			insert(temp[i].key, temp[i].pv);
		}
	}
	return true;
}
int hashTable::findPos(const string &key){
	int pos = hash(key);
	if (data[pos].key.compare(key) == 0){ //Linear prob
		return pos;
	} else {
		while (pos < data.capacity() && data[pos].isOccupied && data[pos].key.compare(key) != 0){
			++pos;
		}
		if (pos == data.capacity()){
			pos = 0;
			while(data[pos].isOccupied && data[pos].key.compare(key) != 0){
				++pos;
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
		filled--;
		return true;
	}
}
bool hashTable::contains(const string &key){
	int pos = findPos(key);
	return (pos != -1) ? true : false;
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