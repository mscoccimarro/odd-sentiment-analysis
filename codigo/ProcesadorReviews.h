#ifndef PROCESADOR_REVIEWS_H
#define PROCESADOR_REVIEWS_H
#include "UtilesTexto.h"
#include <string>
#include <vector>

class ProcesadorReviews {

    public:
		std::vector <std::string> obtenerPalabras(std::string texto, int *resultado);

    private:
		std::vector<std::string> procesarExclamaciones(std::string *palabra);
		std::vector<std::string> procesarTexto(std::string *texto);
		void pre_procesarTexto(std::string *texto);
		void limpiarTexto(std::string *texto,std::vector<std::string> a_eliminar);
		void eliminar_comillas_simples(std::string *texto);
		void limpiarPalabra(std::string *palabra);
};

#endif

