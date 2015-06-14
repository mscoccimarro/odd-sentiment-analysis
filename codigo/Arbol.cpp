#include "Arbol.h"
using namespace std;


/* ------------------------- FUNCIONALIDADES GENERICAS ------------------------*/

/**
 * Funcionalidad que compara dos arboles
 */
bool compararArboles (Arbol* a,Arbol* b) {
	return (a->getPorcentaje() > b->getPorcentaje());
}

/* --------------------------------  A R B O L --------------------------------*/

/**
 * Constructor
 */
Arbol::Arbol(string clave) {

	this->clave = clave;
	this->valor = "";
	this->porcentaje = 0;
	this->decision = false;
	this->hijos = NULL;
	this->indicesDeValoresCaracteristicos = new vector <int>;
}

/*
 * Constructor secundario y privado, donde se setean sus atributos.
 */
Arbol::Arbol(string clave, string valor, double porcentaje, vector<int>* caracteristicas){

	this->clave = clave;
	this->valor = valor;
	this->porcentaje = porcentaje;
	//TODO ver bien si la decision es positiva cuando el porcentaje es igual a 1 u otra cosa.
	this->decision = (porcentaje == 1);
	this->hijos = NULL;
	this->indicesDeValoresCaracteristicos = caracteristicas;
}

/*
 * Destructor
 */
Arbol::~Arbol() {

	if (this->indicesDeValoresCaracteristicos != NULL){
		delete this->indicesDeValoresCaracteristicos;
	}

	if (hijos != NULL){
		Arbol* arbol;
		for (unsigned i = 0; i < hijos->size(); i++){
			arbol = hijos->at(i);
			delete arbol;
		}
		delete hijos;
	}
}

/**
 * Inserta un hijo al arbol
 */
void Arbol::insertarHijo(string clave, string valor,double porcentaje, vector<int>* indicesDeValoresCaracteristicosNuevo){
	if (hijos == NULL){
		hijos = new vector<Arbol*>;
	}

	if(porcentaje == 1 || porcentaje == 0){
		clave = this->getClave();
	}

	hijos->push_back(new Arbol(clave, valor, porcentaje, indicesDeValoresCaracteristicosNuevo));
}

/**
 * Devuelve la decision tomada por el arbol, dependiendo la consulta.
 * En caso de no encontrar decision devuelve false.
 */
bool Arbol::tomarDecision(map<string,string> consulta){

	vector<Arbol*>* hijos = this->hijos;
	for (unsigned int i = 0; hijos != NULL && i < hijos->size(); i++){
		Arbol* hijo = hijos->at(i);
		string valorCaracteristica = consulta[this->getClave()];
//		cout << endl << "comparo: " << valorCaracteristica << " - " << hijo->getValor();
		if (valorCaracteristica.compare(hijo->getValor()) == 0){

			if (hijo->isHoja()){
				return (hijo->getPorcentaje() == 1);
			}else if (!hijo->tieneHijos()){
				return (hijo->getPorcentaje() > 0.5);
			}
			return hijo->tomarDecision(consulta);
		}
	}
	cout << endl << "NO HUBO DECISION";
	return false;
}

/**
 * Ordena sus hijos por su porcentaje de positividad, de manera decreciente
 * Precondicion: Necesita estar definida la funcion que compara los arboles
 */
void Arbol::ordenarHijosPorImportancia(){
	vector<Arbol*>* hijos = this->getHijos();
	if (hijos != NULL && !hijos->empty())
		sort(hijos->begin(), hijos->end(), compararArboles);
}

/**
 * Muestra por consola el arbol formado
 */
void Arbol::verArbol(){

	queue<Arbol*> cola;
	cola.push(this);
	Arbol* arbol = this;

	while (!cola.empty()){

		arbol = cola.front();
		cout << endl << "*" << arbol->getClave() << ": ";
		cola.pop();
		vector<Arbol*>* hijos = arbol->getHijos();

		if (hijos != NULL){
			for (unsigned int i = 0; i < hijos->size(); i++){
				Arbol* hijo = hijos->at(i);
				cout <<"  -" << hijo->getClave() << "|" << hijo->getValor() << "|" << hijo->getPorcentaje();
				if (!hijo->isHoja()){
					cola.push(hijo);
				}
			}
			cout << endl;
		}
	}
}


/* ----------------------- FUNCIONES SECUNDARIAS --------------------------*/

double Arbol::getPorcentaje(){
	return this->porcentaje;
}

void Arbol::setClave(string clave){
	this->clave = clave;
}

string Arbol::getClave(){
	return this->clave;
}

string Arbol::getValor(){
	return this->valor;
}

vector<Arbol*>* Arbol::getHijos(){
	return this->hijos;
}

bool Arbol::tieneHijos(){
	return (hijos != NULL && !hijos->empty());
}

bool Arbol::isHoja(){
	return porcentaje <= 0 || porcentaje >= 1;
}

vector<int>* Arbol::getIndicesDeCaracteristica(){
	return this->indicesDeValoresCaracteristicos;
}
