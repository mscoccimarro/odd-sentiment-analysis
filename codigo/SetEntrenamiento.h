#ifndef SET_ENTRENAMIENTO_H
#define SET_ENTRENAMIENTO_H
#include "SetReviews.h"
class SetEntrenamiento: public SetReviews {
    public:
		void agregarReview(std::string id_review, std::string sentimiento_review,std::vector<std::string> contenido_review);
		std::string getSentimiento(std::string id_review);
		bool vacio();
		void vaciar();
	private:
		std::map<std::string,std::string> sentimientos;
};
#endif


