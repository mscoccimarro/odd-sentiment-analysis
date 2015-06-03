#include "EliminadorSufijos.h"
#include "ProcesadorSufijos.h"
#include "UtilesTexto.h"
#define STRING_VACIO ""
using namespace std;

EliminadorSufijos::EliminadorSufijos(){
	this->procesador = new ProcesadorSufijos();
	this->util = new UtilesTexto();
}

EliminadorSufijos::~EliminadorSufijos(){
	delete this->procesador;
	delete this->util;
};

string EliminadorSufijos::copiar(string::iterator it,string::iterator finPalabra){
	string ri;
	while (it != finPalabra){
		ri.push_back(*it);
		it++;
	}
	return ri;
}

string EliminadorSufijos::procesarRegionRi(string palabra){
	string::iterator it = palabra.begin();
	while (it != palabra.end()){
		if (it+1 != palabra.end() && !this->util->esConsonante(it) && this->util->esConsonante(it+1)) return copiar(it+2,palabra.end());
		else it++;
	}
	return STRING_VACIO;
}

/* definirR1()
 * Devuelve la seccion R1 de una palabra.
 * Seccion R1 = todo lo que sigue despues de la primera vocal seguida de una consonante o la region vacia del
 * final de la palabra si no existe esta consonante. 
 */
string EliminadorSufijos::definirR1(string palabra){return procesarRegionRi(palabra);}

/* definirR2()
 * Devuelve la seccion R2 de una palabra.
 * Seccion R2 = todo lo que sigue despues de la primera vocal seguida de una consonante en la region R1 
 * o la region vacia del final de R1 si no existe esta vocal.
 */
string EliminadorSufijos::definirR2(string r1){
	if (r1 != STRING_VACIO && r1.length() > 1) return procesarRegionRi(r1);	
	return STRING_VACIO;
}

/* cambiarYconsonante()
 * Si la letra inicial es 'y' no se comporta como vocal si no como consonante.
 * Si es asi, se cambia la 'y' por una 'Y' para diferenciarla de una 'y' vocal en el procesamiento de los sufijos. */
void EliminadorSufijos::cambiarYconsonante(string *palabra){
	string::iterator it = palabra->begin();
	if (*it == 'y') *it = 'Y';
}

/* quitarYconsonante()
 * Se vuelve la 'Y' inicial a 'y' */
void EliminadorSufijos::quitarYconsonante(string *palabra){
	string::iterator it = palabra->begin();
	if (*it == 'Y') *it = 'y';
}

/* esDoble()
 * Se consideran "dobles" a las siguientes combinaciones:
 * bb, dd, ff, gg, mm, nn, pp, rr, tt
 */
 
int EliminadorSufijos::esDoble(string palabra){
	if (palabra == "bb" || palabra == "dd" || palabra == "ff" || 
	    palabra == "gg" || palabra == "mm" || palabra == "nn" || 
	    palabra == "pp" || palabra == "rr" || palabra == "tt") return true;
	return false;
}

/* silaba_es_short()
 * Devuelve true si la silaba es short y false en caso contrario. 
 * Una silaba es short si esta conformada por una consonante + una vocal + una consonante distinta de w,x e Y o si
 * la palabra empieza con una vocal seguida por una consonante
 */
int EliminadorSufijos::silaba_es_short(string palabra){
	string::iterator it = palabra.end()-1 ; 
	if (palabra.length() == 2 && !this->util->esConsonante(it-1) && this->util->esConsonante(it)) return true;
	else if (palabra.length() >= 3 && this->util->esConsonante(it-2) && !this->util->esConsonante(it-1) && 
			 this->util->esConsonante(it) && *(it) != 'w' && *(it) != 'x' && *(it) != 'Y') return true;
	return false;
}

/* esShort()
 * Devuelve true si la palabra es short y false en caso contario.
 * Una palabra es short si termina con una silaba short y si su seccion R1 (ver metodo definirR1()) es nula.
*/
int EliminadorSufijos::esShort(string palabra){
	string r1 = definirR1(palabra);
	if (silaba_es_short(palabra) && r1 == STRING_VACIO) return true;
	return false;
}
	
/* Step 1a:
* Reemplazar 'sses' por 'ss' 
* Reemplazar 'ied' e 'ies' por 'i' si estan precedidos por mas de una letra, sino por 'ie' (por ejemplo 'ties' sera 'tie' y
* 'cries' sera 'cri')
* Si no tenia 'sses' al final, eliminar 's' final si la palabra contiene alguna vocal que no este inmediatamente antes de la 's' 
* (por ejemplo 'gas' conservara su 's' mientras que 'gaps' y 'kiwis' no la conservaran) y no tiene dos 'ss' al final (por ejemplo
* 'caress' conservara su s)
*/
void EliminadorSufijos::step1a(string *palabra){
	this->procesador->procesar_ied_ies(palabra,"ied");
	this->procesador->procesar_ied_ies(palabra,"ies"); 
	int sses_procesado = this->procesador->procesar_sses(palabra);	
	if (!sses_procesado) this->procesador->procesar_s(palabra);
}

/* Realiza el siguiente post-procesamiento luego del step 1b:
 * - Si la palabra termina con 'at', 'bl' o 'iz' agregar 'e' (asi por ejemplo 'luxuriat' sera 'luxuriate').
 * - Si la palabra termina con una doble (ver esDoble()), remover la ultima letra (asi 'hopp' sera 'hop').
 * - Si la palabra es short (ver esShort()), agregar 'e' (asi 'hop' sera 'hope').
 */
void EliminadorSufijos::postStep1b(string *palabra){ 
	if(palabra->length() >= 2){ 
		string final_palabra = palabra->substr(palabra->length()-2,2);
		if (esDoble(final_palabra)) palabra->erase(palabra->length()-1);
		if (final_palabra == "at" || final_palabra == "bl" || final_palabra == "iz" || esShort(*palabra)) palabra->push_back('e');	
	}
}

/* Step 1b:
 * Si la palabra tiene 'eed' o 'eedly' y estan en la seccion R1 (ver metodo definirR1()), reemplazarlos por 'ee'.
 * Si la palabra tiene 'ed', 'edly', 'ing' o 'ingly', eliminarlos si la parte de la palabra que lo precede tiene una vocal y
 * luego de la eliminacion proceder de la siguiente manera:
 * - Si la palabra termina con 'at', 'bl' o 'iz' agregar 'e' (asi por ejemplo 'luxuriat' sera 'luxuriate').
 * - Si la palabra termina con una doble (ver esDoble()), remover la ultima letra (asi 'hopp' sera 'hop').
 * - Si la palabra es short (ver esShort()), agregar 'e' (asi 'hop' sera 'hope').
 */

void EliminadorSufijos::step1b(string *palabra){
	string r1 = definirR1(*palabra);
	if(this->procesador->procesar_ingly_edly_ing_ed(palabra,"ingly")) postStep1b(palabra);
	this->procesador->procesar_eedly_eed(palabra,r1,"eedly");
	if(this->procesador->procesar_ingly_edly_ing_ed(palabra,"edly")) postStep1b(palabra);
	this->procesador->procesar_eedly_eed(palabra,r1,"eed");
	if(this->procesador->procesar_ingly_edly_ing_ed(palabra,"ing")) postStep1b(palabra);
	if(this->procesador->procesar_ingly_edly_ing_ed(palabra,"ed")) postStep1b(palabra);
}

/* Step 1c:
 * Se reemplaza el sufijo 'y' o 'Y' por 'i' si esta precedido por una consonante que NO es la primera letra de la palabra.
 * Por ejemplo 'cry', sera 'cri'; 'by' sera 'by' ; 'say' sera 'say'
 */
void EliminadorSufijos::step1c(string *palabra){
	string::iterator it = palabra->end()-1;
	if ((*it == 'y' || *it == 'Y') && this->util->esConsonante(it-1) && palabra->length()> 2) *it = 'i';	
}

/* Step 2:
 * Si la palabra contiene los siguientes sufijos y estos se encuentran en la seccion R1 de la palabra (ver metodo definirR1())
 * realizar las siguientes acciones:
 * 'ational','ation','ator': reemplazar por 'ate'  
 * 'tional': reemplazar por 'tion' 
 * 'enci': reemplazar por 'ence'
 * 'anci': reemplazar por 'ance'
 * 'abli': reemplazar por 'able' 
 * 'entli': reemplazar por 'ent' 
 * 'izer','ization': reemplazar por 'ize'
 * 'alism','aliti','alli': reemplazar por 'al'
 * 'fulness': reemplazar por 'ful'
 * 'ousli','ousness': reemplazar por 'ous'
 * 'iveness','iviti': reemplazar por 'ive'
 * 'biliti','bli': reemplazar por 'ble'
 * 'ogi': reemplazar con 'og' si esta precedido por una 'l'
 * 'fulli': reemplazar por 'ful' 
 * 'lessli': reemplazar por 'less'
 * 'li': eliminar si esta precedido por un li-ending valido (ver es_endingLiValido() en clase ProcesadorSufijos)
 */
void EliminadorSufijos::step2(string *palabra){
	string r1 = definirR1(*palabra);
 	this->procesador->procesar_y_borrar(palabra,r1,"iveness","ive");
	this->procesador->procesar_y_borrar(palabra,r1,"ousness","ous");
	this->procesador->procesar_y_borrar(palabra,r1,"fulness","ful");
	this->procesador->procesar_y_reemplazar(palabra,r1,"ational","ate");
	this->procesador->procesar_y_reemplazar(palabra,r1,"ization","ize");
	this->procesador->procesar_y_reemplazar(palabra,r1,"biliti","ble");
	this->procesador->procesar_y_borrar(palabra,r1,"lessli","less");
	this->procesador->procesar_y_borrar(palabra,r1,"tional","tion");
	this->procesador->procesar_y_reemplazar(palabra,r1,"iviti","ive");
	this->procesador->procesar_y_borrar(palabra,r1,"ousli","ous");
	this->procesador->procesar_y_borrar(palabra,r1,"alism","al");
	this->procesador->procesar_y_borrar(palabra,r1,"aliti","al");
	this->procesador->procesar_y_borrar(palabra,r1,"fulli","ful");
	this->procesador->procesar_y_reemplazar(palabra,r1,"ation","ate");
	this->procesador->procesar_y_borrar(palabra,r1,"entli","ent");
	this->procesador->procesar_y_reemplazar(palabra,r1,"ator","ate");
	this->procesador->procesar_y_borrar(palabra,r1,"alli","al");
	this->procesador->procesar_y_reemplazar(palabra,r1,"enci","ence");
	this->procesador->procesar_y_reemplazar(palabra,r1,"anci","ance");
	this->procesador->procesar_y_reemplazar(palabra,r1,"abli","able");
	this->procesador->procesar_y_borrar(palabra,r1,"izer","ize");
	this->procesador->procesar_y_reemplazar(palabra,r1,"bli","ble");
	this->procesador->procesar_ogi(palabra,r1);
	this->procesador->procesar_li(palabra,r1);
}
 
/* Step 3:
 * Si la palabra contiene alguno de estos sufijos y estos estan en la region R1 (ver definirR1())
 * realizar la accion indicada:
 * 'ational': reemplazar por 'ate'
 * 'tional': reemplazar por 'tion'
 * 'alize': reemplazar por 'al' 
 * 'icate','iciti','ical': reemplzar por 'ic'
 * 'ful','ness' eliminar 
 * 'ative': eliminar si esta en region R2 (ver definir R2()) 
 */
void EliminadorSufijos::step3(string *palabra){
	string r1 = definirR1(*palabra), r2 = definirR2(r1);
	this->procesador->procesar_y_reemplazar(palabra,r1,"ational","ate");
	this->procesador->procesar_y_borrar(palabra,r1,"tional","tion");
	this->procesador->procesar_y_borrar(palabra,r1,"alize","al");
	this->procesador->procesar_y_borrar(palabra,r1,"icate","ic");
	this->procesador->procesar_ative(palabra,r1,r2);
	this->procesador->eliminar_sufijo_de_ri(palabra,r1,"ful");
	this->procesador->eliminar_sufijo_de_ri(palabra,r1,"ness");
}

/* Step 4:
 * Si la palabra contiene alguno de los siguiente sufijos y estan en la region R2 (ver definirR2())
 * realizar la accion indicads:
 * 'arian' 'al' 'ance' 'alist' 'ence' 'er' 'ic' 'able' 'ible' 'ant' 'ement' 'ment' 'ent' 'ism' 'ate' 'iti' 'ou' 'ive' 'ize' 'ari': 
 * eliminar
 * 'ion': eliminar si esta precedido por una 's' o una 't'
 */
void EliminadorSufijos::step4(string *palabra){
	string r1 = definirR1(*palabra), r2 = definirR2(r1);
	this->procesador->eliminar_sufijo_de_ri(palabra,r2,"ement");
	this->procesador->eliminar_sufijo_de_ri(palabra,r2,"arian");
	this->procesador->eliminar_sufijo_de_ri(palabra,r2,"alist");
	this->procesador->eliminar_sufijo_de_ri(palabra,r2,"ance");
	this->procesador->eliminar_sufijo_de_ri(palabra,r2,"ence");
	this->procesador->eliminar_sufijo_de_ri(palabra,r2,"able");
	this->procesador->eliminar_sufijo_de_ri(palabra,r2,"ible");	
	this->procesador->eliminar_sufijo_de_ri(palabra,r2,"ment");
	this->procesador->eliminar_sufijo_de_ri(palabra,r2,"ant");
	this->procesador->eliminar_sufijo_de_ri(palabra,r2,"ent");
	this->procesador->eliminar_sufijo_de_ri(palabra,r2,"ism");
	this->procesador->eliminar_sufijo_de_ri(palabra,r2,"ate");
	this->procesador->eliminar_sufijo_de_ri(palabra,r2,"iti");
	this->procesador->eliminar_sufijo_de_ri(palabra,r2,"ari");
	this->procesador->procesar_ion(palabra,r2); 
	this->procesador->eliminar_sufijo_de_ri(palabra,r2,"ive");
	this->procesador->eliminar_sufijo_de_ri(palabra,r2,"ize");	
	this->procesador->eliminar_sufijo_de_ri(palabra,r2,"al");
	this->procesador->eliminar_sufijo_de_ri(palabra,r2,"er");
	this->procesador->eliminar_sufijo_de_ri(palabra,r2,"ic");
	this->procesador->eliminar_sufijo_de_ri(palabra,r2,"ou");
}

/* Step 5:
 * Buscar si la palabra contiene alguno de los siguientes sufijos y realizar la accion indicada:
 * 'e' : Eliminar si esta en R2 o si esta en R1 y no precedido por una silaba short.
 * 'l': Eliminar si esta en R2 y precedido por otra 'l'
 */
void EliminadorSufijos::step5(string *palabra){
	string r1 = definirR1(*palabra),r2 = definirR2(r1),silaba_anterior = palabra->substr(0,palabra->length()-1);
	string::iterator it = palabra->end()-1, it_r1 = r1.end()-1, it_r2 = r2.end()-1;
	if (*it == 'e' && (*it_r2 == 'e' || *it_r1  == 'e' && !silaba_es_short(silaba_anterior))) palabra->erase(it);
	if (*it == 'l' && *(it-1) == 'l' && *it_r2 == 'l') palabra->erase(it);  
}

/* Remueve los sufijos de las palabras dejando solo su 'stem' (parte de la palabra que nunca cambia)
 * Por ejemplo, dada la palabra 'produced' su stem es 'produc', ya que hay palabras como
 * 'production', 'productively', 'producing', etc.
 */
void EliminadorSufijos::eliminarSufijos(string *palabra){
	cambiarYconsonante(palabra);
// Si la palabra tiene longitud menor o igual a 2, no se le aplica ningun cambio. 
// Esto se chequea en cada paso, ya que al irse procesando la palabra esta se va acortando.
	if (palabra->length() > 2) step1a(palabra);
	if (palabra->length() > 2) step1b(palabra);
	if (palabra->length() > 2) step1c(palabra);		
	if (palabra->length() > 2) step2(palabra);
	if (palabra->length() > 2) step3(palabra);
	if (palabra->length() > 2) step4(palabra);
	if (palabra->length() > 2) step5(palabra);
	quitarYconsonante(palabra);
}
