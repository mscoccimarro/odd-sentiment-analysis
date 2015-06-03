#ifndef PROCESADOR_SUFIJOS_H
#define PROCESADOR_SUFIJOS_H
#include "UtilesTexto.h"
#include <string>
class ProcesadorSufijos {
	public:
		ProcesadorSufijos();
		~ProcesadorSufijos();
		int procesar_ingly_edly_ing_ed(std::string *palabra,std::string sufijo);
		int procesar_sses(std::string *palabra);
		void eliminar_sufijo_de_ri(std::string *palabra,std::string r1,std::string sufijo);
		void procesar_ative(std::string *palabra,std::string r1,std::string r2);
		void procesar_eedly_eed(std::string *palabra,std::string r1,std::string sufijo);
		void procesar_ied_ies(std::string *palabra,std::string sufijo);
		void procesar_ion(std::string *palabra,std::string r2);	
		void procesar_s(std::string *palabra);
		void procesar_ogi(std::string *palabra,std::string r1);
		void procesar_li(std::string *palabra,std::string r1);
		void procesar_y_borrar(std::string *palabra,std::string r1,std::string sufijo,std::string reemplazo);
		void procesar_y_reemplazar(std::string *palabra,std::string r1,std::string sufijo,std::string reemplazo);
				
	private:
		UtilesTexto *util;
		int es_endingLiValido(char caracter);
		int s_cumple_condicion(std::string palabra);
		int palabra_cumple_condicion(std::string palabra,int tamanio);
};
#endif
