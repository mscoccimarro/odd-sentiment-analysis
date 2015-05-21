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
