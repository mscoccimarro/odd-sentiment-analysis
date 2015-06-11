#ifndef UTILES_TEXTO_H
#define UTILES_TEXTO_H
#include <string>
#include <vector>

class UtilesTexto {
    
    public:
		std::vector<std::string> getTags();
		void aMinuscula (std::string *texto);
		void limpiarPuntuacion(std::string *texto);
		int esConsonante(std::string::iterator it_letra);
	private:  
		std::vector<char> getPuntuacion();
};

#endif

