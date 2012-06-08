#ifndef objects_movtest_hpp
#define objects_test_hpp
#include <pic-gl/Gameflow/Level.hpp>
#include <pic-gl/Ui/gfx_object.hpp>
namespace picppgl{
class Unit:public levelObject, gfxobject{
private:
    Image img;
    float x=200;
    float y=200;
    float spx=50;
    float spy=100;

public:
    Unit(Level*lvl);
    virtual void draw(Image&);
    virtual void update(int);
    virtual ~Unit();
};

}
#endif