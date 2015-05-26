#include "UtilesTexto.h"
#include "Puntuacion.h"
#include <string>
#include <vector>

using namespace std;

void UtilesTexto::aMinuscula (string *texto){

	string::iterator it;
	for (it = texto->begin(); it != texto->end(); it++)
		(*it) = tolower(*it);
}

void UtilesTexto::limpiarPuntuacion(string *texto){

	size_t pos_encontrada;
	Puntuacion *puntuacion = new Puntuacion();
	vector<char> signos_p= puntuacion->getPuntuacion();
	vector<char>::iterator it;
	
	for (it = signos_p.begin(); it != signos_p.end(); it++){
		pos_encontrada = texto->find(*it);
		while(pos_encontrada != std::string::npos){
			texto->erase(pos_encontrada,1);
			pos_encontrada = texto->find(*it);
		}
	}
	delete puntuacion;
}

int UtilesTexto::esConsonante(string::iterator it_letra){

	if (*it_letra == 'a' || *it_letra == 'e' || *it_letra == 'i' || *it_letra == 'o' || *it_letra == 'u') return false;
	// Si hay una consonante seguida por una 'y', la 'y' se considera vocal:
	if (*it_letra == 'y' && esConsonante(it_letra-1)) return false;
	return true;	
	
}
