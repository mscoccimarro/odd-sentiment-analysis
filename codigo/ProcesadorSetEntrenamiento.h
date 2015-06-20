#ifndef PROCESADOR_SET_ENTRENAMIENTO_H
#define PROCESADOR_SET_ENTRENAMIENTO_H
#include "ProcesadorSet.h"
#include "SetReviews.h"
#include "SetEntrenamiento.h"
#include <string>
#include <vector>

class ProcesadorSetEntrenamiento : public ProcesadorSet {
    public:
		ProcesadorSetEntrenamiento();
		ProcesadorSetEntrenamiento(std::string fileName);
    private:
		void mensaje_inicial();
		void mensaje_final();
		void error_set();
		void obtenerReview(SetReviews *setR,std::string linea);
};

#endif

