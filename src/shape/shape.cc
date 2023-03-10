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

struct S2d 
{
    double x = 0;
    double y = 0;
};

struct square
{   
    S2d center = {0, 0};
    double distance = 1;
};

struct circle
{
    S2d center = {0, 0};
    double radius = 1;
};

//detecte une collision entre deux cercles
bool detect_collision_circle(circle C1, circle C2, double epsil_zero = 0)
{
    double D(sqrt(pow(C1.center.x-C2.center.x, 2) + pow(C1.center.y-C2.center.y, 2)));
    if (D < (C1.radius + C2.radius + epsil_zero))
    {
        return true;
    }
    return false;
}

//detecte une collision entre deux carrés
bool detect_collision_square(square S1, square S2, double epsil_zero = 0)
{
    if ((abs(S2.center.x-S1.center.x) < S1.distance/2.0+S2.distance/2.0+epsil_zero) 
    and (abs(S2.center.y-S2.center.y) < S1.distance/2.0+S2.distance/2.0+epsil_zero))
    {
        return true;
    }
    return false;
}

//detecte la collision entre un cercle et un carré
bool detect_collision_mix(circle C, square S, double epsil_zero = 0)
{
    double L(sqrt(pow(abs(C.center.x-S.center.x)-S.distance/2.0, 2) + 
    pow(abs(C.center.y-S.center.y)-S.distance/2.0, 2)));
    
    if ((abs(C.center.x-S.center.x) > S.distance/2.0 and 
    abs(C.center.y-S.center.y) > S.distance/2.0) and (L > C.radius+epsil_zero))
    {
        return false;
    }

    if ((abs(C.center.x-S.center.x) < S.distance/2.0+C.radius+epsil_zero) and 
    abs(C.center.y-S.center.y) < S.distance/2.0+C.radius+epsil_zero)
    {
        return true;
    }
    return false;
}

