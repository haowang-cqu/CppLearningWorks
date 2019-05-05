#include "TColor910.h"

TColor::TColor(const uchar R,const uchar G,const uchar B)
{
    _RED = R;
    _GREEN = G;
    _BLUE = B;
}

TColor::TColor(const TColor& color)
{
    _RED = color._RED;
    _GREEN = color._GREEN;
    _BLUE = color._BLUE;
}

void TColor::setColor(uchar R, uchar G, uchar B)
{
    _RED = R;
    _GREEN = G;
    _BLUE = B;
}
uchar TColor::getComponent(EColorComponent component)const
{
    uchar color;
    switch(component)
    {
        case RED:
            color = _RED;
            break;
        case GREEN:
            color = _GREEN;
            break;
        case BLUE:
            color = _BLUE;
            break;
        default:
            color = 0X00;
            break;
    }
    return color;
}

TColor& TColor::operator=(const TColor& color)
{
    _RED = color._RED;
    _GREEN = color._GREEN;
    _BLUE = color._BLUE;

    return *this;
}
