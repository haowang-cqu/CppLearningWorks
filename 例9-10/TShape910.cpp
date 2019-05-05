//TShape910.cpp

#include "TShape910.h"
#include "TColor910.h"
#include <iostream>
using namespace std;

TShape::TShape(uint x, uint y):_color()
{
    _x = x;
    _y = y;
}

TShape::TShape(uint x, uint y, TColor color)
{
    _x = x;
    _y = y;
    _color = color;
}

TShape::~TShape()
{
    cout << "TShape destructed" << endl;
}

void TShape::Draw()
{
    uint R, G, B;
    R = static_cast<uint>(_color.getComponent(RED));
    G = static_cast<uint>(_color.getComponent(GREEN));
    B = static_cast<uint>(_color.getComponent(BLUE));
    cout << "Draw a shape with color(" 
        << R << ","<< G << "," << B << ") at point(" 
        << _x << "," << _y << ")" << endl;
}

void TShape::getXY(uint& x, uint& y)const
{
    x = _x;
    y = _y;
}

void TShape::setXY(uint x, uint y)
{
    _x = x;
    _y = y;
}
TColor TShape::getColor()const
{
    return _color;
}
void TShape::setColor(TColor color)
{
    _color = color;
}
