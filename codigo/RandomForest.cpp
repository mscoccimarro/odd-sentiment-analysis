#include "RandomForest.h"

/* ------------------ FUNCIONALIDADES GENERICAS ------------------------*/

/**
 * Funcionalidad que duvuelve si el valor esta en el vector.
 */
bool inVector (vector<int>* vector, int valor){

	if (vector == NULL || vector->size() == 0){
		return false;
	}

	for (unsigned int i = 0; i < vector->size(); i++){
		if (valor == vector->at(i)){
			return true;
		}
	}
	return false;
}

/**
 * Funcionalidad que duvuelve si el valor esta en el vector.
 */
bool inVector (vector<string>* vector, string valor){

	if (vector == NULL || vector->size() == 0){
		return false;
	}

	for (unsigned int i = 0; i < vector->size(); i++){
		if (valor.compare(vector->at(i)) == 0){
			return true;
		}
	}
	return false;
}


/* ------------------------------ RANDOM  FOREST -----------------------------*/

/**
 * Constructor
 */
RandomForest::RandomForest() {
	this->arboles = new vector<Arbol*>;
	this->caracteristicas = NULL;
	this->setDeDatos = NULL;
}

/**
 * Destructor
 */
RandomForest::~RandomForest(){

	if (this->caracteristicas != NULL){
		delete this->caracteristicas;
	}

	if (this->setDeDatos != NULL){
		for (unsigned int i = 0; i < this->setDeDatos->size(); i++){
			delete this->setDeDatos->at(i);
		}
		delete this->setDeDatos;
	}

	for (unsigned int i = 0; this->arboles != NULL && i < this->arboles->size(); i++){
		delete this->arboles->at(i);
	}
	delete this->arboles;
}

/**
 * Almacena las caracteristicas, todos los valores de las caracteristicas
 * y el valor que hace positivo a cada una de las caracteristicas.
 */
void RandomForest::insertarSetDeDatos(vector<string>* caracteristicas, vector< vector<string>* >* matriz, string valorPositivo){

	if (this->caracteristicas != NULL){
		delete this->caracteristicas;
	}

	if (this->setDeDatos != NULL){
		for (unsigned int i = 0; i < this->setDeDatos->size(); i++){
			delete this->setDeDatos->at(i);
		}
		delete this->setDeDatos;
	}

	this->caracteristicas = caracteristicas;
	this->setDeDatos = matriz;
	this->valorPositivo = valorPositivo;
}

/**
 * Si el indice de las caracteristicas esta vacio, lo completa con los valores de 0 a n-1 (con n: cantidad de datos a analizar).
 * En caso de no estar vacío devuelve los mismos indices.
 */
vector<int>* RandomForest::armarIndiceDeCarateristicas (vector<int>* indiceDeCaracteristicas){

	if (indiceDeCaracteristicas->size() == 0){
		for (unsigned int i = 0; i < this->getCantidadDeDatos(); i++){
			indiceDeCaracteristicas->push_back(i);
		}
	}
	return indiceDeCaracteristicas;
}

/**
 * obtiene la ganancia de la caracteristica pasada por parametro, teniendo solamente
 * en cuenta los datos que aparecen en los indices de las caracteristicas.
 * La ganancia se calcula como la cantidad de datos distintos de dicha caracteristica.
 * Mientras mas datos distintos existan, mas ganancia tendra.
 */
double RandomForest::getGanancia (vector<int>* indiceDeCaracteristicas, int columnaCaracteristica){

	vector<string>* valoresDistintos = new vector <string>;
	indiceDeCaracteristicas = armarIndiceDeCarateristicas(indiceDeCaracteristicas);

	for (unsigned int i = 0; i < indiceDeCaracteristicas->size(); i++){

		int posicionFila = indiceDeCaracteristicas->at(i);
		string valor = this->setDeDatos->at(posicionFila)->at(columnaCaracteristica);
		if (!inVector(valoresDistintos,valor)){
			valoresDistintos->push_back(valor);
		}
	}
	double distintos = valoresDistintos->size();
	delete valoresDistintos;
	if (distintos != 0){
		distintos = (double) (distintos/this->getCantidadDeDatos());
	}
	return distintos;
}

/**
 * Obtiene la caracteristica con mayor ganancia, sin tener en cuenta las caracteristicas que ya fueron procesadas.
 */
int RandomForest::getCaracteristicaMayor(vector<int>* indiceDeCaracteristicas, vector<int>* caracteristicasYaProcesadas){

	unsigned int cols = this->getCantidadDeCaracteristicas();
	double ganancia;
	double gananciaMayor = 0;
	int caracteristicaMayor = 0;

	for (unsigned int i = 1; i < (cols - 1); i++){

		if (!inVector(caracteristicasYaProcesadas, i)){
			ganancia = this->getGanancia(indiceDeCaracteristicas, i);
			if (ganancia > gananciaMayor){
				gananciaMayor = ganancia;
				caracteristicaMayor = i;
			}
		}
	}
	return caracteristicaMayor;
}

/**
 * Construye el arbol de decision a partir del set de datos. Almacena el arbol armado.
 */
void RandomForest::armarArbolDeDecision(){

	Arbol* raiz = new Arbol ("");

	vector <int>* caracteristicaYaProcesada = new vector<int>;
	int caracteristicaMayor = this->getCaracteristicaMayor(raiz->getIndicesDeCaracteristica(), caracteristicaYaProcesada);

	string claveArbol = "";
	if (caracteristicaMayor > 0){
		claveArbol = this->caracteristicas->at(caracteristicaMayor);
	}else{
		claveArbol = "Hoja";
	}
	raiz->setClave(claveArbol);
	queue<Arbol*> cola;
	cola.push(raiz);

	while (!cola.empty()){

		Arbol* arbol = cola.front();

		if (caracteristicaMayor > 0){
			claveArbol = this->caracteristicas->at(caracteristicaMayor);
		}else{
			claveArbol = "Hoja";
		}
		arbol->setClave(claveArbol);
		cola.pop();

		vector<Arbol*>* hijos = this->armarHijos(arbol, caracteristicaMayor);

		if (caracteristicaMayor > 0){
			caracteristicaYaProcesada->push_back(caracteristicaMayor);
		}

		caracteristicaMayor = this->getCaracteristicaMayor(arbol->getIndicesDeCaracteristica(), caracteristicaYaProcesada);

		if (hijos != NULL){
			for (unsigned int i = 0; i < hijos->size(); i++){
				Arbol* hijo = hijos->at(i);
				if (!hijo->isHoja()){
					cola.push(hijo);
				}
			}
		}
	}
	raiz->verArbol();
	this->arboles->push_back(raiz);
	delete caracteristicaYaProcesada;
}

/**
 * Construye los hijos del arbol de decision
 */
vector<Arbol*>* RandomForest::armarHijos(Arbol* arbol,  int caracteristicaMayor){

	vector<int>* indiceDeCaracteristicas = this->armarIndiceDeCarateristicas(arbol->getIndicesDeCaracteristica());
	vector<Arbol*>* hijos = NULL;

	if (caracteristicaMayor > 0){

		map <string, Porcentaje> caracteristica = this->armarMapaDeCaracteristica(indiceDeCaracteristicas, caracteristicaMayor);
		map <string, vector<int>* > indiceDeValores = this->armarMapaDeIndices(indiceDeCaracteristicas, caracteristicaMayor);

		for (map<string, Porcentaje>::iterator it = caracteristica.begin(); it != caracteristica.end(); ++it){

			string valorCaracteristico = (string) it->first;
 			Porcentaje p = (Porcentaje) it->second;
			double probabilidad = (double) p.positivos / (p.negativos + p.positivos);
			vector<int>* indices = indiceDeValores[valorCaracteristico];
			arbol->insertarHijo("",valorCaracteristico,probabilidad,indices);
		}
		arbol->ordenarHijosPorImportancia();
		hijos = arbol->getHijos();
	}
	return hijos;
}

/**
 * Devuelve un mapa con clave caracteristica y valor el porcentaje de positividad de la misma,
 * teniendo en cuenta solamente a los datos afectados.
 */
map <string, Porcentaje> RandomForest::armarMapaDeCaracteristica (vector<int>* indiceDeCaracteristicas, int columnaCaracteristica){

	unsigned int cols = this->getCantidadDeCaracteristicas();
	map <string, Porcentaje> caracteristica;

	for (unsigned int i = 0; i < indiceDeCaracteristicas->size(); i++){
		int posValorCarac = indiceDeCaracteristicas->at(i);
		string valorCarac = this->setDeDatos->at(posValorCarac)->at(columnaCaracteristica);
		string decision = this->setDeDatos->at(posValorCarac)->at(cols-1);
		Porcentaje p;

		if(caracteristica.find(valorCarac) == caracteristica.end()){
			p.positivos = 0;
			p.negativos = 0;
		}else{
			p = caracteristica[valorCarac];
		}

		if(decision.compare(this->valorPositivo) == 0){
			p.positivos++;
		}else{
			p.negativos++;
		}

		caracteristica[valorCarac] = p;
	}
	return caracteristica;
}

/**
 * Devuelve un mapa de clave caracteristica y valor un vector de indices, donde dichos indices son los datos
 * afectados por dicha caracteristica.
 */
map <string, vector<int>* > RandomForest::armarMapaDeIndices (vector<int>* indiceDeCaracteristicas, int columnaCaracteristica){

	map <string, vector<int>* > caracteristica;

	for (unsigned int i = 0; i < indiceDeCaracteristicas->size(); i++){
		int posValorCarac = indiceDeCaracteristicas->at(i);
		string valorCarac = this->setDeDatos->at(posValorCarac)->at(columnaCaracteristica);
		vector<int>* indices;

		if(caracteristica.find(valorCarac) == caracteristica.end()){
			indices = new vector<int>;
		}else{
			indices = caracteristica[valorCarac];
		}
		indices->push_back(posValorCarac);
		caracteristica[valorCarac] = indices;
	}
	return caracteristica;
}

/**
 * Toma la decision dependiendo la consulta pasada por parametro. En caso de no encontrar decision devuelve NULL
 * La decision la tomará verdadera si la mitad o mas de las decisiones de los arboles sobre la consulta, fue verdadera.
 */
bool RandomForest::tomarDecision (map<string,string> consulta){

	if (this->arboles == NULL || this->arboles->empty()){
		return NULL;
	}

	double arbolesPositivos = 0;
	double arbolesTotales = 0;

	for (unsigned int i = 0; i < this->arboles->size(); i++){
		bool* decision = this->arboles->at(i)->tomarDecision(consulta);
		if (decision != NULL){
			if (*decision == true)
				arbolesPositivos++;
			arbolesTotales++;
			delete decision;
		}
	}

	double cantidadTotal = arbolesPositivos / arbolesTotales;
	cout << endl << endl << "cantidad positivos: " << arbolesPositivos << endl;
	cout << "cantidad total: " << arbolesTotales << endl;

	while (cantidadTotal == 0.5){
		srand((unsigned)time(0));
		cantidadTotal = (double)(rand()%(100))/100;
	}

	return cantidadTotal > 0.5;
}


/* ----------------------- FUNCIONES SECUNDARIAS --------------------------*/

/**
 * Obtiene la cantidad de reviews del set de datos.
 */
unsigned int RandomForest::getCantidadDeDatos(){
	return this->setDeDatos->size();
}

/**
 * Obtiene la cantidad de caracteristicas del set de datos,
 * teniendo en cuenta el id y la positividad de las mismas.
 */
unsigned int RandomForest::getCantidadDeCaracteristicas(){
	return this->setDeDatos->at(0)->size();
}
