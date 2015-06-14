#ifndef PROCESADOR_SUFIJOS_H
#define PROCESADOR_SUFIJOS_H
#include "UtilesTexto.h"
#include <string>
class ProcesadorSufijos {
	public:
		ProcesadorSufijos();
		~ProcesadorSufijos();
		bool procesar_ingly_edly_ing_ed(std::string *palabra,std::string sufijo);
		bool procesar_sses(std::string *palabra);
		bool eliminar_sufijo_de_ri(std::string *palabra,std::string r1,std::string sufijo);
		bool procesar_ative(std::string *palabra,std::string r2);
		bool procesar_eedly_eed(std::string *palabra,std::string r1,std::string sufijo);
		bool procesar_ied_ies(std::string *palabra,std::string sufijo);
		bool procesar_ion(std::string *palabra,std::string r2);	
		bool procesar_s(std::string *palabra);
		bool procesar_ogi(std::string *palabra,std::string r1);
		bool procesar_li(std::string *palabra,std::string r1);
		bool procesar_y_borrar(std::string *palabra,std::string r1,std::string sufijo,std::string reemplazo);
		bool procesar_y_reemplazar(std::string *palabra,std::string r1,std::string sufijo,std::string reemplazo);
				
	private:
		UtilesTexto *util;
		bool termina_con(std::string palabra,std::string sufijo); 
		bool es_endingLiValido(char caracter);
		bool s_cumple_condicion(std::string palabra);
		bool palabra_cumple_condicion(std::string palabra,int tamanio);
};
#endif
