#include "gui_combobox.h"
GUICombobox::GUICombobox(int x,int y,std::vector<std::string> elements,TTF_Font *font,SDL_Renderer *render,int selectedItem,int r,int g,int b,int listr,int listg,int listb){
    GUICombobox::x=x;
    GUICombobox::y=y;
    GUICombobox::elements=elements;
    GUICombobox::font=font;
    GUICombobox::render=render;
    GUICombobox::selectedElement=selectedItem;
    GUICombobox::textureSelectedElement=SDL_CreateTextureFromSurface(render,TTF_RenderText_Blended(font,elements[selectedElement].c_str(),{0,0,0}));
    GUICombobox::selected=false;
    GUICombobox::expanded=false;
    int w,h;
    SDL_QueryTexture(GUICombobox::textureSelectedElement,0,0,&w,&h);
    GUICombobox::w2=w;
    GUICombobox::h2=h;
    GUICombobox::listh=0;
    for(int i=0; i<elements.size(); i++){
        GUICombobox::textureElements.push_back(SDL_CreateTextureFromSurface(render,TTF_RenderUTF8_Blended(font,elements[i].c_str(),{0,0,0})));
        SDL_QueryTexture(GUICombobox::textureElements[i],0,0,0,&h);
        GUICombobox::listh+=h;
    }
    GUICombobox::r=r;
    GUICombobox::g=g;
    GUICombobox::b=b;
    GUICombobox::listr=listr;
    GUICombobox::listg=listg;
    GUICombobox::listb=listb;
}
void GUICombobox::update(SDL_Event *ev){
    if(ev->type==SDL_MOUSEBUTTONDOWN){
        if(ev->button.button==SDL_BUTTON_LEFT){
            if(ev->motion.x>=GUICombobox::x && ev->motion.x<=GUICombobox::x+GUICombobox::w2 && ev->motion.y>=GUICombobox::y && ev->motion.y<=GUICombobox::y+GUICombobox::h2){
                GUICombobox::expanded=!GUICombobox::expanded;
            }else if(ev->motion.x>=GUICombobox::x && ev->motion.x<=GUICombobox::x+GUICombobox::w2 && ev->motion.y>=GUICombobox::y+GUICombobox::h2 && ev->motion.y<=GUICombobox::y+GUICombobox::h2+GUICombobox::listh){
                if(GUICombobox::expanded){
                    GUICombobox::selectedElement=(ev->motion.y-GUICombobox::y)/GUICombobox::h2-1;
                    SDL_DestroyTexture(GUICombobox::textureSelectedElement);
                    GUICombobox::textureSelectedElement=SDL_CreateTextureFromSurface(GUICombobox::render,TTF_RenderUTF8_Blended(GUICombobox::font,GUICombobox::elements[GUICombobox::selectedElement].c_str(),{0,0,0}));
                    GUICombobox::expanded=false;
                }
            }else{
                GUICombobox::expanded=false;
            }
        }
    }
}

void GUICombobox::draw(){
    guiRect.x=GUICombobox::x;
    guiRect.y=GUICombobox::y;
    guiRect.w=GUICombobox::w2+10;
    guiRect.h=GUICombobox::h2;
    SDL_SetRenderDrawColor(GUICombobox::render,GUICombobox::r,GUICombobox::g,GUICombobox::b,255);
    SDL_RenderFillRect(GUICombobox::render,&guiRect);
    guiRect.x=GUICombobox::x;
    guiRect.y=GUICombobox::y;
    SDL_QueryTexture(GUICombobox::textureSelectedElement,0,0,&guiRect.w,&guiRect.h);
    SDL_RenderCopy(GUICombobox::render,GUICombobox::textureSelectedElement,0,&guiRect);
    if(GUICombobox::expanded){
        guiRect.x=GUICombobox::x;
        guiRect.y=GUICombobox::y+GUICombobox::h2;
        guiRect.w=GUICombobox::w2;
        guiRect.h=GUICombobox::listh;
        SDL_SetRenderDrawColor(GUICombobox::render,GUICombobox::listr,GUICombobox::listg,GUICombobox::listb,255);
        SDL_RenderFillRect(GUICombobox::render,&guiRect);
        for(int i=0; i<GUICombobox::elements.size(); i++){
            guiRect.y=GUICombobox::y+GUICombobox::h2+i*GUICombobox::h2;
            SDL_QueryTexture(GUICombobox::textureElements[i],0,0,&guiRect.w,&guiRect.h);
            SDL_RenderCopy(GUICombobox::render,GUICombobox::textureElements[i],0,&guiRect);
        }
    }
}
std::string GUICombobox::getSelectedElementName(){
	return GUICombobox::elements[GUICombobox::selectedElement];
}
