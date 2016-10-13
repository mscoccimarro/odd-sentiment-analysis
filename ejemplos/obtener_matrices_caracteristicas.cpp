#include "SetEntrenamiento.h"
#include "ProcesadorSetEntrenamiento.h"
#include "RandomForest.h"
#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
#include <fstream>
#include <time.h>
#define SEC_PER_MIN 60
using namespace std;

int main (){
	clock_t t = clock();
	ofstream out("matrices_caracteristicas.txt");
	cout << "Iniciando prueba...\n";
	SetEntrenamiento *setEntrenamiento = new SetEntrenamiento();
	ProcesadorSetEntrenamiento *pSetEntrenamiento = new ProcesadorSetEntrenamiento();
	pSetEntrenamiento->procesarSet(setEntrenamiento);
	delete pSetEntrenamiento;
	vector<vector<string> *> *vectorCaracteristicas = new vector< vector<string> *>; // Vector que en la posicion i tiene el vector de caracteristicas asociado a la matriz i.
	vector<vector<vector<string> *> *> *matrices = new vector < vector< vector<string> * > * >; // Vector que en cada posicion tie ne una matriz (vector de vectores)
	
	if (!setEntrenamiento->vacio()){
		int n = 20;
		vector<string> lista_ids;
		map<string,string> sentimientos;
		map<string,vector<string> > reviews;
		setEntrenamiento->get_N_caracteristicas(n,vectorCaracteristicas,matrices);
		int i = 0;
		while (i < matrices->size()){
			out << "-------------------------------------------------\n";
			out << "Nueva matriz\n";
			out << "-------------------------------------------------\n";
			out << "Vector de caracteristicas:\n";
			int j = 0;
			while (j < vectorCaracteristicas->at(i)->size()){
				out << vectorCaracteristicas->at(i)->at(j) << "\t\t\t\t";
				j++;
			}
			out << endl;
			out << "Matriz: \n";
			j = 0;
			while (j < matrices->at(i)->size()){
				int k = 0;
				while(k < matrices->at(i)->at(j)->size()){
					out << matrices->at(i)->at(j)->at(k) << "\t\t\t";
					k++;
				}
				out << endl;
				j++;
			}
			i++;
		}
	}
	else cout << "ERROR: El set de entrenamiento se encuentra vacio." << endl; 
	delete setEntrenamiento;
	delete matrices;
	delete vectorCaracteristicas;
	out.close();
	t = clock() - t;
	cout << fixed << setprecision(2) << ((float)t/CLOCKS_PER_SEC)/SEC_PER_MIN << " minutos transcurridos en total durante la prueba.\n\n";
	return 0;
}
