#include "gui_checkbox.h"
GUICheckbox::GUICheckbox(int x,int y,std::string text,TTF_Font *font,Renderer* renderer,int r,int g,int b,int chr,int chg,int chb){
    GUICheckbox::x=x;
    GUICheckbox::y=y;
    GUICheckbox::text=text;
    GUICheckbox::renderer=renderer;
    GUICheckbox::r=r;
    GUICheckbox::g=g;
    GUICheckbox::b=b;
    GUICheckbox::chr=chr;
    GUICheckbox::chg=chg;
    GUICheckbox::chb=chb;
    GUICheckbox::checked=false;
    GUICheckbox::selected=false;
    GUICheckbox::font=font;
    GUICheckbox::textureText=new Texture();
    SDL_Surface* surf=TTF_RenderUTF8_Blended(font,text.c_str(),{255,255,255});
    textureText->loadFromSurface(surf);
    SDL_FreeSurface(surf);
}
void GUICheckbox::update(SDL_Event *ev){
    if(ev->type==SDL_MOUSEBUTTONDOWN){
        if(ev->button.button==SDL_BUTTON_LEFT){
            if(ev->motion.x>=GUICheckbox::x && ev->motion.x<=GUICheckbox::x+32 && ev->motion.y>=GUICheckbox::y && ev->motion.y<=GUICheckbox::y+32){
                GUICheckbox::checked=!GUICheckbox::checked;
            }
        }
    }
}
void GUICheckbox::draw(){
    if(GUICheckbox::checked)
        renderer->drawColoredRect(glm::vec4((float)GUICheckbox::chr/255.0f,(float)GUICheckbox::chg/255.0f,(float)GUICheckbox::chb/255.0f,1),glm::vec2(x,y),glm::vec2(32,32));
    else
        renderer->drawColoredRect(glm::vec4((float)GUICheckbox::r/255.0f,(float)GUICheckbox::g/255.0f,(float)GUICheckbox::b/255.0f,1),glm::vec2(x,y),glm::vec2(32,32));
    renderer->drawTexturedRect(textureText,glm::vec2(x+35,y+(32-textureText->getH())/2),glm::vec2(textureText->getW(),textureText->getH()));
}
void GUICheckbox::setChecked(bool checked){
    GUICheckbox::checked=checked;
}
bool GUICheckbox::isChecked(){
    return GUICheckbox::checked;
}
