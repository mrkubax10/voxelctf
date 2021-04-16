#include "gui_checkbox.h"
GUICheckbox::GUICheckbox(int x,int y,std::string text,TTF_Font *font,SDL_Renderer *render,int r,int g,int b,int chr,int chg,int chb){
    GUICheckbox::x=x;
    GUICheckbox::y=y;
    GUICheckbox::text=text;
    GUICheckbox::render=render;
    GUICheckbox::r=r;
    GUICheckbox::g=g;
    GUICheckbox::b=b;
    GUICheckbox::chr=chr;
    GUICheckbox::chg=chg;
    GUICheckbox::chb=chb;
    GUICheckbox::checked=false;
    GUICheckbox::selected=false;
    GUICheckbox::font=font;
    GUICheckbox::textureText=SDL_CreateTextureFromSurface(render,TTF_RenderUTF8_Blended(font,text.c_str(),{255,255,255}));
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
    if(GUICheckbox::checked) roundedBoxRGBA(GUICheckbox::render,GUICheckbox::x,GUICheckbox::y,GUICheckbox::x+32,GUICheckbox::y+32,5.5,GUICheckbox::chr,GUICheckbox::chg,GUICheckbox::chb,255);
    else roundedBoxRGBA(GUICheckbox::render,GUICheckbox::x,GUICheckbox::y,GUICheckbox::x+32,GUICheckbox::y+32,5.5,GUICheckbox::r,GUICheckbox::g,GUICheckbox::b,255);
    if(GUICheckbox::checked){
        thickLineRGBA(GUICheckbox::render,GUICheckbox::x+5,GUICheckbox::y+15,GUICheckbox::x+15,GUICheckbox::y+28,4,255,255,255,255);
        thickLineRGBA(GUICheckbox::render,GUICheckbox::x+14,GUICheckbox::y+27,GUICheckbox::x+27,GUICheckbox::y+5,4,255,255,255,255);
    }
    SDL_QueryTexture(GUICheckbox::textureText,0,0,&guiRect.w,&guiRect.h);
    guiRect.x=GUICheckbox::x+35;
    guiRect.y=GUICheckbox::y+(32-guiRect.h)/2;
    SDL_RenderCopy(GUICheckbox::render,GUICheckbox::textureText,0,&guiRect);
}
void GUICheckbox::setChecked(bool checked){
    GUICheckbox::checked=checked;
}
bool GUICheckbox::isChecked(){
    return GUICheckbox::checked;
}
