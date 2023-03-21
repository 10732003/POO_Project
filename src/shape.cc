/**
 * @file shape.cc
 * @author J.Ropars 364156
 * @date 2023-03-07
 * @version 0.1
 * @brief source code shape module
 */

#include <iostream>
#include <cmath>
#include "shape.h"

// to avoid write shape:: before each shape struct S2D, circle, square
using namespace shape;

namespace{
    double get_value_epszero(bool activate_epsil_zero)
    {
        if (activate_epsil_zero)
        {
            return epsil_zero;
        }
        return 0;
    }
}

bool shape::collision(circle C1, circle C2, bool activate_epsil_zero)
{
    double ezero = get_value_epszero(activate_epsil_zero);
    double D(sqrt(pow(C1.center.x-C2.center.x, 2) + pow(C1.center.y-C2.center.y, 2)));
    if (D < (C1.radius + C2.radius + ezero))
    {
        return true;
    }
    return false;
}

bool shape::collision(square S1, square S2, bool activate_epsil_zero)
{
    double ezero = get_value_epszero(activate_epsil_zero);
    if ((abs(S2.center.x-S1.center.x) < S1.size/2.0+S2.size/2.0+ezero) 
    and (abs(S2.center.y-S1.center.y) < S1.size/2.0+S2.size/2.0+ezero))
    {
        return true;
    }
    return false;
}

bool shape::collision(circle C, square S, bool activate_epsil_zero)
{
    double ezero = get_value_epszero(activate_epsil_zero);
    double L(sqrt(pow(abs(C.center.x-S.center.x)-S.size/2.0, 2) + 
    pow(abs(C.center.y-S.center.y)-S.size/2.0, 2)));
    
    if ((abs(C.center.x-S.center.x) > S.size/2.0 and 
    abs(C.center.y-S.center.y) > S.size/2.0) and (L > C.radius+ezero))
    {
        return false;
    }

    if ((abs(C.center.x-S.center.x) < S.size/2.0+C.radius+ezero) and 
    abs(C.center.y-S.center.y) < S.size/2.0+C.radius+ezero)
    {
        return true;
    }
    return false;
}

bool shape::collision(square S, circle C, bool activate_epsil_zero)
{
    return collision(C, S, activate_epsil_zero);
}

bool shape::is_inside(square S, double domain_size)
{
    if (S.center.x + S.size/2. > domain_size) // right limit
    {
        return false;
    }
    if (S.center.x - S.size/2. < -domain_size) // left limit
    {
        return false;
    }
    if (S.center.y + S.size/2. > domain_size) // top limit
    {
        return false;
    }
    if (S.center.y - S.size/2. < -domain_size) // bottom limit
    {
        return false;
    }
    
    return true;
}

bool shape::is_inside(circle C, double domain_size)
{
    if (C.center.x + C.radius > domain_size) // right limit
    {
        return false;
    }
    if (C.center.x - C.radius < -domain_size) // left limit
    {
        return false;
    }
    if (C.center.y + C.radius > domain_size) // top limit
    {
        return false;
    }
    if (C.center.y - C.radius < -domain_size) // bottom limit
    {
        return false;
    }
    
    return true;
}