#include "Node.hpp"
#include <pic-gl/Ui/main_window.hpp>
#include <game_name/Objects/Unit.hpp>
#include <iostream>
#include <string>
#include <sstream>
namespace picppgl{
Node *lastClicked=nullptr;
using namespace std;

Node::Node(int x, int y, Level *lvl): levelObject(lvl),
                                    img("game_name/gfx/town1.png",75, 60),
                                    x(x),y(y),l(lvl){
    mwindow->addLay(this, mainwindow::layer::towns);
}

void Node::event(char ev){
    if(!lastClicked)
        return;
    lastClicked->real_event(ev);
}

void Node::real_event(char ev){
    switch(ev){
        case 'b':
            if( !((owner==Player::User)&&(unitcnt>0)) )
                return;
            if(l->money()<25)
                return;
            l->money(l->money()-25);
            unitcnt++;
        break;
        case ' ':
            lastClicked=nullptr;
        break;
        default:
            cout<<"unknown event: "<<ev<<endl;
        break;
    }

}

void Node::draw(Image &target){
    stringstream txt;
    txt<<"u: "<<unitcnt<<" s:"<<int(storage_);
    Image::Color fg={255,255,255};
    Image::Color bg={0,0,0};
    if(unitcnt>0){
        if(owner==Player::User){
            bg={0,50,180};
        }else if(owner==Player::Ki){
            bg={150,0,0};
        }
    }

    if(lastClicked==this){
        fg={255,255,0};
        auto t=txt.str();
        txt.str("");
        txt<<"["<<t<<"]";
    }
    auto text=Image(txt.str(),18, fg, bg);
    Image tmp=img;
    tmp.apply(img, 0, 0);
    tmp.apply(text, 0, 0);
    target.apply(tmp, x-(img.w()/2), y-(img.h()/2));
}

void Node::clicked(){
    if(lastClicked==nullptr){
        lastClicked=this;
    }else if(lastClicked==this){
        lastClicked=nullptr;
    }else if( (lastClicked->unitcount()>1)&&(lastClicked->Owner()==Player::User) ){
        lastClicked->unitcount(lastClicked->unitcount()-1);
        new Unit{lastClicked->Owner(), lastClicked, this,l};
    }else{
        cout<<"You have no units to move there "<<this<<endl;
    }
}

objinfo Node::getBox(){
    return {{x-img.w()/2,y-img.h()/2}, img.w(), img.h()};
}

void Node::update(int ticks){
    if(storage_<max_storage){
        storage_+=refreshrate*ticks/1000.0;
    }
}


Node::~Node(){
    mwindow->remLay(this, mainwindow::layer::towns);
    if(lastClicked==this)
        lastClicked=nullptr;
}


}