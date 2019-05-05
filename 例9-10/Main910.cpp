//Main910.cpp

#include "TEllipse910.h"
#include <iostream>
using namespace std;

int main()
{
    TShape shp(0u, 0u);
    shp.setColor(TColor(0xFF, 0x00, 0x00));
    cout << __FILE__ << ":" << __LINE__ << " ";
    shp.Draw();

    TEllipse elps01(10u, 5u, 0u, 0u);
    cout << __FILE__ << ":" << __LINE__ << " ";
    elps01.Draw();
    TEllipse elps02(10u, 5u, 20u, 30u, TColor(0x00, 0xFF, 0x00));
    cout << __FILE__ << ":" << __LINE__ << " ";
    elps02.TShape::Draw();
    cout << __FILE__ << ":" << __LINE__ << " ";
    elps02.Draw();
    elps02.setColor(shp.getColor());
    cout << __FILE__ << ":" << __LINE__ << " ";
    elps02.Draw();
    elps02.setColor(TColor(shp.getColor()));
    cout << __FILE__ << ":" << __LINE__ << " ";
    elps02.Draw();
    return 0;
}
