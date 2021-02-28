#include "gui_serverlist.hpp"
GUIServerlist::GUIServerlist(int x,int y,int w,int h,TTF_Font* font,LanguageManager* langManager,SDL_Renderer* render,GUITextbox* textboxIP){
    GUIServerlist::x=x;
    GUIServerlist::y=y;
    GUIServerlist::w=w;
    GUIServerlist::h=h;
    GUIServerlist::selectedEntry=-1;
    GUIServerlist::render=render;
    GUIServerlist::font=font;
    GUIServerlist::titleNameX=0;
    GUIServerlist::titleIPX=0;
    GUIServerlist::titleServerName=SDL_CreateTextureFromSurface(render,TTF_RenderText_Blended(font,langManager->getFromCurrentLanguage("gamemenu_serverlistname").c_str(),{255,255,255}));
    GUIServerlist::titleServerIP=SDL_CreateTextureFromSurface(render,TTF_RenderText_Blended(font,langManager->getFromCurrentLanguage("gamemenu_serverlistip").c_str(),{255,255,255}));
    GUIServerlist::textboxIP=textboxIP;
    GUIServerlist::loadListFromFile();
    for(int i=0; i<GUIServerlist::entries.size(); i++){
        GUIServerlist::entries[i].textureName=SDL_CreateTextureFromSurface(GUIServerlist::render,TTF_RenderText_Blended(font,GUIServerlist::entries[i].name.c_str(),{255,255,255}));
        GUIServerlist::entries[i].textureIP=SDL_CreateTextureFromSurface(GUIServerlist::render,TTF_RenderText_Blended(font,GUIServerlist::entries[i].ip.c_str(),{255,255,255}));
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
        SDL_Texture* textureName=SDL_CreateTextureFromSurface(GUIServerlist::render,surfName);
        SDL_Texture* textureIP=SDL_CreateTextureFromSurface(GUIServerlist::render,surfIP);
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
    guiRect.x=GUIServerlist::x;
    guiRect.y=GUIServerlist::y;
    guiRect.w=GUIServerlist::w;
    guiRect.h=GUIServerlist::h;
    SDL_SetRenderDrawColor(GUIServerlist::render,50,50,50,255);
    SDL_RenderFillRect(GUIServerlist::render,&guiRect);
    guiRect.x=GUIServerlist::x+2;
    guiRect.y=GUIServerlist::y+1;
    GUIServerlist::titleNameX=guiRect.x;
    SDL_QueryTexture(GUIServerlist::titleServerName,0,0,&guiRect.w,&guiRect.h);
    SDL_RenderCopy(GUIServerlist::render,GUIServerlist::titleServerName,0,&guiRect);
    SDL_QueryTexture(GUIServerlist::titleServerIP,0,0,&guiRect.w,&guiRect.h);
    guiRect.x=GUIServerlist::x+(GUIServerlist::w-guiRect.w)/2+30;
    GUIServerlist::titleIPX=GUIServerlist::x+(GUIServerlist::w-guiRect.w)/2+30;
    SDL_RenderCopy(GUIServerlist::render,GUIServerlist::titleServerIP,0,&guiRect);
    if(GUIServerlist::selectedEntry>=0){
        guiRect.x=GUIServerlist::x;
        guiRect.y=GUIServerlist::selectedEntry*GUI_SERVERLIST_ENTRY_HEIGHT+GUIServerlist::y+GUI_SERVERLIST_ENTRY_HEIGHT/2;
        guiRect.w=GUIServerlist::w;
        guiRect.h=GUI_SERVERLIST_ENTRY_HEIGHT;
        SDL_SetRenderDrawColor(GUIServerlist::render,200,0,0,255);
        SDL_RenderFillRect(GUIServerlist::render,&guiRect);
    }
    for(int i=0; i<GUIServerlist::entries.size(); i++){
        guiRect.x=GUIServerlist::x+2;
        guiRect.y=GUI_SERVERLIST_ENTRY_HEIGHT*i+32;
        SDL_QueryTexture(GUIServerlist::entries[i].textureName,0,0,&guiRect.w,&guiRect.h);
        SDL_RenderCopy(GUIServerlist::render,GUIServerlist::entries[i].textureName,0,&guiRect);
        guiRect.x=GUIServerlist::titleIPX;
        SDL_QueryTexture(GUIServerlist::entries[i].textureIP,0,0,&guiRect.w,&guiRect.h);
        SDL_RenderCopy(GUIServerlist::render,GUIServerlist::entries[i].textureIP,0,&guiRect);

    }
}
void GUIServerlist::addServer(std::string name,std::string ip){
    SDL_Texture* textureName=SDL_CreateTextureFromSurface(GUIServerlist::render,TTF_RenderText_Blended(GUIServerlist::font,name.c_str(),{255,255,255}));
    SDL_Texture* textureIP=SDL_CreateTextureFromSurface(GUIServerlist::render,TTF_RenderText_Blended(GUIServerlist::font,ip.c_str(),{255,255,255}));
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