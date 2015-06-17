#include "ProcesadorSetEntrenamiento.h"
#include "ProcesadorReviews.h"
#include "UtilesTexto.h"
#include <iostream>
#include <fstream>
#define OK 0
#define ARCH_DATOS "labeledTrainData.tsv"

using namespace std;

ProcesadorSetEntrenamiento::ProcesadorSetEntrenamiento(){ this->archivoSet = "labeledTrainData.tsv"; }

void ProcesadorSetEntrenamiento::mensaje_inicial(){ 
	cout << "---------------------------------------------------------------\n";
	cout << "Procesando set de entrenamiento...\n"; 
	cout << "---------------------------------------------------------------\n";
}

void ProcesadorSetEntrenamiento::mensaje_final(){ cout << "Set de entrenamiento procesado: "; }

void ProcesadorSetEntrenamiento::error_set(){ cout << "ERROR: No se pudo procesar correctamente el archivo de entrenamiento.\n\n"; }

void ProcesadorSetEntrenamiento::obtenerReview(SetReviews *setR,string linea){
	int resultado;
	string id_review, sentimiento_review, delimitador = "\t";
	vector<string> contenido_review;
	size_t inicio_linea = 0;		
	ProcesadorReviews *pReviews = new ProcesadorReviews();
	UtilesTexto *util = new UtilesTexto();

	id_review = linea.substr(inicio_linea, linea.find(delimitador));
	linea.erase(inicio_linea, id_review.length() + delimitador.length());
	// Borro comillas del ID
	id_review.erase(0,1);
	id_review.erase(id_review.length()-1,1);
		
	sentimiento_review = linea.substr(inicio_linea,linea.find(delimitador));
	linea.erase(inicio_linea, sentimiento_review.length() + delimitador.length());

	contenido_review = pReviews->obtenerPalabras(linea,&resultado);

	if (resultado==OK) ((SetEntrenamiento*)setR)->agregarReview(id_review,sentimiento_review,contenido_review);
	else setR->vaciar();

	delete pReviews;
	delete util;
}
