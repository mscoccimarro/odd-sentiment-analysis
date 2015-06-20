#ifndef WORD_SCORER_H
#define WORD_SCORER_H
#include "SetEntrenamiento.h"
#include <map>
#include <string>

std::map<std::string, std::string> getWordScore(int topQuantity, SetEntrenamiento *setEntrenamiento);
std::string getScale(double score);
#endif
