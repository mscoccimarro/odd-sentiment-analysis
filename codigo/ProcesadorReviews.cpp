#include "ProcesadorReviews.h"
#include "UtilesTexto.h"
#include "ProcesadorStopWords.h"
#include "Tags.h"
#define ERROR -1
#define OK 0

using namespace std;

void ProcesadorReviews::limpiarTags (string *texto){
	
	size_t pos_encontrada;
	Tags *tags = new Tags();
	vector<string>::iterator tags_it;
	vector<string> listaTags = tags->getTags();
	
	for (tags_it = listaTags.begin(); tags_it != listaTags.end(); tags_it++){
	
		pos_encontrada = texto->find(*tags_it);
	
		while(pos_encontrada != std::string::npos){
			texto->erase(pos_encontrada,(*tags_it).length());
			pos_encontrada = texto->find(*tags_it);
		}
	} 
	delete tags;
}

/* Devuelve en un vector las palabras del texto recibido en minuscula, sin signos de puntuacion, tags ni stop words. */
vector<string> ProcesadorReviews::obtenerPalabras(string texto,int *resultado){
	
	vector<string> palabras;
	string delimitador = " ", palabra;
	size_t inicio_texto = 0;
	
	UtilesTexto *util = new UtilesTexto();
	ProcesadorStopWords* stopWords = new ProcesadorStopWords();
		
	limpiarTags(&texto);
	util->limpiarPuntuacion(&texto);
	util->aMinuscula(&texto);
	
	
	while (texto.size() > 0){
		
		palabra = texto.substr(inicio_texto,texto.find(delimitador));
		palabras.push_back(palabra);
		texto.erase(inicio_texto, palabra.size() + delimitador.size());
	}
	
	*resultado = stopWords->eliminarStopWords(&palabras);
	
	delete util;
	delete stopWords;
	return palabras;
}
