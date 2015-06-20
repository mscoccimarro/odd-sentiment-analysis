#include "SetEntrenamiento.h"
#include "ProcesadorSetEntrenamiento.h"
#include "RandomForest.h"
#include <iostream>
#include <fstream>
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

	set->get_N_caracteristicas(5, vectorCaracteristicas, vectorDeMatrices);

	RandomForest* randomForest = new RandomForest(vectorCaracteristicas, valorPositivo);

	for (unsigned int i = 0; vectorDeMatrices != NULL && i < vectorDeMatrices->size(); i++){
		vector<vector<string>* >* matriz = vectorDeMatrices->at(i);
		if(matriz != NULL) {
			randomForest->insertarSetDeDatos(matriz);
			cout << "Arbol " << i << endl;
			cout << "/---------------------------------------/" << endl << endl;
			randomForest->armarArbolDeDecision();
		}	
	}
	
	map<string,double> top_n_palabras = set->getTopN();
	SetReviews *setTest = new SetReviews();
	ProcesadorSet* procesadorSetReviews = new ProcesadorSet(testFile);
	procesadorSetReviews->procesarSet(setTest);
	vector<string> ids = setTest->getIds();
	ofstream out("clasificaciones.txt");	
	for (vector<string>::iterator id = ids.begin(); id != ids.begin()+2; id++){
		map<string,string> * consulta = setTest->generarConsultas(*id,top_n_palabras);
		for (map<string,string>::iterator it = consulta->begin(); it != consulta->end(); it++){
			cout << "Palabra: " << it->first << " Valor: " << it->second << endl;
		}
		bool clasificacion_review = randomForest->tomarDecision(consulta);
		out << "ID: " << *id << " Clasificacion:" << clasificacion_review << endl;
	}
	out.close();

}
