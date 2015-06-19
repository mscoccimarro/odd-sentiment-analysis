#include "SetEntrenamiento.h"
#include "ProcesadorSetEntrenamiento.h"
#include "RandomForest.h"
#include <iostream>
#include <string>
using namespace std;

int main (int argc, char* argv[]){
	string trainingFile, testFile;
	
	if(argc > 1) {
		trainingFile = argv[1];
	}

	if(argc > 2) {
		testFile = argv[2];
	}

}
