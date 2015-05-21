/* 
 * Prueba: Obtener reviews del set de entrenamiento 
 * Recorre los reviews del set de entrenamiento e imprime sus ID's,
 * sentimientos asociados y contenido en el archivo 'out.txt' 
 * */

#include "ProcesadorSetEntrenamiento.h"
#include "SetEntrenamiento.h"
#include <iostream>
#include <fstream>  
#include <string>
#include <vector>

using namespace std;

int main (){
	
	vector<string> ids,contenido;
	string sentimiento;
	vector<string>::iterator i,j;
	ofstream out("out.txt");
	ProcesadorSetEntrenamiento *pSetEntrenamiento = new ProcesadorSetEntrenamiento();
	SetEntrenamiento *setEntrenamiento = pSetEntrenamiento->procesarSetEntrenamiento();
	
	if (!setEntrenamiento->vacio()){
		ids = setEntrenamiento->getIds();
		i = ids.begin();
		while(i != ids.end()){
			out << "\n";
			out << "ID review: " << *i << endl;
			out << "Sentimiento: " << setEntrenamiento->getSentimiento(*i) << endl;
			contenido = setEntrenamiento->getContenido(*i);
			out << "Contenido: " << endl;
			j = contenido.begin();
			while (j != contenido.end()){
				out << *j << " ";
				j++;
			}
			out << "\n";
			i++;
		}
	}	
	else cout << "Ocurrio un problema al intentar procesar el set de entrenamiento." << endl;	
	delete pSetEntrenamiento;
	delete setEntrenamiento;
	out.close();
	return 0;
}
