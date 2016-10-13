//: C0:.cpp
#include "ProcesadorSetEntrenamiento.h"
#include "SetEntrenamiento.h"
#include <iostream>
#include <string>
#include <map>
#include "wordScorer.h"

using namespace std;

int main() {
	ProcesadorSetEntrenamiento *pSetEntrenamiento = new ProcesadorSetEntrenamiento();
	SetEntrenamiento *setEntrenamiento = new SetEntrenamiento();
	pSetEntrenamiento->procesarSet(setEntrenamiento);

	map<string, string> words = getWordScore(10,setEntrenamiento);	

	for(map<string, string>::iterator it = words.begin(); it != words.end(); it++) {
		cout << it->first << " => " << it->second << endl;
	}
} ///:~

