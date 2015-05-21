#ifndef PUNTUACION_H
#define PUNTUACION_H
#include <vector>
class Puntuacion {
    
    public: 
		Puntuacion();
		std::vector<char> getPuntuacion();

	private:
		std::vector<char> signosPuntuacion;
};

#endif


