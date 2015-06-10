#include "ProcesadorSetEntrenamiento.h"
#include "SetEntrenamiento.h"
#include <iostream>
#include <fstream>  
#include <string>
#include <vector>
#include <map>

using namespace std;

int main (){
	
	vector<string> ids,contenido;
	string sentimiento;
	vector<string>::iterator i,j;
	ofstream out("words.txt");
	ProcesadorSetEntrenamiento *pSetEntrenamiento = new ProcesadorSetEntrenamiento();
	SetEntrenamiento *setEntrenamiento = pSetEntrenamiento->procesarSetEntrenamiento();
	map<string, int> hash;	
	if (!setEntrenamiento->vacio()){
		ids = setEntrenamiento->getIds();
		i = ids.begin();
		while(i != ids.end()){
			string sentiment = setEntrenamiento->getSentimiento(*i);
			contenido = setEntrenamiento->getContenido(*i);
			j = contenido.begin();
			while (j != contenido.end()){
				string word = *j + "_" + sentiment;
				if(hash[word])
					hash[word]++;
				else
					hash[word] = 1;
				j++;
			}
			i++;
		}
		map<int, string> reverse_map;
		// Fill reverse map with hash
		for(map<string, int>::iterator it = hash.begin(); it != hash.end(); it++) 
			reverse_map[it->second] = it->first;
		// Output "word appearances" => "word"_"sentiment"
		// Ex: "1034 => hola_0"
		for(map<int, string>::iterator it = reverse_map.begin(); it != reverse_map.end(); it++)
			out << it->first << " => " << it->second << '\n';
	}	
	else cout << "Ocurrio un problema al intentar procesar el set de entrenamiento." << endl;	
	delete pSetEntrenamiento;
	delete setEntrenamiento;
	out.close();
	return 0;
}
