#include "spellcheck.h"
#include <iostream>
using namespace std;
int main(){
	spellCheck *check = new spellCheck();
	check->checkFile();
	cout << sizeof(long) << endl;
	cout << sizeof(unsigned int) << endl;
	return 0;
}