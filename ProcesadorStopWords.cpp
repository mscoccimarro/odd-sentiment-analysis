#include "ProcesadorStopWords.h"
#include <fstream>
#include <string>
#define ERROR -1
#define OK 0

using namespace std;

/*Si ocurre algun problema al abrir el archivo de stop words, la lista queda vacia.*/
ProcesadorStopWords::ProcesadorStopWords(){
    
    ifstream archStopWords ("listaStopWords.txt");
    string linea;
	
	if (archStopWords.is_open()){
    
		while (getline (archStopWords,linea)) 
			
			this->listaStopWords.push_back(linea);
		
		limpiarStopWords();		
		archStopWords.close();
	}
}


/*Elimina '/r' del ultimo caracter de las stop words.*/
void ProcesadorStopWords::limpiarStopWords(){
	
	vector<string>::iterator it;
	for(it = this->listaStopWords.begin(); it != this->listaStopWords.end(); it++) 
		
		(*it).erase((*it).length() - 1, 1);
			
}

/*Elimina palabras consideradas stop words del vector de strings recibido, devulve ERROR en 
 * caso de que la lista estuviera vacia.*/
int ProcesadorStopWords::eliminarStopWords(vector <string> *palabras_review){
	
	vector<string>::iterator i,j;
	if (!this->listaStopWords.empty()) {
	
		for (i = palabras_review->begin() ; i < palabras_review->end(); i++){
	
			j = this->listaStopWords.begin();
	
			while (j != this->listaStopWords.end()) {
				if ((*i).compare(*j) == OK) {
					palabras_review->erase(i);
					i--; // Para que no ignore la siguiente palabra.
					j = this->listaStopWords.end();				 
				}
				else j++; 
			}
		} 
		return OK;
	} 
	return ERROR;
}
