#include "gui_image.h"
GUIImage::GUIImage(int x,int y,SDL_Renderer* render,SDL_Texture* texture){
    GUIImage::x=x;
    GUIImage::y=y;
    GUIImage::texture=texture;
    GUIImage::render=render;
    GUIImage::visible=true;
    SDL_QueryTexture(GUIImage::texture,0,0,&w,&h);
}
void GUIImage::update(SDL_Event* ev){

}
void GUIImage::draw(){
    guiRect.x=GUIImage::x;
    guiRect.y=GUIImage::y;
    guiRect.w=GUIImage::w;
    guiRect.h=GUIImage::h;
    SDL_RenderCopy(GUIImage::render,GUIImage::texture,0,&guiRect);
}