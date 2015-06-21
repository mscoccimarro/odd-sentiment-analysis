#include "SetEntrenamiento.h"
#include "ProcesadorSetEntrenamiento.h"
#include "RandomForest.h"
#include <iostream>
#include <fstream>
#include <string>
using namespace std;

void getAciertos(const char* trainingFile, const char* testFile){
	cout << endl <<
			"/--------------------------------------/" << endl;
	cout << "         Obteniendo Porcentaje..." << endl;
	cout << "/--------------------------------------/" << endl;

	int cantidadPositivos = 0;

	ifstream clasificaciones(testFile);
	ifstream data(trainingFile);

	string lineaLabeled;
	string lineaClasificada;


	string delimitador =  "\t";
	int i = 0;
	if (data.is_open() && clasificaciones.is_open()){
		getline(data,lineaLabeled); // Ignoro la linea de titulos

		while (i < 25000){

			//Analisis del labeled
			getline(data,lineaLabeled);
			string id_review = lineaLabeled.substr(0, lineaLabeled.find(delimitador));
			lineaLabeled.erase(0, id_review.length() + delimitador.length());

			id_review.erase(0,1);
			id_review.erase(id_review.length()-1,1);
			lineaLabeled.erase(1,lineaLabeled.size()-1);
			string sentimiento = lineaLabeled;

			//Analisis del clasificacion
			getline(clasificaciones,lineaClasificada);
			string id_review_clasificada = lineaClasificada.substr(0, lineaClasificada.find("Clasificacion"));
			id_review_clasificada = id_review_clasificada.substr(4, 20);
			id_review_clasificada = id_review_clasificada.substr(0, id_review_clasificada.size()-1);
			string clasificacion = lineaClasificada.substr(lineaClasificada.find("Clasificacion:")+14,lineaClasificada.size());
			
			if (id_review == id_review_clasificada){
	/*			cout << "reviews iguales " << id_review << endl;
				cout << "sentimiento " << sentimiento << endl;
				cout << "clasifacion " << clasificacion << endl;*/
				if (sentimiento == clasificacion)
					cantidadPositivos++;
			}else{
				cout << "No conincidieron las reviews en la review numero: " << id_review << " linea: " << i << endl;
			}
			i++;
		}

		cout << endl << "Aciertos: " << cantidadPositivos << " de " << i << endl;
		cout << "Porcentaje: " << (double) cantidadPositivos/i << "%"<< endl;
		clasificaciones.close();
		data.close();

	}else{
		cout << "NO abrio el archivo" << endl;
	}

}



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

	SetEntrenamiento* setEntrenamiento = new SetEntrenamiento();
	ProcesadorSetEntrenamiento* procesadorSetEntrenamiento = new ProcesadorSetEntrenamiento(trainingFile);
	procesadorSetEntrenamiento->procesarSet(setEntrenamiento);
	delete procesadorSetEntrenamiento;

	if (!setEntrenamiento->vacio()){
		vector<string>* vectorCaracteristicas = new vector<string>;
		vector<vector<vector<string>* >* >* vectorDeMatrices = new vector<vector<vector<string>* >* >;

		setEntrenamiento->get_N_caracteristicas(14, vectorCaracteristicas, vectorDeMatrices);

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

		map<string,double> top_n_palabras = setEntrenamiento->getTopN();

		SetReviews *setTest = new SetReviews();
		ProcesadorSet* procesadorSetReviews = new ProcesadorSet(testFile);
		procesadorSetReviews->procesarSet(setTest);
		delete procesadorSetReviews;

		if (!setTest->vacio()){
			/* csv para kaggle /*
			vector<string> ids = setTest->getIds();
			ofstream out("clasificaciones.csv");
			out<<"\"id\",\"sentiment\"" << endl;
			cout << "Generando consultas del set de test..." << endl;
			for (vector<string>::iterator id = ids.begin(); id != ids.end(); id++){
				map<string,string> * consulta = setTest->generarConsultas(*id,top_n_palabras);
				bool clasificacion_review = randomForest->tomarDecision(consulta);
				out << *id << "," << clasificacion_review << endl;
			}
			out.close();
			*/
			/* txt para pruebas*/
			vector<string> ids = setTest->getIds();
			ofstream out("clasificaciones.txt");
			for (vector<string>::iterator id = ids.begin(); id != ids.end(); id++){
				map<string,string> * consulta = setTest->generarConsultas(*id,top_n_palabras);
				bool clasificacion_review = randomForest->tomarDecision(consulta);
				out << "ID: " << *id << " Clasificacion:" << clasificacion_review << endl;
			}
			out.close();			
			/* **** */
		}
		else cout << "Ocurrio un problema al intentar procesar el set de test." << endl;
		delete setTest;
	}
	else cout << "Ocurrio un problema al intentar procesar el set de entrenamiento." << endl;
	delete setEntrenamiento;

	getAciertos (trainingFile, "clasificaciones.txt");
	return 0;

}


