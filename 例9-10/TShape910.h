//TShape910.h

#ifndef TSHAPE
#define TSHAPE

#include "GlobalType910.h"
#include "TColor910.h"

class TShape
{
    private:
        uint _x, _y;
    protected:
        TColor _color;
    public:
        TShape(uint x, uint y);
        TShape(uint x, uint y, TColor color);
        ~TShape();
        void Draw();
        void getXY(uint& x, uint& y)const;
        void setXY(uint x, uint y);
        TColor getColor()const;
        void setColor(TColor color);

};

#endif
