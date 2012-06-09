#include "Node.hpp"
#include <pic-gl/Ui/main_window.hpp>
#include <game_name/Objects/Unit.hpp>
#include <iostream>
namespace picppgl{
Node *lastClicked=nullptr;
using namespace std;

Node::Node(int x, int y, Level *lvl): levelObject(lvl),
                                    img("game_name/gfx/town1.png",75, 60),
                                    x(x),y(y),l(lvl){
    mwindow->addLay(this, mainwindow::layer::towns);
}

void Node::draw(Image &target){
    target.apply(img, x-(img.w()/2), y-(img.h()/2));
}

void Node::clicked(){
    std::cout<<"recvd click "<<x<<" "<<y<<std::endl;
    if(lastClicked==nullptr){
        //cout<<"sel: "<<this<<endl;
        lastClicked=this;
    }else if(lastClicked==this){
        ///cout<<"double"<<endl;
        lastClicked=nullptr;
    }else if(lastClicked->unitcount()>0){
        //cout<<"SEND THE TROOPS"<<endl;
        auto ex=lastClicked->getBox().p.x;
        auto ey=lastClicked->getBox().p.y;
        lastClicked->unitcount(lastClicked->unitcount()-1);
        new Unit{ex, ey, this,l};
        //lastClicked=nullptr; 
    }else{
        cout<<"No units in "<<this<<endl;
    }
}

objinfo Node::getBox(){
    return {{x-img.w()/2,y-img.h()/2}, img.w(), img.h()};
}

void Node::update(int){}
Node::~Node(){
    mwindow->remLay(this, mainwindow::layer::towns);
    if(lastClicked==this)
        lastClicked=nullptr;
}


}