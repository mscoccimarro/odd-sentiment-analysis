/* 
 * Prueba: Obtener reviews del set de entrenamiento y de test
 * Recorre los reviews del set de entrenamiento e imprime sus ID's,
 * sentimientos asociados y contenido en el archivo 'reviews_entrenamiento.txt'
 * Recorre los reviews del set de test e imprime sus ID'S y contenido en 
 * el archivo 'reviews_test.txt' 
 * */

#include "ProcesadorSetEntrenamiento.h"
#include "SetEntrenamiento.h"
#include <iostream>
#include <iomanip>
#include <fstream>  
#include <string>
#include <vector>

using namespace std;

int main (){
	vector<string> ids,contenido;
	string sentimiento;
	vector<string>::iterator i,j;
	
	ofstream entrenamiento("reviews_entrenamiento.txt");
	ofstream test("reviews_test.txt");
	
	ProcesadorSet *pSet = new ProcesadorSet();
	ProcesadorSetEntrenamiento *pSetEntrenamiento = new ProcesadorSetEntrenamiento();
	
	SetReviews *setTest = new SetReviews();
	SetEntrenamiento *setEntrenamiento = new SetEntrenamiento();
	
	pSetEntrenamiento->procesarSet(setEntrenamiento);
	pSet->procesarSet(setTest);
		
	if (!setEntrenamiento->vacio()){
		ids = setEntrenamiento->getIds();
		i = ids.begin();
		while(i != ids.end()){
			entrenamiento << "\n";
			entrenamiento << "ID review: " << *i << endl;
			entrenamiento << "Sentimiento: " << setEntrenamiento->getSentimiento(*i) << endl;
			contenido = setEntrenamiento->getContenido(*i);
			entrenamiento << "Contenido: " << endl;
			j = contenido.begin();
			while (j != contenido.end()){
				entrenamiento << *j << " ";
				j++;
			}
			entrenamiento << "\n";
			i++;
		}
	}	
	else cout << "Ocurrio un problema al intentar procesar el set de entrenamiento." << endl;	
	
	if (!setTest->vacio()){
		ids = setTest->getIds();
		i = ids.begin();
		while(i != ids.end()){
			test << "\n";
			test << "ID review: " << *i << endl;
			contenido = setTest->getContenido(*i);
			test << "Contenido: " << endl;
			j = contenido.begin();
			while (j != contenido.end()){
				test << *j << " ";
				j++;
			}
			test << "\n";
			i++;
		}
	}	
	else cout << "Ocurrio un problema al intentar procesar el set de test." << endl;	
		
	delete pSet;
	delete pSetEntrenamiento;
	delete setTest;
	delete setEntrenamiento;
	test.close();
	entrenamiento.close();
	return 0;
}
