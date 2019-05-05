// TEllipse910.h
#ifndef TELLIPSE
#define TELLIPSE

#include "GlobalType910.h"
#include "TShape910.h"

class TEllipse: public TShape
{
    protected:
        uint _longR, _shortR;
    public:
        TEllipse(uint longR, uint shortR, uint x, uint y, TColor color);
        TEllipse(uint longR, uint shortR, uint x, uint y);
        ~TEllipse();
        void Draw();
        void getR(uint& longR, uint& shortR)const;
        void setR(uint longR, uint shortR);
};

#endif
