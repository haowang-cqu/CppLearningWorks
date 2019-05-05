// TEllipse910.cpp
#include "TEllipse910.h"
#include <iostream>
using namespace std;


TEllipse::TEllipse(uint longR, uint shortR, uint x, uint y, TColor color):TShape(x, y)
{
    _longR = longR;
    _shortR = shortR;
    _color = color;  //访问父类保护成员
}

TEllipse::TEllipse(uint longR, uint shortR, uint x, uint y):TShape(x, y)
{
    _longR = longR;
    _shortR = shortR;
}

TEllipse::~TEllipse()
{
    cout << "TEllipse destructed" << endl;
}

void TEllipse::Draw()
{
    uint x, y;
    getXY(x, y);
    uint R, G, B;
    R = static_cast<uint>(_color.getComponent(RED));
    G = static_cast<uint>(_color.getComponent(GREEN));
    B = static_cast<uint>(_color.getComponent(BLUE));
    cout << "Draw an ellipse with color("
        << R << "," << G << "," << B
        << ") at point("
        << x << "," << y
        << "), longR:" << _longR << "shortR:" << _shortR << endl;
}

void TEllipse::getR(uint& longR, uint& shortR)const
{
    longR = _longR;
    shortR = _shortR;
}

void TEllipse::setR(uint longR, uint shortR)
{
    _longR = longR;
    _shortR = shortR;
}
