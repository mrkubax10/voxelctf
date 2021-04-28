#include "gui_progressbar.h"
GUIProgressbar::GUIProgressbar(int x,int y,int w,int h,TTF_Font *font,Renderer *renderer,int percents,int r,int g,int b,int r1,int g1,int b1){
    GUIProgressbar::x=x;
    GUIProgressbar::y=y;
    GUIProgressbar::w=w;
    GUIProgressbar::h=h;
    GUIProgressbar::font=font;
    GUIProgressbar::renderer=renderer;
    GUIProgressbar::percents=percents;
    GUIProgressbar::r=r;
    GUIProgressbar::g=g;
    GUIProgressbar::b=b;
    GUIProgressbar::r1=r1;
    GUIProgressbar::g1=g1;
    GUIProgressbar::b1=b1;
    GUIProgressbar::texturePercent=new Texture();
    SDL_Surface* surf=TTF_RenderText_Blended(font,std::to_string(percents).c_str(),{255,255,255});
    texturePercent->loadFromSurface(surf);
    SDL_FreeSurface(surf);
}
void GUIProgressbar::update(SDL_Event *ev){

}
void GUIProgressbar::draw(){
    renderer->drawColoredRect(glm::vec4((float)r/255.0f,(float)g/255.0f,(float)b/255.0f,1),glm::vec2(x,y),glm::vec2(w,h));
    renderer->drawColoredRect(glm::vec4((float)r1/255.0f,(float)g1/255.0f,(float)b1/255.0f,1),glm::vec2(x,y),glm::vec2(GUIProgressbar::percents<=100?GUIProgressbar::w*GUIProgressbar::percents/100:GUIProgressbar::w,h));
    renderer->drawTexturedRect(texturePercent,glm::vec2(GUIProgressbar::x+GUIProgressbar::w+4,GUIProgressbar::y+(GUIProgressbar::h-guiRect.h)/2),glm::vec2(texturePercent->getW(),texturePercent->getH()));
}
void GUIProgressbar::setPercentage(int percents){
    GUIProgressbar::percents=percents;
    SDL_Surface* surf=TTF_RenderText_Blended(GUIProgressbar::font,std::to_string(GUIProgressbar::percents).c_str(),{255,255,255});
    texturePercent->loadFromSurface(surf);
    SDL_FreeSurface(surf);
}
int GUIProgressbar::getPercentage(){
    return GUIProgressbar::percents;
}
void GUIProgressbar::addPercents(int percents){
    GUIProgressbar::setPercentage(GUIProgressbar::getPercentage()+percents);
}
