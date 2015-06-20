#include "ProcesadorSet.h"
#include "ProcesadorReviews.h"
#include "UtilesTexto.h"
#include <iomanip>
#include <vector>
#include <iostream>
#include <fstream>
#include <time.h>
#define MAX_REVIEWS_PROC 5000
#define TOTAL_REVIEWS 25000
#define SEC_PER_MIN 60
#define OK 0
using namespace std;

ProcesadorSet::ProcesadorSet(){ this->archivoSet = "testData.tsv"; }

ProcesadorSet::ProcesadorSet(const char* fileName){ this->archivoSet = fileName; }

void ProcesadorSet::mensaje_inicial(){ 
	cout << "---------------------------------------------------------------\n";
	cout << "Procesando set de test...\n"; 
	cout << "---------------------------------------------------------------\n";
}

void ProcesadorSet::mensaje_final(){ cout << "Set de test procesado: "; }

void ProcesadorSet::error_set(){ cout << "ERROR: No se pudo procesar correctamente el archivo de test.\n\n"; }
		
void ProcesadorSet::error_stopWords(){ cout << "ERROR: No se pudo procesar correctamente el archivo de stop words.\n\n"; }

void ProcesadorSet::obtenerReview(SetReviews *setR,std::string linea){
	string delimitador = "\t";
	int resultado;
	ProcesadorReviews *pReviews = new ProcesadorReviews();
	UtilesTexto *util = new UtilesTexto();
	
	string id_review = linea.substr(0, linea.find(delimitador));
	linea.erase(0, id_review.length() + delimitador.length());
	// Borro comillas del ID
	id_review.erase(0,1);
	id_review.erase(id_review.length()-1,1);
		
	vector<string> contenido_review = pReviews->obtenerPalabras(linea,&resultado);

	if (resultado==OK) setR->agregarReview(id_review,contenido_review);
	else setR->vaciar();

	delete pReviews;
	delete util;
}

/* 
 * procesarSet(): 
 * Devuelve un SetReviews con los id's de cada review del set y sus respectivos contenidos (tambien los sentimientos si esta procesando
 * el set de entrenamiento). 
 * En caso de que ocurra algun error al procesar el set (no se pudieron eliminar correctamente las stop words, 
 * no se pudo procesar el archivo de entrenamiento, etc) devuelve el SetReviews vacio. 
 * */
void ProcesadorSet::procesarSet(SetReviews *setR){
	int cant_reviews_procesados = 0,cantidad_anterior = 0;
	string linea;
	clock_t t = clock();
    ifstream data(this->archivoSet);
	mensaje_inicial();
	if (data.is_open()){
		
		getline(data,linea); // Ignoro la linea de titulos
		
		while (getline(data,linea)){
			if (cant_reviews_procesados == cantidad_anterior + MAX_REVIEWS_PROC && !setR->vacio()) {
				cout<< "Reviews procesados: " << cant_reviews_procesados << " de " << TOTAL_REVIEWS << endl << endl;
				cantidad_anterior = cant_reviews_procesados;
			}
			obtenerReview(setR,linea);
			cant_reviews_procesados ++;			
		}
		
		data.close();
		
		if (setR->vacio()) error_stopWords();
		else {
			mensaje_final();
			t = clock() - t;
			cout << fixed << setprecision(2) << ((float)t/CLOCKS_PER_SEC)/SEC_PER_MIN << " minutos transcurridos.\n\n";
		}
	}
	else error_set();
}
