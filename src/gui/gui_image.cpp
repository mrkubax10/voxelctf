#include "gui_image.hpp"
GUIImage::GUIImage(int x,int y,Renderer* renderer,Texture* texture){
    GUIImage::x=x;
    GUIImage::y=y;
    GUIImage::texture=texture;
    GUIImage::renderer=renderer;
    GUIImage::visible=true;
    GUIImage::w=texture->getW();
    GUIImage::h=texture->getH();
}
void GUIImage::update(SDL_Event* ev){

}
void GUIImage::draw(){
    renderer->drawTexturedRect(texture,glm::vec2(x,y),glm::vec2(w,h));
}