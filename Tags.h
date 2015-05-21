#ifndef TAGS_H
#define TAGS_H
#include <string>
#include <vector>
class Tags {
    
    public: 
		Tags();
		std::vector<std::string> getTags();

	private:
		std::vector<std::string> listaTags;
};

#endif

