#include "hashTable.h"
#include <string>
#include <vector>
#include <iostream>
#include <cstdlib>
#include "MurmurHash3.h"
#define loadFactor 0.5 //in case we want to change the load factor
using namespace std;

hashTable::hashTable(long size){
	capacity = getPrime(size);
	try{
		data.resize(capacity);
	} catch(exception &e){
		cerr << e.what() << endl;
		exit(0);
	}
}

long hashTable::getPrime(long size){
	static vector<long> primes = {53, 97, 193, 389, 769, 1543, 3079, 6151, 12289, 24593, 49157, 98317, 196613, 393241, 786433, 1572869, 3145739};
	static int i = 0;
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
	long pos = hash(key);
	if (!data[pos].isDeleted){
		while (pos < data.capacity() && !data[pos].isDeleted ){ //Check position first so you don't go out of bounds. && will automatically evaluate false if pos == capacity
			++pos;
		}
		if (pos == data.capacity()){
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
	for (long i = 0; i < data.capacity(); ++i){
		data[i].isOccupied = false; //faster than clear()
		data[i].isDeleted = true;
	}
	try{
		data.resize(capacity);
	} catch (exception& e){
		cerr << e.what() << endl;
		return false;
	}
	filled = 0;
	for (long i = 0; i < temp.capacity(); ++i){
		if (!temp[i].isDeleted){
			insert(temp[i].key, temp[i].pv);
		}
	}
	return true;
}

long hashTable::findPos(const string &key){
	long pos = hash(key);
	if (data[pos].key.compare(key) == 0){
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
	long pos = findPos(key);
	if (pos == -1){
		return false;
	} else {
		data[pos].isDeleted = true;
		filled--;
		return true;
	}
}

bool hashTable::contains(const string &key){
	long pos = findPos(key);
	return (pos != -1) ? true : false;
}

long hashTable::hash(const string &key){
	return 0;
}
//test function
void hashTable::print(){
	for (int i = 0; i < data.size(); ++i){
		cout << data[i].key << endl;
	}
}