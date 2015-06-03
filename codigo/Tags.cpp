#include "Tags.h"
#include <string>
#include <vector>

using namespace std;
	
Tags::Tags(){
	this->listaTags.push_back("<br />");
	this->listaTags.push_back("\"");
	this->listaTags.push_back("¨");
}

vector<string> Tags::getTags(){
	return this->listaTags;
}
