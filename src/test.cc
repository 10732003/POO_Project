#include <iostream>
#include "shape.h"

using namespace shape;

int main()
{
    square a;
    a.center.x = -100;
    a.center.y = -100;
    a.size = 56.2;

    std::cout << is_square_inside(a, 128.);

    return 0;
}