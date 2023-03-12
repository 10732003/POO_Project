/**
 * @file particule.cc
 * @author E.Dutruy 355726
 * @date 2023-03-10
 * @version 0.1
 * @brief src code particule module
 */

#include <iostream>
#include "../message/message.h"
#include "particule.h"
#include "../constantes/constantes.h"


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
}

// -------------------- public --------------------

Particule::Particule(double x, double y, double size):
    size_(size)
{
    position_.x = x;
    position_.y = y;

    if (size_ <= cst::d_particule_min)
    {
        error_handler(message::particle_too_small(position_.x, position_.y, size_));
    }
}