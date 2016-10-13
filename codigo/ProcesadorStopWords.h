#ifndef PROCESADOR_STOPWORDS_H
#define PROCESADOR_STOPWORDS_H
#include <set>
#include <vector>
#include <string>

class ProcesadorStopWords {
    
    public:
		ProcesadorStopWords();
		int eliminarStopWords(std::vector<std::string> *palabras_review);
		
    private:
		std::set<std::string> listaStopWords;
		
};

#endif
