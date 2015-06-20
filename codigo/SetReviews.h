#ifndef SET_REVIEWS_H
#define SET_REVIEWS_H
#include <string>
#include <vector>
#include <set>
#include <map>
#define CADENA_VACIA " "
class SetReviews {
	public:
		virtual void agregarReview(std::string id_review, std::vector<std::string> contenido_review);
		std::vector<std::string> getIds();
		std::vector<std::string> getContenido(std::string id_review);
		std::map<std::string,std::string> * generarConsultas(std::string id_review,std::map<std::string,double>top_n_palabras);
		bool vacio();
		void vaciar();
	protected:
		std::map<std::string,	std::set<std::string> > id_contenido;
		std::vector<std::string> listaIds;
		std::map< std::string,std::vector<std::string> > reviews;
};
#endif


