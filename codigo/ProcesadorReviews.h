#ifndef PROCESADOR_REVIEWS_H
#define PROCESADOR_REVIEWS_H
#include <string>
#include <vector>

class ProcesadorReviews {

    public:
		std::vector <std::string> obtenerPalabras(std::string texto, int *resultado);

    private:
		std::vector<std::string> procesarExclamaciones(std::string *palabra);
		void limpiarTags(std::string *texto);
		void eliminar_comillas_simples(std::string *texto);
    
};

#endif

