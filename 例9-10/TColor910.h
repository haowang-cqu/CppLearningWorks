// TColor.h
#ifndef TCOLOR
#define TCOLOR

#include "GlobalType910.h"
enum EColorComponent{RED, GREEN, BLUE};
class TColor{
    private:
        uchar _RED, _GREEN, _BLUE;
    public:
        TColor(const uchar R = 0x00, const uchar G = 0x00, const uchar B = 0x00); //普通构造函数
        TColor(const TColor& color); //拷贝构造函数
        TColor& operator=(const TColor& color); //重载赋值运算符
        void setColor(uchar R, uchar G, uchar B);
        uchar getComponent(EColorComponent component)const;
};

#endif
