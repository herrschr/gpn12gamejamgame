#include "UnitCtrl.hpp"
#include <SDL/SDL.h>
#include <iostream>
namespace picppgl{
ClickCtrl *clickctrl=new ClickCtrl();
void ClickCtrl::handleInput(){
    SDL_Event event;
        while( SDL_PollEvent( &event ) ) {
            if(event.type==SDL_MOUSEBUTTONDOWN){
                int x,y;
                SDL_GetMouseState(&x, &y);
                clickDispatch(x,y);
            }
            if( event.type == SDL_QUIT )
                std::exit(0);
            if( event.type == SDL_KEYDOWN ){
                switch( event.key.keysym.sym ){
                    case SDLK_b: sendSignal('b'); break;
                    case SDLK_SPACE: sendSignal(' '); break;
                    default:break;
                }


            }
        }
}

void ClickCtrl::sendSignal(char sig){
    if(last)
        last->event(sig);
}

void ClickCtrl::clickDispatch(int x, int y){
    objects.realDelete();
    //std::cout<<"clicked: "<<x<<" "<<y<<std::endl;
    for(auto &&obj:objects.data()){
        if(!boxOutsideBox(obj->getBox(), {{x,y},1,1}) ){
            obj->clicked();
            last=obj;
            return;
        }
    }
}

void ClickCtrl::addObj(clickable *obj){
    objects.add(obj);
}

void ClickCtrl::delObj(clickable *obj){
    objects.element_delete(obj);
}

}