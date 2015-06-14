#ifndef ARBOL_H_
#define ARBOL_H_

#include <iostream>
#include <vector>
#include <map>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

class Arbol {

private:

	/* Atributos */
    string clave;
    string valor;
    bool decision;
    double porcentaje;
    vector <Arbol*>* hijos;
    vector <int>* indicesDeValoresCaracteristicos;

    /* Constructor privado */
    Arbol(string clave,string valor,double porcentaje, vector<int>* caracteristicas);

public:

    /* Constructor y destructor publicos */
	Arbol(string clave);
	virtual ~Arbol();

	/* Metodos de atributos */
	string getClave();
	void setClave(string clave);
	string getValor();
	double getPorcentaje();
	vector<Arbol*>* getHijos();
	vector<int>* getIndicesDeCaracteristica();

	/* Funcionalidades publicas */
	bool isHoja();
	bool tieneHijos();

	void insertarHijo(string clave, string valor,double porcentaje, vector<int>* caracteristicas);
	void ordenarHijosPorImportancia();
	bool tomarDecision(map<string,string> consulta);
	void verArbol();
};

#endif /* ARBOL_H_ */
