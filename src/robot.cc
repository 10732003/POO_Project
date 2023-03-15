/**
 * @file robot.cc
 * @author E.Dutruy 355726
 * @date 2023-03-12
 * @version 0.1
 * @brief source code for robot module
 */

#include <iostream>
#include <vector>
#include <cmath>
#include "robot.h"
#include "message.h"
#include "particule.h"
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
}


// -------------------- Robot --------------------

shape::circle Robot::get_circle() const
{
    return shape_;
}

bool Robot::robot_particule_collision(std::vector<Particule> p_vec)
{
    for (size_t i(0); i < p_vec.size(); ++i)
    {
        if (shape::detect_collision_mix(shape_, p_vec[i].get_shape()))
        {
            error_handler(message::particle_robot_superposition(
                                                p_vec[i].get_shape().center.x,
                                                p_vec[i].get_shape().center.y,
                                                p_vec[i].get_shape().size,
                                                shape_.center.x,
                                                shape_.center.y,
                                                shape_.radius
                                                ));
            return true;
        }
    }
    return false;
}

// -------------------- Neutraliseur --------------------

int Neutraliseur::get_k_update_breakdown() const
{
    return k_update_breakdown_;
}

/**void Neutraliseur::set_orientation(double orientation)
{
    while (orientation > M_PI)
    {
        orientation -= M_PI;
    }
    while (orientation <= M_PI)
    {
        orientation += M_PI;
    }
    orientation_ = orientation;
}*/

Neutraliseur::Neutraliseur(std::vector<double> &input, int &vector_pos)
{
    shape_.radius = cst::r_neutraliseur;
    shape_.center.x = input[vector_pos + 1];
    shape_.center.y = input[vector_pos + 2];
    orientation_ = input[vector_pos + 3];
    coordination_type_ = input[vector_pos + 4];
    breakdown_ = input[vector_pos + 5];
    k_update_breakdown_ = input[vector_pos + 6];
    vector_pos += 6;

    #ifdef DEBUG
    std::cout << "Neutraliseur robot was created following this information: "
        << "radius = " << shape_.radius << ", center in (" << shape_.center.x << ","
        << shape_.center.y << "), orientation = " << orientation_ << ", "
        << "coordination type = " << coordination_type_ << ", breakdown = " 
        << breakdown_ << ", k update breakdown  = " << k_update_breakdown_ << "\n";
    #endif
}

bool Neutraliseur::is_ok(std::vector<Neutraliseur> neutraliseur_list) const
{
    for (size_t i(0); i < neutraliseur_list.size(); ++i) // control superposition
    {
        if (shape::detect_collision_circle(shape_, neutraliseur_list[i].shape_))
        {
            error_handler(message::neutralizers_superposition(
                                                shape_.center.x,
                                                shape_.center.y,
                                                neutraliseur_list[i].shape_.center.x,
                                                neutraliseur_list[i].shape_.center.y
                                                ));
            return false;
        }
    }

    if (not shape::is_inside(shape_, cst::dmax))
    {
        std::string msg = "A neutraliseur is outside";
        error_handler(msg);
    }
    return true;
}

bool Neutraliseur::check_k_update_breakdown(int nbUpdate) const
{
    if (k_update_breakdown_ <= nbUpdate)
    {
        return true;
    }
    error_handler(message::invalid_k_update(
                                        shape_.center.x, 
                                        shape_.center.y,
                                        k_update_breakdown_,
                                        nbUpdate
                                        ));
    return false;
}


// -------------------- Reparateur --------------------

Reparateur::Reparateur(double x, double y)
{
    shape_.center.x = x;
    shape_.center.y = y;
    shape_.radius = cst::r_reparateur;

    #ifdef DEBUG
    std::cout << "Reparateur robot was created in (" << x << "," << y << ")\n";
    #endif
}

bool Reparateur::is_ok(std::vector<Reparateur> reparateur_list) const
{
    for (size_t i(0); i < reparateur_list.size(); ++i) // control superposition
    {
        if (shape::detect_collision_circle(shape_, reparateur_list[i].shape_))
        {
            error_handler(message::repairers_superposition(
                                                shape_.center.x,
                                                shape_.center.y,
                                                reparateur_list[i].shape_.center.x,
                                                reparateur_list[i].shape_.center.y
                                                ));
            return false;
        }
    }
    if (not shape::is_inside(shape_, cst::dmax))
    {
        std::string msg = "A reparateur is outside";
        error_handler(msg);
    }
    return true;
}


// -------------------- Spatial --------------------

int Spatial::get_nbr_neutraliseur() const { return nbNd_ + nbNr_ + nbNs_; }
int Spatial::get_nbr_reparateur() const { return nbRr_ + nbRs_; }
int Spatial::get_nbNs() const { return nbNs_; }
int Spatial::get_nbRs() const { return nbRs_; }
int Spatial::get_nbUpdate() const { return nbUpdate_; }

void Spatial::init(std::vector<double> &input, int &vector_pos)
{
    shape_.radius = cst::r_spatial;
    shape_.center.x = input[vector_pos + 1];
    shape_.center.y = input[vector_pos + 2];
    nbUpdate_ = input[vector_pos + 3];
    nbNr_ = input[vector_pos + 4];
    nbNs_ = input[vector_pos + 5];
    nbNd_ = input[vector_pos + 6];
    nbRr_ = input[vector_pos + 7];
    nbRs_ = input[vector_pos + 8];

    vector_pos += 8;

    #ifdef DEBUG
    std::cout << "Space robot was created and has this informations: "
    << "radius of " << shape_.radius 
    << ", center (" << shape_.center.x << "," << shape_.center.y << "), "
    << "nbUpdate = " << nbUpdate_ << ", nbNr = " << nbNr_ << ", nbNs = " << nbNs_
    << ", nbNd = " << nbNd_ << ", nbRr = " << nbRr_ << ", nbRs = " << nbRs_ 
    << "\n";
    #endif

    if (not shape::is_inside(shape_, cst::dmax))
    {
        error_handler(message::spatial_robot_ouside(shape_.center.x, shape_.center.y));
    }
}

bool Spatial::neutra_repa_ok(std::vector<Neutraliseur> neutra_list, 
                             std::vector<Reparateur> repa_list) const
{
    for (size_t i(0); i < neutra_list.size(); ++i)
    {
        for (size_t j(0); j < repa_list.size(); ++j)
        {
            if (shape::detect_collision_circle( neutra_list[i].get_circle(),
                                                repa_list[j].get_circle()
                                                ))
            {
                error_handler(message::repairer_neutralizer_superposition(
                                repa_list[j].get_circle().center.x,
                                repa_list[j].get_circle().center.y,
                                neutra_list[i].get_circle().center.x,
                                neutra_list[i].get_circle().center.y
                                ));
                return false;
            }
        }
    }
    return true;
}