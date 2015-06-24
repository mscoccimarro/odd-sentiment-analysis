#include "SetEntrenamiento.h"
#include "wordScorer.h"
#include <iostream> 
#include <iomanip>
#include <time.h>
#include <cstdlib>
#include <math.h>
#include <fstream>
#define SEC_PER_MIN 60
#define TITULO_ID "id"
#define TITULO_SENTIMIENTO "sentimiento"
#define CANTIDAD_DE_MATRICES 20

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

void SetEntrenamiento::cargar_matriz_y_vector(vector < vector <string>* >* matrizGigante,
																		vector<string>* vectorCaracteristicas,
																		vector<string> *ids,
																		map<string, double> *palabras,map<string,string> word_score){
	
	vectorCaracteristicas->push_back(TITULO_ID);
	for (map<string,double>::iterator palabra = palabras->begin(); palabra != palabras->end(); palabra++){
		if (palabra->first != "") vectorCaracteristicas->push_back((*palabra).first);
	}
	vectorCaracteristicas->push_back(TITULO_SENTIMIENTO);

	for (vector<string>::iterator id = ids->begin(); id != ids->end() ; id++){
		vector<string>* fila = new vector<string>;
		fila->push_back(*id);
		for (map<string, double>::iterator palabra = palabras->begin(); palabra != palabras->end(); palabra++){
		// Busco en el map el score de la palabra y lo agrego a la fila de la matriz
			string id_palabra = *id + "_" + palabra->first;
			if (palabra->first != "") fila->push_back(word_score[id_palabra]);
		}
		fila->push_back(this->sentimientos[*id]);
		matrizGigante->push_back(fila);
	}
	ofstream out("matriz_gigante.txt");
	out << "Vector caracteristicas: \n";
	for (vector<string>::iterator j = vectorCaracteristicas->begin() ; j != vectorCaracteristicas->end() ; j++) 
		out << *j << "\t\t\t";
	out << endl;
	out << "Matriz gigante: \n";
	int j = 0;
	while(j < matrizGigante->size()){
		int k = 0;
		while (k < matrizGigante->at(j)->size()){
			out << matrizGigante->at(j)->at(k) << "\t\t\t\t";
			k++;
		}
		out<< endl;
		j++;
	}
	out << endl;
	out.close();
}

map<string, double> SetEntrenamiento::getTopN(){

	if (!this->topNPalabras.empty()) return this->topNPalabras;
	map<string,double> mapa_vacio;
	return mapa_vacio;
	
}

void SetEntrenamiento::get_N_caracteristicas(int nro_palabras, vector<string> * vectorCaracteristicas,
																	vector< vector< vector<string> *> *> *matrices){ 

	// Para prueba
	ofstream promedios("promedios.txt");
	//
	clock_t t = clock();
	
	cout << "---------------------------------------------------------------\n";
	cout << "Generando entrada del random forest...\n";
	cout << "---------------------------------------------------------------\n";		

	
	// Obtengo score del top N de palabras
	map<string, double> palabras = getWordScore(nro_palabras,this);
	this->topNPalabras = palabras;
	cout << "Score obtenido.\n";

	cout << "\nProcesando palabras...\n";
	// variables para la impresion por pantalla del progreso del proceso
	int procesadas = 0, procesadas_anterior = 0, max_procesadas = nro_palabras/10;

	vector<string> copia_ids = this->listaIds; // En copia_ids tengo los IDs de todos los reviews 
	for (map<string, double>::iterator palabra = palabras.begin(); palabra != palabras.end(); palabra++){
		if ((*palabra).first != ""){
			// Por cada palabra busco los ids de reviews que la contienen y descarto los que no, de esta forma al final voy a tener los ids de los reviews que tienen todas las palabras
			vector<string>::iterator id = copia_ids.begin();
			while (id != copia_ids.end()){
				if (this->id_contenido[*id].find((*palabra).first) == this->id_contenido[*id].end())
					copia_ids.erase(id); // Si el review de esta ID no contenia la palabra, lo borro de la lista de IDs
				else id++;
			}
			procesadas++;
			if (procesadas >= procesadas_anterior + max_procesadas) {
				cout << procesadas << " palabras procesadas hasta el momento.\n" ;
				procesadas_anterior = procesadas;
			}
		}
	}

	// Obtengo cantidad de palabras en review para calcular score
	map<string, int> apariciones;
	map<string, string> word_score;

	for(vector<string>::iterator id = copia_ids.begin(); id != copia_ids.end(); id++) {
		vector<string> review = this->reviews[*id];	
	  int reviewSize = review.size();
		for(int i = 0; i < reviewSize; i++) {
			for(map<string, double>::iterator it = palabras.begin(); it != palabras.end(); it++) {
				if(it->first == review[i]) {
					if(apariciones[it->first])
						apariciones[it->first]++;
					else
						apariciones[it->first] = 1;
				}
			}	
		}	
		int cant_apariciones = 0;
		for(map<string, int>::iterator it = apariciones.begin(); it != apariciones.end(); it++) 
			cant_apariciones += it->second;

	for(map<string, int>::iterator it = apariciones.begin(); it != apariciones.end(); it++) {
		if(apariciones[it->first]) {
			double weight = static_cast<double>(1) + palabras[it->first];  
			double promedio = 0;
			if(cant_apariciones != 0) 
				promedio = (static_cast<double>(apariciones[it->first]) * weight)/ static_cast<double>(cant_apariciones);
				string id_word = *id + "_" + it->first;
				if (promedio > 0.2) promedio = (double)(rand()%(100))/100 ;
				else promedio = (double)(rand()%(50))/100;
				promedios << "Palabra: " << it->first << "Promedio: " << promedio << endl;
				word_score[id_word] = getScale(promedio);
			}
		}
	// reset apariciones
	apariciones.clear();
	}

	vector < vector <string>* >* matrizGigante = new vector < vector<string>* >;
	cargar_matriz_y_vector(matrizGigante,vectorCaracteristicas,&copia_ids,&palabras,word_score);
	getMatrices(matrizGigante,matrices);

	t = clock() - t;
	cout << "Proceso concluido: " << fixed << setprecision(2) << ((float)t/CLOCKS_PER_SEC)/SEC_PER_MIN << " minutos transcurridos.\n\n";
}

// Dada la matriz pasada por parametro, se divide a la misma devolviendo un vector de dichas divisiones
void SetEntrenamiento::getMatrices(vector < vector <string>* >* matrizGigante,vector< vector < vector <string> * > * > *  vectorDeMatrices){

	for (unsigned int i = 0; i < CANTIDAD_DE_MATRICES; i++){
		vector < vector <string>* >* matriz = new vector < vector <string>* >;
		
		for (unsigned int j = 0; j < 5; j++){
			//srand(rd());
			int indiceFila = rand()%(matrizGigante->size());
			vector <string>* fila = matrizGigante->at(indiceFila);
			matriz->push_back(fila);
		}
		vectorDeMatrices->push_back(matriz);
		
	}

}
