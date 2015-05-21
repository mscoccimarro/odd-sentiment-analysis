#include "SetEntrenamiento.h"
#include <string>
#include <vector>
#define CADENA_VACIA " "

using namespace std;
/* Agrega un review (con su id, sentimiento y contenido) al set de entrenamiento */
void SetEntrenamiento::agregarReview(string id_review, string sentimiento_review, vector<string> contenido_review){
	
	this->listaIds.push_back(id_review);
	this->reviews[id_review] = contenido_review;
	this->sentimientos[id_review] = sentimiento_review;

}
/* Permite vaciar el set de entrenamiento */
void SetEntrenamiento::vaciar(){
	this->listaIds.clear();
	this->reviews.clear();
	this->sentimientos.clear();
}
/* Devuelve true si el set no tiene elementos, false en caso contrario */
bool SetEntrenamiento::vacio(){
	if (this->sentimientos.empty() && this->reviews.empty()) return true;
	return false;	
}
/* Devuelve un vector con todas las ID's de los reviews del set de entrenamiento */
vector<string> SetEntrenamiento::getIds(){
	return this->listaIds;
}

/* Devuelve el vector de palabras que representa el contenido del review asociado al id recibido */
vector<string> SetEntrenamiento::getContenido(string id_review){
	if (!this->reviews.empty()) return this->reviews[id_review];
	vector<string> vector_vacio;
	return vector_vacio;
}

/* Devuelve el sentimiento del review asociado al id recibido */
string SetEntrenamiento::getSentimiento(string id_review){
	if (!this->sentimientos.empty()) return this->sentimientos[id_review];
	return CADENA_VACIA;
}
