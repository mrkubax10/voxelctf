#include "gui_combobox.h"
GUICombobox::GUICombobox(int x,int y,std::vector<std::string> elements,TTF_Font *font,Renderer* renderer,int selectedItem,int r,int g,int b,int listr,int listg,int listb){
    GUICombobox::x=x;
    GUICombobox::y=y;
    GUICombobox::elements=elements;
    GUICombobox::font=font;
    GUICombobox::renderer=renderer;
    GUICombobox::selectedElement=selectedItem;
    GUICombobox::textureSelectedElement=new Texture();
    SDL_Surface* surf=TTF_RenderText_Blended(font,elements[selectedElement].c_str(),{0,0,0});
    textureSelectedElement->loadFromSurface(surf);
    SDL_FreeSurface(surf);
    GUICombobox::selected=false;
    GUICombobox::expanded=false;
    int w,h;
    GUICombobox::w2=textureSelectedElement->getW();
    GUICombobox::h2=textureSelectedElement->getH();
    GUICombobox::listh=0;
    for(int i=0; i<elements.size(); i++){
        surf=TTF_RenderUTF8_Blended(font,elements[i].c_str(),{0,0,0});
        Texture* texture=new Texture();
        texture->loadFromSurface(surf);
        GUICombobox::textureElements.push_back(texture);
        GUICombobox::listh+=textureElements[i]->getH();
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
                    SDL_Surface* surf=TTF_RenderUTF8_Blended(GUICombobox::font,GUICombobox::elements[GUICombobox::selectedElement].c_str(),{0,0,0});
                    GUICombobox::textureSelectedElement->loadFromSurface(surf);
                    SDL_FreeSurface(surf);
                    GUICombobox::expanded=false;
                }
            }else{
                GUICombobox::expanded=false;
            }
        }
    }
}

void GUICombobox::draw(){
    renderer->drawColoredRect(glm::vec4((float)GUICombobox::r/255.0f,(float)GUICombobox::g/255.0f,(float)GUICombobox::b/255.0f,1),glm::vec2(x,y),glm::vec2(w2+10,h2));
    renderer->drawTexturedRect(textureSelectedElement,glm::vec2(x,y),glm::vec2(textureSelectedElement->getW(),textureSelectedElement->getH()));
    if(GUICombobox::expanded){
        renderer->drawColoredRect(glm::vec4((float)GUICombobox::listr/255.0f,(float)GUICombobox::listg/255.0f,(float)GUICombobox::listb/255.0f,1),glm::vec2(x,y+h2),glm::vec2(w2,listh));
        for(int i=0; i<GUICombobox::elements.size(); i++){
            renderer->drawTexturedRect(textureElements[i],glm::vec2(x,y+h2*i+h2),glm::vec2(textureElements[i]->getW(),textureElements[i]->getH()));
        }
    }
}
std::string GUICombobox::getSelectedElementName(){
	return GUICombobox::elements[GUICombobox::selectedElement];
}
