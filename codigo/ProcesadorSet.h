#ifndef PROCESADOR_SET_H
#define PROCESADOR_SET_H
#include "SetReviews.h"
#include <string>

class ProcesadorSet {
    public:		
		ProcesadorSet();
		ProcesadorSet(const char* fileName);
		void procesarSet(SetReviews *setR);
		
    protected:
		const char* archivoSet;
		virtual void mensaje_inicial();
		virtual void mensaje_final();
		virtual void error_set();
		virtual void obtenerReview(SetReviews *setR,std::string linea);
		
	private:
		void error_stopWords();
};

#endif


