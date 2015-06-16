#ifndef UTILES_TEXTO_H
#define UTILES_TEXTO_H
#include <string>
#include <vector>

class UtilesTexto {
	public:
		UtilesTexto();
		std::vector<std::string> getTags();
		std::vector<char> getPuntuacion();
		std::vector<std::string>getCaracsIndeseables();
		void aMinuscula (std::string *texto);
		void limpiarPuntuacion(std::string *texto);
		int esConsonante(std::string::iterator it_letra);
		bool termina_con(std::string palabra,std::string sufijo); 
		bool empieza_con(std::string palabra,std::string prefijo);
	private:
		std::vector<std::string> listaTags;
		std::vector<std::string> caracsIndeseables;
		std::vector<char> signosPuntuacion;
};

#endif

