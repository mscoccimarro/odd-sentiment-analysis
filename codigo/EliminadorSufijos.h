#ifndef ELIMINADOR_SUFIJOS_H
#define ELIMINADOR_SUFIJOS_H
#include "ProcesadorSufijos.h"
#include "UtilesTexto.h"
#include <string>
class EliminadorSufijos {
	public:
		EliminadorSufijos();
		~EliminadorSufijos();
		void eliminarSufijos(std::string *palabra);

	private:
		ProcesadorSufijos *procesador;
		UtilesTexto *util;
		//Steps del proceso:
		void step1a(std::string *palabra);
		void step1b(std::string *palabra);
		void step1c(std::string *palabra);
		void step2(std::string *palabra);
		void step3(std::string *palabra);
		void step4(std::string *palabra);
		void step5(std::string *palabra);
		//Otros:
		std::string copiar(std::string::iterator finPalabra,std::string::iterator it);
		std::string definirR1(std::string palabra);
		std::string definirR2(std::string palabra);
		std::string procesarRegionRi(std::string palabra);
		int esDoble(std::string palabra);
		int esShort(std::string palabra);
		int silaba_es_short(std::string palabra);
		void cambiarYconsonante(std::string *palabra);
		void postStep1b(std::string *palabra);
		void quitarYconsonante(std::string *palabra);				
};
#endif
