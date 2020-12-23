
/*
 * languagemanager.cpp
 *
 *  Created on: 15 sty 2020
 *      Author: kuba-pc
 */
#include "languagemanager.hpp"
void LanguagePack::load(std::string path){
	std::fstream file;

	file.open(path,std::ios::in);
	std::string line;
	while(getline(file,line)){
		if(line[0]=='!')continue;
		LanguagePack::texts[split(split(line,'!')[0],'=')[0]]=split(split(line,'!')[0],'=')[1];
	}
	file.close();
}
std::string LanguagePack::getText(std::string name){
	return LanguagePack::texts[name];
}
LanguageManager::LanguageManager(std::string root){
	LanguageManager::root=root;
	LanguageManager::currentLanguage="english";
}
void LanguageManager::setCurrentLanguage(std::string lang){
	LanguageManager::currentLanguage=lang;
}
std::string LanguageManager::getText(std::string lang,std::string name){
	if(LanguageManager::loadedLanguages[lang]){
		return LanguageManager::languages[lang].getText(name);
	}
	std::cout<<"(Log) [LanguageManager] Loaded language "<<lang<<std::endl;
	LanguageManager::languages[lang].load(LanguageManager::root+"/"+lang+".lang");
	LanguageManager::loadedLanguages[lang]=1;
	return LanguageManager::languages[lang].getText(name);
}
std::string LanguageManager::getFromCurrentLanguage(std::string name){
	return LanguageManager::getText(LanguageManager::currentLanguage,name);
}
