#include "ProcesadorSufijos.h"
#include "UtilesTexto.h"
#include <string>
#define STRING_VACIO "" 

using namespace std;

ProcesadorSufijos::ProcesadorSufijos(){ this->util = new UtilesTexto(); }
ProcesadorSufijos::~ProcesadorSufijos(){ delete this->util; }

/* 
 * Reemplaza 'ied' por 'i' si esta precedido por mas de una letra 
 * Reemplaza 'ies' por 'i' si esta precedido por mas de una letra 
 */	
bool ProcesadorSufijos::procesar_ied_ies(string *palabra,string sufijo){
	size_t long_palabra = palabra->length(),long_sufijo = sufijo.length(),tamanio = long_palabra-long_sufijo;
	if (this->util->termina_con(*palabra,sufijo) && tamanio > 1) {
		palabra->erase(long_palabra-long_sufijo+1,2);
		return true;
	}
	return false;
}

/* Reemplaza 'sses' por 'ss'. Devuelve true si lo elimino, false en caso contrario. */
bool ProcesadorSufijos::procesar_sses(string *palabra){
	string sufijo = "sses";
	if (this->util->termina_con(*palabra,sufijo)){ 
		palabra->erase(palabra->length()-sufijo.length()+2,2); 
		return true; 
	}
	return false;
}

/* Si hay alguna vocal antes de la 's' del final (exceptuando la letra que la precede) devuelve true, sino false. */
bool ProcesadorSufijos::s_cumple_condicion(string palabra){
	string::iterator it;
	string inicio_palabra = palabra.substr(0,palabra.length()-2);
	for (it = inicio_palabra.begin();it != inicio_palabra.end(); it++) 
			if (!this->util->esConsonante(it)) return true;
	return false;
}
		
/* Elimina 's' si no tiene vocal que no este inmediatamente antes de la 's' */
bool ProcesadorSufijos::procesar_s(string *palabra){
	string::iterator it = palabra->end()-1;
	if (*it == 's' && s_cumple_condicion(*palabra)){
		palabra->erase(it);
		return true;
	}
	return false;
}

/* Elimina 'ative' si esta en region R2 (ver metodo definir R2() en la clase Procesador de sufijos) */
bool ProcesadorSufijos::procesar_ative(string *palabra,string r2){
	string sufijo = "ative";
	if (this->util->termina_con(*palabra,sufijo) && r2.find(sufijo) != string::npos){
		size_t long_sufijo = sufijo.length();
		palabra->erase(palabra->length()-long_sufijo,long_sufijo);
		return true;
	}
	return false; 
}

/* Devuelve true si hay alguna vocal antes del sufijo del tamanio recibido, false en caso contrario.*/
bool ProcesadorSufijos::palabra_cumple_condicion(string palabra,int tamanio){
	string inicio_palabra = palabra.substr(0,palabra.length()- tamanio);
	for (string::iterator it = inicio_palabra.begin(); it != inicio_palabra.end(); it++) 
		if (!this->util->esConsonante(it)) return true;
	return false;
}

/* Elimina el sufijo recibido ('ingly','edly','ing','ed') si la parte de la palabra que lo precede tiene una vocal */
bool ProcesadorSufijos::procesar_ingly_edly_ing_ed(string *palabra,string sufijo){
	size_t long_sufijo = sufijo.length();
	if (this->util->termina_con(*palabra,sufijo) && palabra_cumple_condicion(*palabra,long_sufijo)) {
		palabra->erase(palabra->length()-long_sufijo,long_sufijo);
		return true;
	}
	return false;
}

/* Reemplaza el sufijo recibido ('eedly', 'eed') por 'ee' si estan en la seccion R1 
 * (ver metodo definirR1() de la clase EliminadorSufijos) 
 */
bool ProcesadorSufijos::procesar_eedly_eed(string *palabra,string r1,string sufijo){
	if (this->util->termina_con(*palabra,sufijo) && r1.find(sufijo) != string::npos){
		size_t long_sufijo = sufijo.length();
		palabra->erase(palabra->length()-long_sufijo+2,long_sufijo-2);
		return true;
	}
	return false;
}

/* Acorta el sufijo recibido al tamaño del reemplazo recibido. */
bool ProcesadorSufijos::procesar_y_borrar(string *palabra,string r1,string sufijo,string reemplazo){
	if (this->util->termina_con(*palabra,sufijo) && r1.find(sufijo)!= string::npos){ 
		size_t long_sufijo = sufijo.length(), long_reemplazo = reemplazo.length();
		palabra->erase(palabra->length()-long_sufijo+long_reemplazo,long_sufijo-long_reemplazo);
		return true;
	}
	return false;
}

/* Reemplaza el sufijo recibido por el reemplazo recibido */
bool ProcesadorSufijos::procesar_y_reemplazar(string *palabra,string r1,string sufijo,string reemplazo){
	if (this->util->termina_con(*palabra,sufijo) && r1.find(sufijo)!= string::npos) {
		size_t long_palabra = palabra->length(),long_sufijo = sufijo.length(),long_reemplazo = reemplazo.length();
		palabra->replace(long_palabra-long_sufijo,long_reemplazo,reemplazo);
		palabra->erase(long_palabra-long_sufijo+long_reemplazo,long_sufijo-long_reemplazo);
		return true;
	}
	return false;
}

/* Reemplaza 'ogi' con 'og' si esta precedido por una 'l' */
bool ProcesadorSufijos::procesar_ogi(string *palabra,string r1){
	string sufijo = "ogi";
	if (this->util->termina_con(*palabra,sufijo) && r1.find(sufijo)!= string::npos){
		size_t long_sufijo = sufijo.length();
		string::iterator predecesora = palabra->end()-long_sufijo-1; 
		if(*predecesora == 'l'){
			palabra->erase(palabra->length()-long_sufijo+2,1);
			return true;
		}
	}
	return false;
}

/* Devuelve true si el caracter es un li-ending valido, false en caso contrario.
 * Un li-ending es valido si es alguno de los siguientes caracteres:
 * c   d   e   g   h   k   m   n   r   t
 */
bool ProcesadorSufijos::es_endingLiValido(char caracter){
	if (caracter == 'c' || caracter == 'd' || caracter == 'e' || caracter == 'g' || 
		caracter == 'h' || caracter == 'k' || caracter == 'm' || caracter == 'n' || 
		caracter == 'r' || caracter == 't' ) return true;
	return false;
}
 
/* Elimina 'li' si esta precedido por un li-ending valido (ver es_endingLiValido()) */
bool ProcesadorSufijos::procesar_li(string *palabra,string r1){
	string sufijo = "li";
	if (this->util->termina_con(*palabra,sufijo) && r1.find(sufijo)!= string::npos){
		size_t long_sufijo = sufijo.length();
		string::iterator predecesora = palabra->end()-long_sufijo-1;
		if(es_endingLiValido(*predecesora)){
			palabra->erase(palabra->length()-long_sufijo,long_sufijo);
			return true;
		}
	}
	return false;
}

/* Si el sufijo recibido se encuentra en la seccion Ri recibida (ver metodos definirR1() y definirR2() 
 * de la clase EliminadorSufijos), se elimina de la palabra 
 */
bool ProcesadorSufijos::eliminar_sufijo_de_ri(string *palabra,string ri, string sufijo){
	if (this->util->termina_con(*palabra,sufijo) && ri.find(sufijo) != string::npos){
		size_t long_sufijo = sufijo.length();
		palabra->erase(palabra->length()-long_sufijo,long_sufijo);
		return true;
	}
	return false;	
}

/* Elimina 'ion' si esta en R2 (ver metodo definirR2() de la clase EliminadorSufijos) y precedido por una 's' o una 't' */
bool ProcesadorSufijos::procesar_ion(string *palabra,string r2){
	string sufijo = "ion";
	if (this->util->termina_con(*palabra,sufijo) && r2.find("ion") != string::npos){
		size_t long_sufijo = sufijo.length();
		string::iterator predecesora = palabra->end()-long_sufijo-1;
		if(*predecesora == 's'|| *predecesora == 't'){
			palabra->erase(palabra->length()-long_sufijo,long_sufijo);
			return true;
		}
	}
	return false;
}
