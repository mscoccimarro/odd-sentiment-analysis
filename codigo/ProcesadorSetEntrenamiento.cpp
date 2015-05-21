#include "ProcesadorSetEntrenamiento.h"
#include "ProcesadorReviews.h"
#include "SetEntrenamiento.h"
#include "UtilesTexto.h"
#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#define OK 0
#define ERROR -1

using namespace std;

void ProcesadorSetEntrenamiento::error_setEntrenamiento(){
	cout << "Error: No se pudo procesar correctamente el archivo de entrenamiento.\n";
}
void ProcesadorSetEntrenamiento::error_stopWords(){
	cout << "Error: No se pudo procesar correctamente el archivo de stop words.\n";
}

void ProcesadorSetEntrenamiento::obtenerReview (string linea, string *id_review, string *sentimiento_review,
												vector<string> *contenido_review, int *resultado){
					
	string delimitador = "\t";
	size_t inicio_linea = 0;		
	ProcesadorReviews *pReviews = new ProcesadorReviews();
	UtilesTexto *util = new UtilesTexto();
	
	*id_review = linea.substr(inicio_linea, linea.find(delimitador));
	linea.erase(inicio_linea, (*id_review).size() + delimitador.size());
	util->limpiarPuntuacion(id_review);
	
	*sentimiento_review = linea.substr(inicio_linea,linea.find(delimitador));
	linea.erase(inicio_linea, (*sentimiento_review).size() + delimitador.size());
	
	*contenido_review = pReviews->obtenerPalabras(linea,resultado);
	
	delete pReviews;
	delete util;
}

/* 
 * procesarSetEntrenamiento(): 
 * Devuelve un SetEntrenamiento con los id's de cada review del set y sus respectivos sentimientos y contenidos. 
 * En caso de que ocurra algun error al procesar el set (no se pudieron eliminar correctamente las stop words, 
 * no se pudo procesar el archivo de entrenamiento, etc) devuelve un SetEntrenamiento vacio. 
 * */
 
SetEntrenamiento* ProcesadorSetEntrenamiento::procesarSetEntrenamiento(){
	
	int resultado;
	string linea, id_review, sentimiento_review;
	vector <string> contenido_review;
	SetEntrenamiento *setEntrenamiento = new SetEntrenamiento();
	ifstream trainData ("labeledTrainData.tsv");
			
	if (trainData.is_open()){
			
		getline(trainData,linea); // Ignoro la linea de titulos
		while (getline(trainData,linea)){
			obtenerReview(linea,&id_review,&sentimiento_review,&contenido_review,&resultado);
			if (resultado==OK) 
				setEntrenamiento->agregarReview(id_review,sentimiento_review,contenido_review);
			else {
				error_stopWords();
				setEntrenamiento->vaciar();
				return setEntrenamiento;
			}
		}
		trainData.close(); 
	}
	else error_setEntrenamiento();
	return setEntrenamiento;

}
