#include "ProcesadorSetEntrenamiento.h"
#include "SetEntrenamiento.h"
#include <iostream>
#include <fstream>  
#include <string>
#include <vector>
#include <map>

using namespace std;

string getScale(double score) {
	if(score < 0.2) return "muy malo";	
	if(score >= 0.2 && score < 0.4) return "malo";	
	if(score >= 0.4 && score < 0.6) return "regular";
	if(score >= 0.6 && score < 0.8) return "bueno";
	if(score >= 0.8) return "muy bueno";
	return "score out of bounds";
}

int main (){
	
	vector<string> ids,contenido;
	string sentimiento;
	vector<string>::iterator i,j;
	ofstream out("words.txt");
	ProcesadorSetEntrenamiento *pSetEntrenamiento = new ProcesadorSetEntrenamiento();
	SetEntrenamiento *setEntrenamiento = pSetEntrenamiento->procesarSetEntrenamiento();
	map<string, int> positivos;	
	map<string, int> negativos;

	if (!setEntrenamiento->vacio()){
		ids = setEntrenamiento->getIds();
		i = ids.begin();
		while(i != ids.end()){
			string sentiment = setEntrenamiento->getSentimiento(*i);
			contenido = setEntrenamiento->getContenido(*i);
			j = contenido.begin();
			while (j != contenido.end()){
				string last_word, last_sentiment;
				// save last word to sum possible "!" signs
				if(*j != "!") {
					last_word = *j + "_" + sentiment;
					last_sentiment = sentiment;
				}
				if(last_sentiment == "0") {
					if(negativos[last_word]) {
						negativos[last_word]++;
					} else {
						negativos[last_word] = 1;
					}
				} else {
					if(positivos[last_word]) {
						positivos[last_word]++;
					} else {
						positivos[last_word] = 1;
					}
				}
				j++;
			}
			i++;
		}

		double promedio;
		for(map<string, int>::iterator it = positivos.begin(); it != positivos.end(); it++) {
			// Si la palabra tiene apariciones negativas
			string word = it->first.substr(0, it->first.length() - 2);
			if(negativos[word + "_0"]) { 
				promedio = static_cast<double>(it->second) / static_cast<double>((it->second + negativos[word + "_0"]));
			} else 
					promedio = 1;

			out << word << " => " << promedio << " => " << getScale(promedio) << "\n";
		}

	}	
	else cout << "Ocurrio un problema al intentar procesar el set de entrenamiento." << endl;	
	delete pSetEntrenamiento;
	delete setEntrenamiento;
	out.close();
	return 0;
}
