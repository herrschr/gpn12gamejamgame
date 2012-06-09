#include "gamecore.hpp"
#include <pic-gl/Ui/main_window.hpp>
#include <pic-gl/Gameflow/Level.hpp>
#include <game_name/Objects/Unit.hpp>
#include <game_name/Objects/Node.hpp>
#include <game_name/Objects/ImgObj.hpp>
#include <game_name/GameLogic/UnitCtrl.hpp>
#include <game_name/GameLogic/Players.hpp>
#include <iostream>
namespace picppgl{
gamecore::gamecore(){
    window=new mainwindow(800, 500);
    auto lvl1=[]()->Level*{
        auto lvl=new Level(nullptr);
        auto n1=new Node(50,50,lvl);
        n1->unitcount(10);
        n1->Owner(Player::User);
        auto n2=new Node(400,100,lvl);
        auto n3=new Node(100,400,lvl);
        n3->unitcount(4);

        new ImgObj(100,200,Image("Click a town to select it, click it again to deselect.", 12),lvl);
        new ImgObj(100,250,Image("After selecting one of your towns, click another one to send a robot.", 12),lvl);
        new ImgObj(100,300,Image("To win a level if you hold all towns.", 12),lvl);
        //new ImgObj(300,300,Image("Test text", 18),lvl);
        n3->Owner(Player::Ki);
        lvl->setWinFun([=](){
            return  ((n1->unitcount() && n2->unitcount() && n3->unitcount())&&
                ( (n1->Owner()==Player::User) && (n2->Owner()==Player::User) && (n3->Owner()==Player::User) ));
        });
        return lvl;
    };
    levels.push_back(lvl1);
}
    
void gamecore::gameloop(){
    timer.start();
    for(auto &&lgen:levels){
        auto level=lgen();
        while(!level->hasWon()){
            window->render();
            level->update(timer.get_dticks());
            clickctrl->handleInput();
        }
    }
    std::cout<<"all levels played. game over"<<std::endl;
}

}