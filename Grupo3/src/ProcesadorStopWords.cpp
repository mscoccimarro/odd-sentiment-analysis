#include "ProcesadorStopWords.h"
#include <fstream>
#define ERROR -1
#define OK 0

using namespace std;

/*Si ocurre algun problema al abrir el archivo de stop words, el set queda vacio.*/
ProcesadorStopWords::ProcesadorStopWords(){
    ifstream archStopWords ("listaStopWords.txt");
    string linea;
	if (archStopWords.is_open()){
    	while (getline (archStopWords,linea)){ 
			linea.erase(linea.length()-1,1); //Elimino '/r' del ultimo caracter de la stop word.
			this->listaStopWords.insert(linea);
		}
		archStopWords.close();
	}
}

/*Elimina palabras consideradas stop words del vector de strings recibido, devulve ERROR en 
 * caso de que la lista estuviera vacia.*/
int ProcesadorStopWords::eliminarStopWords(vector <string> *palabras_review){
	if (!this->listaStopWords.empty()) {
		vector<string>::iterator i = palabras_review->begin();
		while(i != palabras_review->end()){
			if (this->listaStopWords.find(*i) != this->listaStopWords.end()) palabras_review->erase(i);
			else i++;
		} 
		return OK;
	} 
	return ERROR;
}
