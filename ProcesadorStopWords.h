#ifndef PROCESADOR_STOPWORDS_H
#define PROCESADOR_STOPWORDS_H
#include <string>
#include <vector>

class ProcesadorStopWords {
    
    public:
		ProcesadorStopWords();
		int eliminarStopWords(std::vector <std::string> *palabras_review);
        
    private:
		std::vector <std::string> listaStopWords;
		void limpiarStopWords();
		
};

#endif
