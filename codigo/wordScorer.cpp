#include "ProcesadorSetEntrenamiento.h"
#include "SetEntrenamiento.h"
#include "wordScorer.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
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

bool pairCompare(const pair<string, int>& firstElem, const pair<string, int>& secondElem) {
	return firstElem.second > secondElem.second;
}

// returns word => score relation from processed training file
map<string, string> getWordScore(int topQuantity) {

	vector<string> ids,contenido;
	string sentimiento;
	vector<string>::iterator i,j;
	ProcesadorSetEntrenamiento *pSetEntrenamiento = new ProcesadorSetEntrenamiento();
	SetEntrenamiento *setEntrenamiento = pSetEntrenamiento->procesarSetEntrenamiento();
	map<string, int> positivos;	
	map<string, int> negativos;
	map<string, string> empty_map;

	// Fill maps with words
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

		// Process words to get scale and top appearances
		double promedio;
		vector< pair<string, int> > word_total;
		map<string, string> word_score, result;
		cout << endl << "Obteniendo score de " << topQuantity  << " palabras..." << endl;

		delete pSetEntrenamiento;
		delete setEntrenamiento;
		
		for(map<string, int>::iterator it = positivos.begin(); it != positivos.end(); it++) {
			// Si la palabra tiene apariciones negativas
			string word = it->first.substr(0, it->first.length() - 2);
			int total_appearances = it->second;
			if(negativos[word + "_0"]) { 
				total_appearances += negativos[word + "_0"];
				promedio = static_cast<double>(it->second) / static_cast<double>(total_appearances);
			} else promedio = 1;

			// fill word total
			word_total.push_back(make_pair(word, total_appearances));
			// fill word score
			word_score[word] = getScale(promedio);
		}

		// sort word total in descending order
		sort(word_total.begin(), word_total.end(), pairCompare);			

		for(vector< pair<string, int> >::iterator it = word_total.begin(); 
				it != word_total.begin() + topQuantity;
			 	it++) {
			result[it->first] = word_score[it->first];
		}

		return result;
	}	
	else cout << "Ocurrio un problema al intentar procesar el set de entrenamiento." << endl;	

	return empty_map; 
}
