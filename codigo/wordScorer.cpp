#include "wordScorer.h"
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <map>
#include <cmath>

using namespace std;

string getScale(double score) {
	if(score < 0.15) return "muy malo";
	if(score >= 0.15 && score < 0.3) return "malo";	
	if(score >= 0.3 && score < 0.5) return "regular";	
	if(score >= 0.5 && score < 0.7) return "bueno";
	if(score >= 0.7 && score < 0.9) return "muy bueno";
	if(score >= 0.9) return "excelente";
	return "score out of bounds";
}

bool pairCompare(const pair<string, int>& firstElem, const pair<string, int>& secondElem) {
	return firstElem.second > secondElem.second;
}

// returns word => score relation from processed training file
map<string, double> getWordScore(int topQuantity,SetEntrenamiento *setEntrenamiento) {
	vector<string> ids,contenido;
	string sentimiento;
	vector<string>::iterator i,j;
	map<string, int> positivos;
	map<string, int> negativos;
	map<string, int> docsConTermino;
	map<string, bool> processed;
	map<string, int> wordTotalAparitions;
	ids = setEntrenamiento->getIds();
	int cantReviews = ids.size();
	int cantTerminos = 0;
	map<string, map<string, int> > docTerminoApariciones;
	map<string, int> docCantTerminos;

	i = ids.begin();
	while(i != ids.end()){
			string sentiment = setEntrenamiento->getSentimiento(*i);
			contenido = setEntrenamiento->getContenido(*i);
			j = contenido.begin();
			while (j != contenido.end()){
				string last_word, last_sentiment;
				// get docs with term
				if(!processed[*j]) {
					processed[*j] = true;
					cantTerminos++;
					if(docsConTermino[*j]) {
						docsConTermino[*j]++;
					} else {
						docsConTermino[*j] = 1;
					}
				}
				// get term appearances in doc
				if(docTerminoApariciones[*i][*j]) {
					docTerminoApariciones[*i][*j]++;	
				} else {
					docTerminoApariciones[*i][*j] = 1;
				}

				if(wordTotalAparitions[*j]) {
					wordTotalAparitions[*j]++;
				} else {
					wordTotalAparitions[*j] = 1;
				}

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
			// clean processed words
			processed.clear();
			docCantTerminos[*i] = cantTerminos;
			cantTerminos = 0;
			i++;
		}

		// Process words to get scale and top appearances
		double promedio;
		map<string, double> idf;
		vector< pair<string, int> > word_total;
		map<string, double> word_score, result;
		cout << endl << "Obteniendo score de " << topQuantity  << " palabras..." << endl;
		map<string, map<string, double> > docTermino_TF_IDF;

		for(map<string, int>::iterator it = positivos.begin(); it != positivos.end(); it++) {
			// Si la palabra tiene apariciones negativas
			string word = it->first.substr(0, it->first.length() - 2);
			int total_appearances = it->second;
			if(negativos[word + "_0"]) { 
				total_appearances += negativos[word + "_0"];
				promedio = static_cast<double>(it->second) / static_cast<double>(total_appearances);	
				idf[word] = log2(static_cast<double>(cantReviews) / static_cast<double>(docsConTermino[word]));
			} else promedio = 1;

			// fill word total
			word_total.push_back(make_pair(word, total_appearances));
			// fill word score
			word_score[word] = promedio;
		}

		cout << "Cantidad total de palabras: " << word_total.size() << endl;
		double totalWords = word_total.size();
		for(map<string, int>::iterator it = wordTotalAparitions.begin(); it != wordTotalAparitions.end(); it++) {
			double tf = static_cast<double>(it->second) / static_cast<double>(totalWords);
//			cout << "Word: " << it->first << " | TF-IDF = " << tf * idf[it->first] << endl;
		}
		// sort word total in descending order
		sort(word_total.begin(), word_total.end(), pairCompare);			
		
		// get review -> word -> TF IDF
		for(map<string, map<string, int> >::iterator it = docTerminoApariciones.begin(); it != docTerminoApariciones.end(); it++) {
			string review = it->first;
			int cantTermsReview = docCantTerminos[review];
			for(map<string, int>::iterator iw = it->second.begin(); iw != it->second.end(); iw++) {
				double tf = static_cast<double>(iw->second) / static_cast<double>(cantTermsReview);
				double TF_IDF = tf * idf[iw->first];
				docTermino_TF_IDF[review][iw->first] = TF_IDF;
			}
		}		

		for(map<string, map<string, double> >::iterator it = docTermino_TF_IDF.begin(); it != docTermino_TF_IDF.end(); it++) {
			//cout << "ID: " << it->first << endl; 
			for(map<string, double>::iterator iw = it->second.begin(); iw != it->second.end(); iw++) {
			//cout << "\tWord: " << iw->first << " | TF-IDF = " << iw->second << endl;
			}
		}

		for(vector< pair<string, int> >::iterator it = word_total.begin(); 
				it != word_total.begin() + topQuantity;
			 	it++) {
			result[it->first] = idf[it->first];
			cout << "Promedio: " << word_score[it->first] << endl;
		}

		return result;
		
}
