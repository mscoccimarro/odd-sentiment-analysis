#include "SetEntrenamiento.h"
#include <string>
#include <vector>

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
/* Devuelve el sentimiento del review asociado al id recibido */
string SetEntrenamiento::getSentimiento(string id_review){
	if (!this->sentimientos.empty()) return this->sentimientos[id_review];
	return CADENA_VACIA;
}
