#ifndef RANDOMFOREST_H_
#define RANDOMFOREST_H_

#include <string>
#include <math.h>
#include <vector>
#include <queue>
#include "Arbol.h"

using namespace std;

struct Porcentaje{
	double positivos;
	double negativos;
};

class RandomForest {

private:

	/* Atributos */
	vector<Arbol*>* arboles;
	vector<string>* caracteristicas;
	vector<vector<string>* >* setDeDatos;
	string valorPositivo;

	/* Funcionalidades internas */
	unsigned int getCantidadDeDatos();
	unsigned int getCantidadDeCaracteristicas();

	double getGanancia (vector<int>* indiceDeCaracteristicas, int columna);
	int getCaracteristicaMayor(vector<int>* indiceDeCaracteristicas, vector<int>* caracteristicasYaProcesadas);

	vector<int>* armarIndiceDeCarateristicas (vector<int>* indiceDeCaracteristicas);
	vector<Arbol*>* armarHijos(Arbol* arbol, vector<int>* caracteristicaYaProcesada);

	map <string, Porcentaje> armarMapaDeCaracteristica (vector<int>* indiceDeCaracteristicas, int columnaCaracteristica);
	map <string, vector<int>* > armarMapaDeIndices (vector<int>* indiceDeCaracteristicas, int columnaCaracteristica);

public:
	RandomForest();
	virtual ~RandomForest();

	void insertarSetDeDatos(vector<string>* caracteristicas, vector< vector<string>* >* setDeDatos, string valorPositivo);
	void armarArbolDeDecision();

	bool tomarDecision (map<string,string> consulta);
};

#endif /* RANDOMFOREST_H_ */
