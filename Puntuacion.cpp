#include "Puntuacion.h"
#include <string>

using namespace std;
	
Puntuacion::Puntuacion(){
	this->signosPuntuacion.push_back('"');
	this->signosPuntuacion.push_back('.');
	this->signosPuntuacion.push_back(',');
	this->signosPuntuacion.push_back('?');
	this->signosPuntuacion.push_back('!');
	this->signosPuntuacion.push_back('(');
	this->signosPuntuacion.push_back(')');
	this->signosPuntuacion.push_back('\\');
	this->signosPuntuacion.push_back('-');
	this->signosPuntuacion.push_back('_');
	this->signosPuntuacion.push_back(':');
	this->signosPuntuacion.push_back(';');
	this->signosPuntuacion.push_back('*');
	this->signosPuntuacion.push_back('/');
	this->signosPuntuacion.push_back('\'');
	this->signosPuntuacion.push_back('#');
	this->signosPuntuacion.push_back('$');
	this->signosPuntuacion.push_back('%');
	this->signosPuntuacion.push_back('=');
	this->signosPuntuacion.push_back('*');
	this->signosPuntuacion.push_back('`');
}

vector<char> Puntuacion::getPuntuacion(){
	return this->signosPuntuacion;
}
