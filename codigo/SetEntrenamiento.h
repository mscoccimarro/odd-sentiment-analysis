#ifndef SET_ENTRENAMIENTO_H
#define SET_ENTRENAMIENTO_H
#include "SetReviews.h"
#include <string>
#include <vector>
#include <map>
#include <set>

class SetEntrenamiento: public SetReviews {

    public:

		void agregarReview(std::string id_review, std::string sentimiento_review,std::vector<std::string> contenido_review);
		std::string getSentimiento(std::string id_review);
		void get_N_caracteristicas(int n, std::vector<std::vector<std::string> *>* vectorCaracteristicas,
												std::vector< std::vector< std::vector<std::string> *>* > *matrices);													
		bool vacio();
		void vaciar();

	private:

		std::map<std::string,std::string> sentimientos;
		std::map<std::string,	std::set<std::string> > id_contenido;
		void cargar_matriz_y_vector(int i, std::vector< std::vector< std::vector<std::string> *> *> * matrices,
													std::vector<std::vector<std::string>*> * vectorCaracteristicas,
													std::vector<std::string> *ids,
													std::map<std::string,std::string> *palabras,
													std::vector<std::string> *grupo_palabras);
};
#endif


