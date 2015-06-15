#include <iostream>
#include "RandomForest.h"

using namespace std;


/**
 * Inserta un vector a un puntero
 */
vector <string>* vectorAPuntero(string vectorPorValor[], unsigned int cantidad){
	vector<string>* puntero = new vector<string>;
	for (unsigned int j = 0; j < cantidad; j++) {
		puntero->push_back(vectorPorValor[j]);
	}
	return puntero;
}

/**
 * Inserta una matriz a un puntero
 */
vector< vector<string>* >* matrizAPuntero(string** matrizPorValor, unsigned int filas, unsigned int cols){

	vector< vector<string>* >* puntero = new vector < vector<string>* >;
	for (unsigned int i = 0; i < filas; i++) {
		vector<string>* fila;
		for (unsigned int j = 0; j < cols; j++) {
			fila->push_back(matrizPorValor[i][j]);
		}
		puntero->push_back(fila);
	}
	return puntero;
}

/**
 * Inserta los datos del ejercicio de apunte de datos.
 */
void armarRandomForestEjercicioDeDatos1(RandomForest* randomForest){
	const unsigned int filas = 8;
	const unsigned int cols = 5;

	string caracteristicas[cols] = {"id", "presencia", "estudios", "experiencia", "contratado"};

	string matriz[filas][cols] = {
	{"1", "buena",   "universitarios", "alta",  "si"},
	{"2", "mala",    "universitarios", "media", "no"},
	{"3", "buena",   "secundarios",    "alta",  "si"},
	{"4", "mala",    "universitarios", "baja",  "no"},
	{"5", "buena",   "secundarios",    "media", "si"},
	{"6", "buena",   "universitarios", "media", "si"},
	{"7", "regular", "primarios",      "baja", 	"no"},
	{"8", "regular", "universitarios", "media", "si"}
	};

	vector<string>* vectorCaracteristicas = vectorAPuntero(caracteristicas, cols);
	vector< vector<string>* >* matrizConVector = new vector < vector<string>* >;
	for (unsigned int i = 0; i < filas; i++) {
		vector<string>* fila = new vector <string>;
		for (unsigned int j = 0; j < cols; j++) {
			fila->push_back(matriz[i][j]);
		}
		matrizConVector->push_back(fila);
	}

	string valorPositivo = "si";

	randomForest->insertarSetDeDatos(vectorCaracteristicas, matrizConVector, valorPositivo);
}

/**
 * Inserta un nuevo set de datos, siguiendo con el ejercicio de apunte de datos.
 */
void armarRandomForestEjercicioDeDatos2(RandomForest* randomForest){
	const unsigned int filas = 3;
	const unsigned int cols = 5;

	string caracteristicas[cols] = {"id", "presencia", "estudios", "experiencia", "contratado"};

	string matriz[filas][cols] = {
	{"1", "buena",   "universitarios", "alta",  "si"},
	{"2", "buena",   "universitarios", "media", "no"},
	{"3", "buena",   "universitarios", "alta",  "si"},
	};

	vector<string>* vectorCaracteristicas = vectorAPuntero(caracteristicas, cols);
	vector< vector<string>* >* matrizConVector = new vector < vector<string>* >;
	for (unsigned int i = 0; i < filas; i++) {
		vector<string>* fila = new vector <string>;
		for (unsigned int j = 0; j < cols; j++) {
			fila->push_back(matriz[i][j]);
		}
		matrizConVector->push_back(fila);
	}
	string valorPositivo = "si";

	randomForest->insertarSetDeDatos(vectorCaracteristicas, matrizConVector, valorPositivo);
}

/**
 * Inserta los datos del ejercicio de you tube.
 */
void armarRandomForestEjercicioDeYouTube(RandomForest* randomForest){
	const unsigned int filas = 14;
	const unsigned int cols = 5;

	string caracteristicas[cols] = {"Day", "Outlook", "Humidity", "Wind", "Play"};

	string matriz[filas][cols] = {
	{"D1" , "Sunny",    "High",   "Weak",   "No" },
	{"D2" , "Sunny",    "High",   "Strong", "No" },
	{"D3" , "Overcast", "High",   "Weak",   "Yes"},
	{"D4" , "Rain",     "High",   "Weak",   "Yes"},
	{"D5" , "Rain",     "Normal", "Weak",   "Yes"},
	{"D6" , "Rain",     "Normal", "Strong", "No" },
	{"D7" , "Overcast", "Normal", "Strong", "Yes"},
	{"D8" , "Sunny",    "High",   "Weak",   "No" },
	{"D9" , "Sunny",    "Normal", "Weak",   "Yes"},
	{"D10", "Rain",     "Normal", "Weak",   "Yes"},
	{"D11", "Sunny",    "Normal", "Strong", "Yes"},
	{"D12", "Overcast", "High",   "Strong", "Yes"},
	{"D13", "Overcast", "Normal", "Weak",   "Yes"},
	{"D14", "Rain",     "High",   "Strong", "No" }
	};

	vector<string>* vectorCaracteristicas = vectorAPuntero(caracteristicas, cols);
	vector< vector<string>* >* matrizConVector = new vector < vector<string>* >;
	for (unsigned int i = 0; i < filas; i++) {
		vector<string>* fila = new vector <string>;
		for (unsigned int j = 0; j < cols; j++) {
			fila->push_back(matriz[i][j]);
		}
		matrizConVector->push_back(fila);
	}

	string valorPositivo = "Yes";
	randomForest->insertarSetDeDatos(vectorCaracteristicas, matrizConVector, valorPositivo);
}

/**
 * Prueba el armado del arbol.
 */
void testRandomForestEjercicioDeDatos(bool ejecutar){

	if(!ejecutar)
		return;
	cout << endl << endl << "/--------  ARMAR RANDOM FOREST - EJERCICIO APUNTES DE DATOS ---------/" << endl << endl;

	RandomForest* randomForest = new RandomForest();
	armarRandomForestEjercicioDeDatos1(randomForest);
	randomForest->armarArbolDeDecision();
	delete randomForest;
	cout << endl << "Fin armar arbol de decision" << endl;
}

/**
 * Prueba el armado del arbol.
 */
void testRandomForestEjercicioYouTube(bool ejecutar){
	if(!ejecutar)
		return;
	cout << endl << endl << "/--------  ARMAR RANDOM FOREST - EJERCICIO DE YOU TUBE ---------/" << endl << endl;

	RandomForest* randomForest = new RandomForest;
	armarRandomForestEjercicioDeYouTube(randomForest);
	randomForest->armarArbolDeDecision();
	delete randomForest;
	cout << endl << "Fin armar arbol de decision" << endl;
}

/**
 * Prueba de toma de decision con una consulta determinada.
 */
void testTomarDecisionRandomForestEjercicioDeDatos(bool ejecutar){
	if(!ejecutar)
		return;
	cout << endl << endl << "/--------  ARMAR RANDOM FOREST - TOMA DE DECISION - EJERCICIO APUNTES DE DATOS ---------/" << endl << endl;

	RandomForest* randomForest = new RandomForest();

	cout << "Arbol 1:";
	armarRandomForestEjercicioDeDatos1(randomForest);
	randomForest->armarArbolDeDecision();

	cout << endl << "Arbol 2:";
	armarRandomForestEjercicioDeDatos2(randomForest);
	randomForest->armarArbolDeDecision();


	map<string,string> consulta;
	consulta["presencia"] = "regular";
	consulta["estudios"] = "universitarios";
	consulta["experiencia"] = "alta";

	bool decision = randomForest->tomarDecision(consulta);
	delete randomForest;

	cout << endl << "Decision final: ";
	if (decision){
		cout << "Verdadera";
	}else{
		cout << "Falsa";
	}

	cout << endl << endl << endl << "Fin toma de decision" << endl;
}

/**
 * Prueba de toma de decision con una consulta determinada.
 */
void testTomarDecisionRandomForestEjercicioDeYouTube(bool ejecutar){
	if(!ejecutar)
		return;
	cout << endl << endl << "/--------  ARMAR RANDOM FOREST - TOMA DE DECISION - EJERCICIO DE YOU TUBE ---------/" << endl << endl;

	RandomForest* randomForest = new RandomForest;
	armarRandomForestEjercicioDeYouTube(randomForest);
	randomForest->armarArbolDeDecision();

	map<string,string> consulta;
	consulta["Outlook"] = "Rain";
	consulta["Humidity"] = "Normal";
	consulta["Wind"] = "Weak";

	bool decision = randomForest->tomarDecision(consulta);
	delete randomForest;

	cout << "Decision final: ";
	if (decision){
		cout << "Verdadera";
	}else{
		cout << "Falsa";
	}
	cout << endl << endl << "Fin toma de decision" << endl;
}

int main() {

	testRandomForestEjercicioDeDatos(true);
	testRandomForestEjercicioYouTube(true);
	testTomarDecisionRandomForestEjercicioDeDatos(true);
	testTomarDecisionRandomForestEjercicioDeYouTube(true);
	return 0;
}
