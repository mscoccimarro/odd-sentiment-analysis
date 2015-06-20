#include "SetEntrenamiento.h"
#include "ProcesadorSetEntrenamiento.h"
#include "RandomForest.h"
#include <iostream>
#include <string>
using namespace std;

int main (int argc, char* argv[]){
	const char* trainingFile = NULL;
	const char*	testFile = NULL;
	
	if(argc > 1) {
		trainingFile = argv[1];
	}

	if(argc > 2) {
		testFile = argv[2];
	}

	string valorPositivo = "1";

	SetEntrenamiento* set = new SetEntrenamiento();
	ProcesadorSetEntrenamiento* procesadorSetEntrenamiento = new ProcesadorSetEntrenamiento(trainingFile);
	procesadorSetEntrenamiento->procesarSet(set);
	vector<string>* vectorCaracteristicas = new vector<string>;
	vector<vector<vector<string>* >* >* vectorDeMatrices = new vector<vector<vector<string>* >* >;

	set->get_N_caracteristicas(20, vectorCaracteristicas, vectorDeMatrices);

	RandomForest* randomForest = new RandomForest(vectorCaracteristicas, valorPositivo);

	for (unsigned int i = 0; vectorDeMatrices != NULL && i < vectorDeMatrices->size(); i++){
		vector<vector<string>* >* matriz = vectorDeMatrices->at(i);
		randomForest->insertarSetDeDatos(matriz);
		randomForest->armarArbolDeDecision();
	}

}
