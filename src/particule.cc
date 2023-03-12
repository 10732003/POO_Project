/**
 * @file particule.cc
 * @author E.Dutruy 355726
 * @date 2023-03-10
 * @version 0.1
 * @brief src code particule module
 */
#include <iostream>
#include "particule.h"
#include "message.h"
#include "constantes.h"
#include "shape.h"


namespace
{
    void error_handler(std::string msg)
    {
        std::cout << msg;
        if (msg == message::success())
        {
            exit(0);
        } else {
            exit(EXIT_FAILURE);
        }
    }

    #ifdef DEBUG
    /**
     * @brief this is a debug function
     */
    void print_particle_creation(shape::square shape_)
    {
        std::cout << "A particle was created : position (" 
            << shape_.center.x << "," << shape_.center.y << ") "
            << "size " << shape_.size << "\n";
    }
    #endif
}

// -------------------- public --------------------

Particule::Particule(double x, double y, double size)
{   
    shape::S2d position;
    position.x = x;
    position.y = y;
    shape_.center = position;
    shape_.size = size;

    #ifdef DEBUG
    print_particle_creation(shape_);
    #endif
}

bool Particule::is_ok(std::vector<Particule> particule_list)
{
    if (shape_.size <= cst::d_particule_min) // control size
    {
        error_handler(message::particle_too_small(
                                                shape_.center.x, 
                                                shape_.center.y,
                                                shape_.size
                                                ));
        return false;
    }

    for (size_t i(0); i < particule_list.size(); ++i) // control superposition
    {
        if (shape::detect_collision_square(shape_, particule_list[i].shape_))
        {
            error_handler(message::particle_superposition(
                                                shape_.center.x,
                                                shape_.center.y,
                                                particule_list[i].shape_.center.x,
                                                particule_list[i].shape_.center.y
                                                ));
            return false;
        }
    }

    if (not shape::is_square_inside(shape_, cst::dmax)) // check if it's inside domain
    {
        error_handler(message::particle_outside(
                                            shape_.center.x, 
                                            shape_.center.y, 
                                            shape_.size
                                            ));
        return false;
    }

    return true;
}