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

bool shape::detect_collision_circle(circle C1, circle C2, double epsil_zero)
{
  double D(sqrt(pow(C1.center.x-C2.center.x, 2) + pow(C1.center.y-C2.center.y, 2)));
  if (D < (C1.radius + C2.radius + epsil_zero))
    {
        return true;
    }
    return false;
}

bool shape::detect_collision_square(square S1, square S2, double epsil_zero)
{
    if ((abs(S2.center.x-S1.center.x) < S1.size/2.0+S2.size/2.0+epsil_zero) 
    and (abs(S2.center.y-S1.center.y) < S1.size/2.0+S2.size/2.0+epsil_zero))
    {
        return true;
    }
    return false;
}

bool shape::detect_collision_mix(circle C, square S, double epsil_zero)
{
    double L(sqrt(pow(abs(C.center.x-S.center.x)-S.size/2.0, 2) + 
    pow(abs(C.center.y-S.center.y)-S.size/2.0, 2)));
    
    if ((abs(C.center.x-S.center.x) > S.size/2.0 and 
    abs(C.center.y-S.center.y) > S.size/2.0) and (L > C.radius+epsil_zero))
    {
        return false;
    }

    if ((abs(C.center.x-S.center.x) < S.size/2.0+C.radius+epsil_zero) and 
    abs(C.center.y-S.center.y) < S.size/2.0+C.radius+epsil_zero)
    {
        return true;
    }
    return false;
}

bool shape::is_inside(square S, double domain_size)
{
    if (S.center.x + S.size > domain_size) // right limit
    {
        return false;
    }
    if (S.center.x - S.size < -domain_size) // left limit
    {
        return false;
    }
    if (S.center.y + S.size > domain_size) // top limit
    {
        return false;
    }
    if (S.center.y - S.size < -domain_size) // bottom limit
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
    /*square s;
    s.center.x = C.center.x;
    s.center.y = C.center.y;
    s.size = 2 * C.radius;
    return is_inside(s, domain_size);
    */
}