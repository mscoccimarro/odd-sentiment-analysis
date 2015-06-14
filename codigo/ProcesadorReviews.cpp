#include "ProcesadorReviews.h"
#include "UtilesTexto.h"
#include "EliminadorSufijos.h"
#include "ProcesadorStopWords.h"
#include <iostream>
#define STRING_VACIO " "
#define CARAC_BLANCO ' '
#define ERROR -1
#define OK 0

using namespace std;

/* Se eliminan las comillas simples para que por ejemplo: he's pase a ser hes o i've pase a ser ive y 
 * sean interpretados como parte de la misma palabra. */
void ProcesadorReviews::eliminar_comillas_simples(string *texto){
	size_t pos_encontrada;
	string comilla_simple = "\'";
	vector<string>::iterator it;
	pos_encontrada = texto->find(comilla_simple);
	while(pos_encontrada != string::npos){
		texto->erase(pos_encontrada,1);
		pos_encontrada = texto->find(comilla_simple);
	}
} 

void ProcesadorReviews::limpiarTags (string *texto){
	size_t pos_encontrada;
	UtilesTexto *util = new UtilesTexto();
	vector<string>::iterator tags_it;
	vector<string> listaTags = util->getTags();
	
	for (tags_it = listaTags.begin(); tags_it != listaTags.end(); tags_it++){
		pos_encontrada = texto->find(*tags_it);
		while(pos_encontrada != string::npos){
			texto->replace(pos_encontrada,(*tags_it).length(),STRING_VACIO);
			pos_encontrada = texto->find(*tags_it);
		}
	} 
	delete util;
}
/* Devuelve en un vector los signos de exclamacion que posee la palabra, ademas de eliminarlos de la misma.
 * Si la palabra no tenia ningun signo de exclamacion, devuelve un vector vacio.
 */
vector<string> ProcesadorReviews::procesarExclamaciones(string *palabra){
		vector<string> exclamaciones;
		string signo_exclamacion = "!";
		size_t found = palabra->find(signo_exclamacion);
		while(found != string::npos){
			exclamaciones.push_back(signo_exclamacion);
			palabra->erase(found,signo_exclamacion.length());
			found = palabra->find(signo_exclamacion);		
		}
		return exclamaciones;
}			
/* Devuelve en un vector las palabras del texto recibido en minuscula, sin signos de puntuacion, sufijos, tags ni stop words. */
vector<string> ProcesadorReviews::obtenerPalabras(string texto,int *resultado){
	vector<string> palabras,exclamaciones;
	vector<string>::iterator it_palabra;
	string delimitador = STRING_VACIO, palabra;
	
	UtilesTexto *util = new UtilesTexto();
	ProcesadorStopWords* stopWords = new ProcesadorStopWords();
	EliminadorSufijos *eSuf = new EliminadorSufijos();
	
	limpiarTags(&texto);
	eliminar_comillas_simples(&texto);
	util->limpiarPuntuacion(&texto);
	util->aMinuscula(&texto);
	// Borro espacios extra que haya dejado la eliminacion de tags o puntuacion
	while(*texto.begin() == CARAC_BLANCO) texto.erase(texto.begin());	
	while (texto.size() > 0){
		palabra = texto.substr(0,texto.find(delimitador));
		texto.erase(0, palabra.size() + delimitador.size());
		exclamaciones = procesarExclamaciones(&palabra); 
		palabras.push_back(palabra);
		if(!exclamaciones.empty()){
			// Si se encontraron signos de exclamacion, se los agrega como palabras al contenido del review
			vector<string>::iterator exclamacion;
			for (exclamacion = exclamaciones.begin(); exclamacion != exclamaciones.end(); exclamacion++)
				palabras.push_back(*exclamacion);
		}
		while(*texto.begin() == CARAC_BLANCO) texto.erase(texto.begin());	
	}
	*resultado = stopWords->eliminarStopWords(&palabras);
	for (it_palabra = palabras.begin(); it_palabra != palabras.end() ; it_palabra++) eSuf->eliminarSufijos(&(*it_palabra));
	delete eSuf;
	delete util;
	delete stopWords;
	return palabras;
}
