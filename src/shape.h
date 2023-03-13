/**
 * @file shape.h
 * @author E.Dutruy 355726
 * @date 2023-03-07
 * @version 0.1
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
     * @brief detect collision between two circles
     * 
     * @param C1 circle
     * @param C2 circle
     * @param epsil_zero double 
     * @return true when there is a collision
     */
    bool detect_collision_circle(circle C1, circle C2, double epsil_zero = 0);

    /**
     * @brief detect collision between two squares
     * 
     * @param S1 square
     * @param C2 square
     * @param epsil_zero double 
     * @return true when there is a collision
     */
    bool detect_collision_square(square S1, square S2, double epsil_zero = 0);

    /**
     * @brief detect collision between a square and a circle
     * 
     * @param C circle
     * @param S square
     * @param epsil_zero double
     * @return true when there is a collision
     */
    bool detect_collision_mix(circle C, square S, double epsil_zero = 0);

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
