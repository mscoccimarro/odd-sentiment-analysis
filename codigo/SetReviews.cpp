#include "SetReviews.h"
#include <string>
#include <vector>

using namespace std;

/* Agrega un review (con su id y contenido) al set de entrenamiento */
void SetReviews::agregarReview(string id_review, vector<string> contenido_review){
	this->listaIds.push_back(id_review);
	this->reviews[id_review] = contenido_review;
}
/* Permite vaciar el set de entrenamiento */
void SetReviews::vaciar(){
	this->listaIds.clear();
	this->reviews.clear();
}
/* Devuelve true si el set no tiene elementos, false en caso contrario */
bool SetReviews::vacio(){ return this->reviews.empty(); }

/* Devuelve un vector con todas las ID's de los reviews del set de entrenamiento */
vector<string> SetReviews::getIds(){ return this->listaIds; }

/* Devuelve el vector de palabras que representa el contenido del review asociado al id recibido */
vector<string> SetReviews::getContenido(string id_review){
	if (!this->reviews.empty()) return this->reviews[id_review];
	vector<string> vector_vacio;
	return vector_vacio;
}
