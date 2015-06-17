#ifndef SET_REVIEWS_H
#define SET_REVIEWS_H
#include <string>
#include <vector>
#include <map>
#define CADENA_VACIA " "
class SetReviews {
	public:
		virtual void agregarReview(std::string id_review, std::vector<std::string> contenido_review);
		std::vector<std::string> getIds();
		std::vector<std::string> getContenido(std::string id_review);
		bool vacio();
		void vaciar();
	protected:
		std::vector<std::string> listaIds;
		std::map< std::string,std::vector<std::string> > reviews;
};
#endif


