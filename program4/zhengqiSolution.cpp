//Zhengqi Xi
#include <cctype>
#include <iostream>
#include <fstream>
#include <string>
using namespace std;
int data[1005][1005];
int main(){
	string inputFile, outputFile;
	cout << "Enter name of input file: " ;
	cin >> inputFile;
	cout << "Enter name of output file: ";
	cin >> outputFile;
	ifstream readIn(inputFile.c_str());
	if (!readIn){
		cerr << "File not found!" << endl;
		return 1;
	}
	ofstream readOut(outputFile.c_str());
	if (!readOut){
		cerr << "Cannot open output file!" << endl;
		return 1;
	}
	data[0][0] = 0;
	string first, second, merge;
	int larger = 0;
	bool up = false;
	char comp;
	int i, j, traceback;
	while (!readIn.eof()){
		readIn >> first >> second >> merge;
		// fill in the top row
		for (i = 0; i < first.length(); ++i){
			data[0][i+1] = (merge[data[0][i]] == first[i]) ? data[0][i] + 1 : data[0][i]; 
		}
		//fill in first column
		for (i = 0; i < second.length() + 1; ++i){
			data[i+1][0] = (merge[data[i][0]] == second[i]) ? data[i][0] + 1 : data[i][0]; 
		}
		//first in rest of matrix as necessary
		for (i = 1; i < second.length() + 1; ++i){
			for (j = 1; j < first.length() + 1; ++j){
				up = (data[i-1][j] > data[i][j-1]);
				larger = (up) ? data[i-1][j] : data[i][j-1];	
				comp = (up) ? second[i-1] : first[j-1];
				data[i][j] = (comp == merge[larger]) ? larger + 1 : larger;
			}
		}
		--j;
		--i;
		if (data[i][j] != merge.length()){
			readOut << "*** NOT A MERGE ***" << endl;
		} else {
			larger = data[i][j];		
			while (larger != 0){
				if (i == 0){
					--j;
					larger = data[i][j];
					merge[larger] = toupper(merge[larger]);
					continue;
				}
				if (j == 0){
					--i;
					larger = data[i][j];
					continue;
				}
				if (data[i-1][j] == (larger-1)){
					--i;
					larger = data[i][j];
				} else {
					--j;
					larger = data[i][j];
					merge[larger] = toupper(merge[larger]);
				}	
			}
			readOut << merge << endl;
		}
	}
}
