#include "UtilesTexto.h"
#include <string>
#include <vector>

using namespace std;

vector<char> UtilesTexto::getPuntuacion(){
	vector<char> signosPuntuacion;
	signosPuntuacion.push_back('"');
	signosPuntuacion.push_back('.');
	signosPuntuacion.push_back(',');
	signosPuntuacion.push_back('?');
	signosPuntuacion.push_back('!');
	signosPuntuacion.push_back('(');
	signosPuntuacion.push_back(')');
	signosPuntuacion.push_back('{');
	signosPuntuacion.push_back('}');
	signosPuntuacion.push_back('\\');
	signosPuntuacion.push_back('-');
	signosPuntuacion.push_back(':');
	signosPuntuacion.push_back(';');
	signosPuntuacion.push_back('*');
	signosPuntuacion.push_back('/');
	signosPuntuacion.push_back('#');
	signosPuntuacion.push_back('$');
	signosPuntuacion.push_back('%');
	signosPuntuacion.push_back('=');
	signosPuntuacion.push_back('*');
	signosPuntuacion.push_back('`');
	return signosPuntuacion;
}

vector<string> UtilesTexto::getTags(){
	vector<string> listaTags;
	listaTags.push_back("<br />");
	listaTags.push_back("\"");
	listaTags.push_back("¨");
	return listaTags;
}

void UtilesTexto::aMinuscula (string *texto){

	string::iterator it;
	for (it = texto->begin(); it != texto->end(); it++)
		(*it) = tolower(*it);
}

void UtilesTexto::limpiarPuntuacion(string *texto){

	size_t pos_encontrada;
	vector<char> signos_p= getPuntuacion();
	vector<char>::iterator it;
	
	for (it = signos_p.begin(); it != signos_p.end(); it++){
		pos_encontrada = texto->find(*it);
		while(pos_encontrada != std::string::npos){
			texto->replace(pos_encontrada,1," ");
			pos_encontrada = texto->find(*it);
		}
	}
}
// Importante chequear que el iterador que se le proporciona al metodo no sea string.end()
int UtilesTexto::esConsonante(string::iterator it_letra){

	if (*it_letra == 'a' || *it_letra == 'e' || *it_letra == 'i' || *it_letra == 'o' || *it_letra == 'u') return false;
	// Si hay una consonante seguida por una 'y', la 'y' se considera vocal:
	if (*it_letra == 'y' && esConsonante(it_letra-1)) return false;
	return true;	
}
