#ifndef UTILES_TEXTO_H
#define UTILES_TEXTO_H
#include <string>

class UtilesTexto {
    
    public:
		void aMinuscula (std::string *texto);
		void limpiarPuntuacion(std::string *texto);
		int esConsonante(std::string::iterator it_letra);
       
};

#endif

