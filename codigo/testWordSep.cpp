//: C0:.cpp
#include <iostream>
#include <string>
#include <map>
#include "wordScorer.h"

using namespace std;

int main() {
	map<string, string> words = getWordScore(50);	

	for(map<string, string>::iterator it = words.begin(); it != words.end(); it++) {
		cout << it->first << " => " << it->second << endl;
	}
} ///:~

