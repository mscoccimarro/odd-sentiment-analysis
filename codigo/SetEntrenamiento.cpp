#include "SetEntrenamiento.h"
#include "wordScorer.h"
#include <iostream> 
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <math.h>
#define MAX_REVIEWS_MATRIZ 500
#define MAX_PALABRAS 5
#define SEC_PER_MIN 60
#define TITULO_ID "id"
#define TITULO_SENTIMIENTO "sentimiento"

using namespace std;

/* Agrega un review (con su id, sentimiento y contenido) al set de entrenamiento */
void SetEntrenamiento::agregarReview(string id_review, string sentimiento_review, vector<string> contenido_review){
	this->listaIds.push_back(id_review);
	this->reviews[id_review] = contenido_review;
	this->sentimientos[id_review] = sentimiento_review;
	// id_contenido: contiene las palabras (sin repeticiones) que tiene el review cuyo ID es la clave:
	for (vector<string>::iterator it = contenido_review.begin(); it != contenido_review.end(); it++) 
		if(this->id_contenido[id_review].find(*it) == this->id_contenido[id_review].end())
			this->id_contenido[id_review].insert(*it);
}

/* Permite vaciar el set de entrenamiento */
void SetEntrenamiento::vaciar(){
	this->listaIds.clear();
	this->reviews.clear();
	this->sentimientos.clear();
	this->id_contenido.clear();
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

void SetEntrenamiento::cargar_matriz_y_vector(int i, vector< vector< vector<string> *> *> * matrices,
																		vector<vector<string>*> * vectorCaracteristicas,
																		vector<string> *ids,
																		map<string, string> *palabras,
																		vector<string> *grupo_palabras){

// Inicializo vector de caracteristicas
	vector<string> *vector_vacio = new vector<string>;
	vectorCaracteristicas->push_back(vector_vacio);
	vectorCaracteristicas->at(i)->push_back(TITULO_ID);

// Inicializo matriz de caracteristicas
	vector< vector<string> *>*  matriz_vacia = new vector < vector<string> *>;
	matrices->push_back(matriz_vacia);
	int id = 0, reviews_procesados = 0;
	while (id < ids->size() && reviews_procesados <= MAX_REVIEWS_MATRIZ){
		// Creo una nueva fila por cada ID asociado a la palabra:
		vector<string> *fila = new vector<string>;
		fila->push_back(ids->at(id));
		matrices->at(i)->push_back(fila);
		id++;
		reviews_procesados++;
	}

// Cargo los valores de las caracteristicas	
	int palabra = 0;
	while (palabra < grupo_palabras->size()){
		vectorCaracteristicas->at(i)->push_back(grupo_palabras->at(palabra));
		int j = 0;
		while (j < matrices->at(i)->size()){
			// Busco en el map el score de la palabra y lo agrego a la fila de la matriz
			matrices->at(i)->at(j)->push_back((*palabras)[grupo_palabras->at(palabra)]);			 
			j++;
		}
		palabra++;
	}

// Agrego los sentimientos en el vector de caracteristicas y en la matriz:
	vectorCaracteristicas->at(i)->push_back(TITULO_SENTIMIENTO);
	int j = 0;
	while (j < matrices->at(i)->size()){
		matrices->at(i)->at(j)->push_back(this->sentimientos[ids->at(j)]);			 
		j++;
	}

}

void SetEntrenamiento::get_N_caracteristicas(int n, vector<vector<string> *>* vectorCaracteristicas,
																	vector< vector< vector<string> *> *> *matrices){ 

	clock_t t = clock();
	
	cout << "---------------------------------------------------------------\n";
	cout << "Generando entrada del random forest...\n";
	cout << "---------------------------------------------------------------\n";		
	
	// Obtengo score del top N de palabras
	map<string,string> palabras = getWordScore(n,this);
	cout << "Score obtenido.\n";
	
	cout << "\nProcesando palabras...\n";
	map<string,string>::iterator palabra = palabras.begin();
	// variables para la impresion por pantalla del progreso del proceso
	int procesadas = 0, procesadas_anterior = 0, max_procesadas = n/10, pos = 0;
	// n = nro palabras
	while (n > 0){ 		
		vector<string> copia_ids = this->listaIds; // En copia_ids tengo los IDs de todos los reviews 
		int i = 0;
		vector<string> *grupo_palabras = new vector<string>;
		while (i < MAX_PALABRAS){ // Tomo MAX_PALABRAS (= 10) palabras por cada iteracion
			if ((*palabra).first != ""){
				grupo_palabras->push_back((*palabra).first);
				// Por cada palabra busco los ids de reviews que la contienen y descarto los que no, de esta forma al final voy a tener
				// los ids de los reviews que tienen todas las palabras
				vector<string>::iterator id = copia_ids.begin();
				while (id != copia_ids.end()){
					if (this->id_contenido[*id].find((*palabra).first) == this->id_contenido[*id].end())
						copia_ids.erase(id); // Si el review de esta ID no contenia la palabra, lo borro de la lista de IDs
					else id++;
				}
				i++; 
				procesadas++;
			}
			palabra++; 
			if (palabra == palabras.end()) i = MAX_PALABRAS; // Si no tengo mas palabras no sigo procesando
		}
		if (procesadas >= procesadas_anterior + max_procesadas) {
			cout << procesadas << " palabras procesadas hasta el momento.\n" ;
			procesadas_anterior = procesadas;
		}
		cargar_matriz_y_vector(pos,matrices,vectorCaracteristicas,&copia_ids,&palabras,grupo_palabras);
		pos++;
		delete grupo_palabras;
		if (palabra == palabras.end()) n = 0; // Si no tengo mas palabras no sigo procesando
		else n -= MAX_PALABRAS;
	}

	t = clock() - t;
	cout << "Proceso concluido: " << fixed << setprecision(2) << ((float)t/CLOCKS_PER_SEC)/SEC_PER_MIN << " minutos transcurridos.\n\n";

	// Para la prueba, despues borrar:
	for(map<string, string>::iterator it = palabras.begin(); it != palabras.end(); it++) {
		cout << it->first << " => " << it->second << endl;
	}
	//
}
