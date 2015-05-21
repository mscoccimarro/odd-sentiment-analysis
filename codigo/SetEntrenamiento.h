#ifndef SET_ENTRENAMIENTO_H
#define SET_ENTRENAMIENTO_H
#include <string>
#include <vector>
#include <map>

class SetEntrenamiento {
    
    public:
		void agregarReview(std::string id_review, std::string sentimiento_review,std::vector<std::string> contenido_review);
		std::vector<std::string> getIds();
		std::vector<std::string> getContenido(std::string id_review);
		std::string getSentimiento(std::string id_review);
		bool vacio();
		void vaciar();
		
	private:
		std::vector<std::string> listaIds;
		std::map<std::string,std::string> sentimientos;
		std::map<std::string,std::vector<std::string> > reviews;
};

#endif


