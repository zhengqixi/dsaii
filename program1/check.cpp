#include "spellcheck.h"
#include <iostream>
using namespace std;
int main(){
	spellCheck *check = new spellCheck();
	check->checkFile();
	return 0;
}