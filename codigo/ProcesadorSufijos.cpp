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
void ProcesadorSufijos::procesar_ied_ies(string *palabra,string sufijo){
	size_t inicio_palabra = 0, found = palabra->find(sufijo);
	if (found != string::npos && inicio_palabra + found > 1) palabra->erase(found+1,2);
}

/* Reemplaza 'sses' por 'ss'. Devuelve true si lo elimino, false en caso contrario. */
int ProcesadorSufijos::procesar_sses(string *palabra){
	size_t found = palabra->find("sses");
	if (found != string::npos) { palabra->erase(found+2,2); return true; }
	return false;
}

/* Chequea que no haya ninguna vocal antes de la 's' del final (exceptuando la letra que la precede) */
int ProcesadorSufijos::s_cumple_condicion(string palabra){
	string::iterator it;
	if (*(palabra.end()-2) != 's')
		for (it = palabra.begin();it != palabra.end()-2; it++) 
			if (!this->util->esConsonante(it)) return true;
	return false;
}

/* Elimina 's' si no tiene vocal que no este inmediatamente antes de la 's' */
void ProcesadorSufijos::procesar_s(string *palabra){
	string::iterator it = palabra->end()-1;
	if (*it == 's' && s_cumple_condicion(*palabra)) palabra->erase(it);
}

/* Elimina 'ative' si esta en region R2 (ver metodo definir R2() en la clase Procesador de sufijos) */
void ProcesadorSufijos::procesar_ative(string *palabra,string r1,string r2){
	size_t found = palabra->find("ative");
	if (found != string::npos && r1.find("ative")!= string::npos && r2.find("ative")) palabra->erase(found,5);
}

/* Devuelve true si hay alguna vocal antes del sufijo del tamanio recibido, false en caso contrario.*/
int ProcesadorSufijos::palabra_cumple_condicion(string palabra,int tamanio){
	string inicio_palabra = palabra.substr(0,palabra.length()- tamanio);
	for (string::iterator it = inicio_palabra.begin(); it != inicio_palabra.end(); it++) 
		if (!this->util->esConsonante(it)) return true;
	return false;
}

/* Elimina el sufijo recibido ('ingly','edly','ing','ed') si la parte de la palabra que lo precede tiene una vocal */
int ProcesadorSufijos::procesar_ingly_edly_ing_ed(string *palabra,string sufijo){
	if (palabra->find(sufijo) != string::npos){
		string final_palabra = palabra->substr(palabra->length()-sufijo.length(),sufijo.length());
		if (final_palabra == sufijo && palabra_cumple_condicion(*palabra,sufijo.length())) {
			palabra->erase(palabra->length()-sufijo.length(),sufijo.length());
			return true;
		}
	}
	return false;
}

/* Reemplaza el sufijo recibido ('eedly', 'eed') por 'ee' si estan en la seccion R1 
 * (ver metodo definirR1() de la clase EliminadorSufijos) 
 */
void ProcesadorSufijos::procesar_eedly_eed(string *palabra,string r1,string sufijo){
	size_t found = palabra->find(sufijo);
	if (found != string::npos && r1.find(sufijo) != string::npos) palabra->erase(found+2,sufijo.length()-2);
}

/* Acorta el sufijo recibido al tamaño del reemplazo recibido. */
void ProcesadorSufijos::procesar_y_borrar(string *palabra,string r1,string sufijo,string reemplazo){
	size_t found = palabra->find(sufijo);
	if (found != string::npos && r1.find(sufijo)!= string::npos) 
		palabra->erase(found+reemplazo.length(),sufijo.length()-reemplazo.length());	
}

/* Reemplaza el sufijo recibido por el reemplazo recibido */
void ProcesadorSufijos::procesar_y_reemplazar(string *palabra,string r1,string sufijo,string reemplazo){
	size_t found = palabra->find(sufijo);
	if (found != string::npos && r1.find(sufijo)!= string::npos) {
		palabra->replace(found,reemplazo.length(),reemplazo);
		palabra->erase(found+reemplazo.length(),sufijo.length()-reemplazo.length());	
	}
}

/* Reemplaza 'ogi' con 'og' si esta precedido por una 'l' */
void ProcesadorSufijos::procesar_ogi(string *palabra,string r1){
	size_t found = palabra->find("ogi");
	if (found != string::npos && r1.find("ogi")!= string::npos && palabra->at(found-1) == 'l') palabra->erase(found+2,1);
}

/* Devuelve true si el caracter es un li-ending valido, false en caso contrario.
 * Un li-ending es valido si es alguno de los siguientes caracteres:
 * c   d   e   g   h   k   m   n   r   t
 */
int ProcesadorSufijos::es_endingLiValido(char caracter){
	if (caracter == 'c' || caracter == 'd' || caracter == 'e' || caracter == 'g' || 
		caracter == 'h' || caracter == 'k' || caracter == 'm' || caracter == 'n' || 
		caracter == 'r' || caracter == 't' ) return true;
	else return false;
}
 
/* Elimina 'li' si esta precedido por un li-ending valido (ver es_endingLiValido()) */
void ProcesadorSufijos::procesar_li(string *palabra,string r1){
	string final_palabra = palabra->substr(palabra->length()-2,2);
	if (final_palabra == "li" && r1.find("li")!= string::npos && 
		es_endingLiValido(palabra->at(palabra->length()-3))) palabra->erase(palabra->length()-2,2);
}

/* Si el sufijo recibido se encuentra en la seccion Ri recibida (ver metodos definirR1() y definirR2() 
 * de la clase EliminadorSufijos), se elimina de la palabra 
 */
void ProcesadorSufijos::eliminar_sufijo_de_ri(string *palabra,string ri, string sufijo){
	size_t found = palabra->find(sufijo); 
	if (found != string::npos && ri.find(sufijo) != string::npos) palabra->erase(found,sufijo.length());	
}

/* Elimina 'ion' si esta en R2 (ver metodo definirR2() de la clase EliminadorSufijos) y precedido por una 's' o una 't' */
void ProcesadorSufijos::procesar_ion(string *palabra,string r2){
	size_t found = palabra->find("ion");
	if (found != string::npos && r2.find("ion") != string::npos){
		string palabra_sin_sufijo = palabra->substr(0,palabra->length()-3);
		char letra_anterior = *(palabra_sin_sufijo.end()-1);
		if(letra_anterior == 's'|| letra_anterior == 't') palabra->erase(found,3);	
	}
}
