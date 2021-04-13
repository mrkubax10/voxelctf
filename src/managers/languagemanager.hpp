
#ifndef SRC_LANGUAGEMANAGER_H_
#define SRC_LANGUAGEMANAGER_H_
#include "../global.hpp"
#include <map>
#include <fstream>
#include "../utils.hpp"
class LanguagePack{
	std::map<std::string,std::string> texts;
public:
	void load(std::string path);
	std::string getText(std::string name);
};
class LanguageManager{
	std::map<std::string,LanguagePack> languages;
	std::map<std::string,bool> loadedLanguages;
	std::string root;
	std::string currentLanguage;
public:
	LanguageManager(std::string root);
	void setCurrentLanguage(std::string lang);
	std::string getText(std::string lang,std::string name);
	std::string getFromCurrentLanguage(std::string name);
	std::string getFromLanguage(std::string name,std::string data);
};




#endif /* SRC_LANGUAGEMANAGER_H_ */
