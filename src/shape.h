/**
 * @file shape.h
 * @author J.Ropars 364156 and E.Dutruy 355726
 * @date 2023-03-07
 * @version Rendu1
 * @brief shape module interface
 */

#ifndef SHAPE_H
#define SHAPE_H

namespace shape
{
    constexpr double epsil_zero(0.125);
    
    struct S2d 
    {
        double x = 0.;
        double y = 0.;
        S2d(double xx = 0, double yy = 0);
    };

    struct square
    {   
        S2d center;
        double size = 1;
    };

    struct circle
    {
        S2d center;
        double radius = 1;
    };

    /**
     * @brief detect collision between two shapes
     * 
     * @param S1 shape 1
     * @param S2 shape 2
     * @param activate_epsil_zero bool
     * @return true when there is a collision
     */
    bool collision(circle C1, circle C2, bool activate_epsil_zero = true);
    bool collision(square S1, square S2, bool activate_epsil_zero = true);
    bool collision(circle C, square S, bool activate_epsil_zero = true);
    bool collision(square S, circle C, bool activate_epsil_zero = true);

    /**
     * @brief check if a square is fully inside the domain
     * 
     * @param S square
     * @param domain_size double
     * @return true when it is inside
     */
    bool is_inside(square S, double domain_size);
    
    /**
     * @brief check if a circle is fully inside the domain
     * 
     * @param C circle
     * @param domain_size double
     * @return true when it is inside
     */
    bool is_inside(circle C, double domain_size);
} // namespace shape

#endif /* SHAPE_H */
