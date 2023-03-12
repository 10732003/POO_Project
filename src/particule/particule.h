/**
 * @file particule.h
 * @author E.Dutruy 355726
 * @date 2023-03-10
 * @version 0.1
 * @brief particule module interface
 */

#ifndef PARTICULE_H
#define PARTICULE_H

#include "../shape/shape.h"

class Particule
{
private:
    S2d position_;
    double size_;

public:
    Particule(double x, double y, double size);
};

#endif /* PARTICULE_H */
