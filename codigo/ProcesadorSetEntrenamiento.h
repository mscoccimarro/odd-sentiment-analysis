#ifndef PROCESADOR_SET_ENTRENAMIENTO_H
#define PROCESADOR_SET_ENTRENAMIENTO_H
#include "SetEntrenamiento.h"
#include <string>
#include <vector>

class ProcesadorSetEntrenamiento {
    
    public:
		SetEntrenamiento* procesarSetEntrenamiento();
		
    private:
		void obtenerReview (std::string linea, std::string *id_review, std::string *sentimiento_review,	
		std::vector<std::string> *contenido_review, int *resultado);
		void error_stopWords();
		void error_setEntrenamiento();
};

#endif

