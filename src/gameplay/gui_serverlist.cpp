#include "gui_serverlist.hpp"
GUIServerlist::GUIServerlist(int x,int y,int w,int h,TTF_Font* font,LanguageManager* langManager,Renderer* renderer,GUITextbox* textboxIP){
    GUIServerlist::x=x;
    GUIServerlist::y=y;
    GUIServerlist::w=w;
    GUIServerlist::h=h;
    GUIServerlist::selectedEntry=-1;
    GUIServerlist::renderer=renderer;
    GUIServerlist::font=font;
    GUIServerlist::titleNameX=0;
    GUIServerlist::titleIPX=0;
    GUIServerlist::titleServerName=new Texture();
    SDL_Surface* surf=TTF_RenderText_Blended(font,langManager->getFromCurrentLanguage("gamemenu_serverlistname").c_str(),{255,255,255});
    titleServerName->loadFromSurface(surf);
    SDL_FreeSurface(surf);
    GUIServerlist::titleServerIP=new Texture();
    surf=TTF_RenderText_Blended(font,langManager->getFromCurrentLanguage("gamemenu_serverlistip").c_str(),{255,255,255});
    titleServerIP->loadFromSurface(surf);
    SDL_FreeSurface(surf);
    GUIServerlist::textboxIP=textboxIP;
    GUIServerlist::loadListFromFile();
    GUIServerlist::visible=true;
    for(int i=0; i<GUIServerlist::entries.size(); i++){
        GUIServerlist::entries[i].textureName=new Texture();
        surf=TTF_RenderText_Blended(font,GUIServerlist::entries[i].name.c_str(),{255,255,255});
        entries[i].textureName->loadFromSurface(surf);
        SDL_FreeSurface(surf);
        GUIServerlist::entries[i].textureIP=new Texture();
        surf=TTF_RenderText_Blended(font,GUIServerlist::entries[i].ip.c_str(),{255,255,255});
        entries[i].textureIP->loadFromSurface(surf);
        SDL_FreeSurface(surf);
    }
    
}
void GUIServerlist::loadListFromFile(){
    std::fstream file;
    file.open("servers.txt",std::ios::in);
    if(!file.good())
        return;
    std::string line;
    while(getline(file,line)){
        std::string name=split(line,'=')[0];
        std::string ip=split(line,'=')[1];
        SDL_Surface* surfName=TTF_RenderText_Blended(GUIServerlist::font,name.c_str(),{255,255,255});
        SDL_Surface* surfIP=TTF_RenderText_Blended(GUIServerlist::font,ip.c_str(),{255,255,255});
        Texture* textureName=new Texture();
        textureName->loadFromSurface(surfName);
        Texture* textureIP=new Texture();
        textureIP->loadFromSurface(surfIP);
        GUIServerlist::entries.push_back({name,ip,textureName,textureIP});
        SDL_FreeSurface(surfName);
        SDL_FreeSurface(surfIP);
    }
    file.close();
}
bool GUIServerlist::isMouseOnList(int mx,int my){
    return (mx>=GUIServerlist::x && mx<=GUIServerlist::x+GUIServerlist::w && my>=GUIServerlist::y+32 && my<=GUIServerlist::y+GUIServerlist::h);
}
void GUIServerlist::update(SDL_Event* ev){
    if(ev->type==SDL_MOUSEBUTTONDOWN){
        if(ev->button.button==SDL_BUTTON_LEFT){
            if(GUIServerlist::isMouseOnList(ev->motion.x,ev->motion.y)){
                int selectedEntryID=(ev->motion.y+GUIServerlist::y)/GUI_SERVERLIST_ENTRY_HEIGHT-1;
                if(selectedEntryID<=GUIServerlist::entries.size()){
                    GUIServerlist::selectedEntry=selectedEntryID;
                    GUIServerlist::textboxIP->setText(GUIServerlist::entries[GUIServerlist::selectedEntry-1].ip);
                }
                else{
                    GUIServerlist::textboxIP->setText("");
                    GUIServerlist::selectedEntry=-1;
                }
                    
            }
        }
    }
}
void GUIServerlist::draw(){
    renderer->drawColoredRect(glm::vec4(50.0f/255.0f,50.0f/255.0f,50.0f/255.0f,1),glm::vec2(x,y),glm::vec2(w,h));
    GUIServerlist::titleNameX=GUIServerlist::x+2;
    renderer->drawTexturedRect(titleServerName,glm::vec2(titleNameX,GUIServerlist::y+1),glm::vec2(titleServerName->getW(),titleServerName->getH()));
    GUIServerlist::titleIPX=GUIServerlist::x+(GUIServerlist::w-guiRect.w)/2+30;
    renderer->drawTexturedRect(titleServerIP,glm::vec2(titleIPX,GUIServerlist::y+1),glm::vec2(titleServerIP->getW(),titleServerIP->getH()));
    if(GUIServerlist::selectedEntry>=0){
        renderer->drawColoredRect(glm::vec4(0.2f,0.2f,0.2f,1),glm::vec2(x,GUIServerlist::selectedEntry*GUI_SERVERLIST_ENTRY_HEIGHT+GUIServerlist::y+GUI_SERVERLIST_ENTRY_HEIGHT/2),glm::vec2(w,GUI_SERVERLIST_ENTRY_HEIGHT));
    }
    for(int i=0; i<GUIServerlist::entries.size(); i++){
        renderer->drawTexturedRect(entries[i].textureName,glm::vec2(GUIServerlist::x+2,GUI_SERVERLIST_ENTRY_HEIGHT*i+32),glm::vec2(entries[i].textureName->getW(),entries[i].textureName->getH()));
        renderer->drawTexturedRect(entries[i].textureIP,glm::vec2(titleIPX,GUI_SERVERLIST_ENTRY_HEIGHT*i+32),glm::vec2(entries[i].textureIP->getW(),entries[i].textureIP->getH()));
    }
}
void GUIServerlist::addServer(std::string name,std::string ip){
    Texture* textureName=new Texture();
    SDL_Surface* surf=TTF_RenderText_Blended(GUIServerlist::font,name.c_str(),{255,255,255});
    textureName->loadFromSurface(surf);
    SDL_FreeSurface(surf);
    Texture* textureIP=new Texture();
    surf=TTF_RenderText_Blended(GUIServerlist::font,ip.c_str(),{255,255,255});
    textureIP->loadFromSurface(surf);
    SDL_FreeSurface(surf);
    GUIServerlist::entries.push_back({name,ip,textureName,textureIP});
}
void GUIServerlist::saveListToFile(){
    std::fstream file;
    file.open("servers.txt",std::ios::out);
    for(int i=0; i<GUIServerlist::entries.size(); i++){
        file<<GUIServerlist::entries[i].name+"="+GUIServerlist::entries[i].ip<<std::endl;
    }
    file.close();
}