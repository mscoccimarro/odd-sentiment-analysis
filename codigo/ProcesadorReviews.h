#ifndef PROCESADOR_REVIEWS_H
#define PROCESADOR_REVIEWS_H
#include <string>
#include <vector>

class ProcesadorReviews {

    public:
		std::vector <std::string> obtenerPalabras(std::string texto, int *resultado);

    private:
		void limpiarTags (std::string *texto);
    
};

#endif

