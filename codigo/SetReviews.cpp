#include "SetReviews.h"
#include "wordScorer.h"
#include <string>
#include <iostream> 
#include <fstream> 
#include <vector>
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <math.h>

using namespace std;

/* Agrega un review (con su id y contenido) al set de entrenamiento */
void SetReviews::agregarReview(string id_review, vector<string> contenido_review){
	this->listaIds.push_back(id_review);
	this->reviews[id_review] = contenido_review;
	// id_contenido: contiene las palabras (sin repeticiones) que tiene el review cuyo ID es la clave:
	for (vector<string>::iterator it = contenido_review.begin(); it != contenido_review.end(); it++) 
		if(this->id_contenido[id_review].find(*it) == this->id_contenido[id_review].end())
			this->id_contenido[id_review].insert(*it);

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

// puntero a map<string,string> *
// clave = caracteristica , valor = muy bueno malo muy malo
map<string,string> * SetReviews::generarConsultas(string id_review,map<string,double> top_n_palabras){
	map<string,string> *consulta = new map<string,string>;
	vector<string> palabras_consulta = reviews[id_review];
	cout << "Consulta review " << id_review << endl;
	for(vector<string>::iterator palabra = palabras_consulta.begin(); palabra != palabras_consulta.end(); palabra++){
		if(top_n_palabras[*palabra]){
			(*consulta)[*palabra] = getScale(top_n_palabras[*palabra]);
			cout << "Palabra: " << *palabra << "Score: " << getScale(top_n_palabras[*palabra]) << endl;
		}
	}
	return consulta;
}
