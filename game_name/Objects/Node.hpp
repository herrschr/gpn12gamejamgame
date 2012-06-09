#ifndef objects_movtest_hpp
#define objects_test_hpp
#include <pic-gl/Gameflow/Level.hpp>
#include <pic-gl/Ui/gfx_object.hpp>
#include <game_name/GameLogic/UnitCtrl.hpp>
namespace picppgl{
class Node:public levelObject, gfxobject, clickable{
private:
    Image img;
    int x,y;
    Level *l;
    int unitcnt=0;
public:
    Node(int x, int y, Level*lvl);
    int unitcount()const{return unitcnt;}
    void unitcount(int nval){unitcnt=nval;}
    virtual void draw(Image&);
    virtual void update(int);
    virtual void clicked();
    virtual objinfo getBox();
    virtual ~Node();
};

}
#endif