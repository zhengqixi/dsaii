#include "spellCheck.h"
#include <iostream>

using namespace std;
int main(){
	spellCheck *check = new spellCheck();
	check->checkFile();
	cout << check->contains("and") << endl;
	cout << check->contains("change") << endl;
	return 0;
}