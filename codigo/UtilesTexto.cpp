#include "UtilesTexto.h"

using namespace std;

UtilesTexto::UtilesTexto(){
	this->signosPuntuacion.push_back('"');
	this->signosPuntuacion.push_back('.');
	this->signosPuntuacion.push_back(',');
	this->signosPuntuacion.push_back('?');
	this->signosPuntuacion.push_back('(');
	this->signosPuntuacion.push_back(')');
	this->signosPuntuacion.push_back('{');
	this->signosPuntuacion.push_back('}');
	this->signosPuntuacion.push_back('\\');
	this->signosPuntuacion.push_back('-');
	this->signosPuntuacion.push_back(':');
	this->signosPuntuacion.push_back(';');
	this->signosPuntuacion.push_back('*');
	this->signosPuntuacion.push_back('/');
	this->signosPuntuacion.push_back('#');
	this->signosPuntuacion.push_back('$');
	this->signosPuntuacion.push_back('%');
	this->signosPuntuacion.push_back('=');
	this->signosPuntuacion.push_back('*');
	this->signosPuntuacion.push_back('`');
	this->signosPuntuacion.push_back('_');
	this->listaTags.push_back("<br />");
	this->listaTags.push_back("\"");
	this->listaTags.push_back("¨");
	this->caracsIndeseables.push_back("");
	this->caracsIndeseables.push_back("");
}

vector<char> UtilesTexto::getPuntuacion(){ return this->signosPuntuacion; }

vector<string> UtilesTexto::getTags(){ return this->listaTags; }

vector<string> UtilesTexto::getCaracsIndeseables(){ return this->caracsIndeseables; }

/* Convierte a minuscula el texto recibido */
void UtilesTexto::aMinuscula (string *texto){
	string::iterator it;
	for (it = texto->begin(); it != texto->end(); it++)
		(*it) = tolower(*it);
}

/* Devuelve true si la palabra empieza con el prefijo recibido, false en caso contrario */
bool UtilesTexto::empieza_con(std::string palabra,std::string prefijo){  
   size_t long_palabra = palabra.length(),long_prefijo = prefijo.length();
   if (long_palabra < long_prefijo) return false;
   string inicio_palabra = palabra.substr(0,long_prefijo);
   if (inicio_palabra == prefijo) return true;
   return false;
}

/* Devuelve true si la palabra termina con el sufijo recibido, false en caso contrario */
bool UtilesTexto::termina_con(std::string palabra,std::string sufijo){  
   size_t long_palabra = palabra.length(),long_sufijo = sufijo.length();
   if (long_palabra < long_sufijo) return false;
   string final_palabra = palabra.substr(long_palabra-long_sufijo,long_sufijo);
   if (final_palabra == sufijo) return true;
   return false;
}

/* Elimina la puntuacion del texto recibido */
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

/* Devuelve true si la letra recibida es consonante, false en caso contrario.
 * Importante chequear que el iterador que se le proporciona al metodo no sea string.end() */
int UtilesTexto::esConsonante(string::iterator it_letra){
	if (*it_letra == 'a' || *it_letra == 'e' || *it_letra == 'i' || *it_letra == 'o' || *it_letra == 'u') return false;
	// Si hay una consonante seguida por una 'y', la 'y' se considera vocal:
	if (*it_letra == 'y' && esConsonante(it_letra-1)) return false;
	return true;	
}
