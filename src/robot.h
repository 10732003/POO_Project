/**
 * @file robot.h
 * @author E.Dutruy 355726
 * @date 2023-03-12
 * @version 0.1
 * @brief robot module interface
 */

#ifndef ROBOT_H
#define ROBOT_H

#include <vector>
#include "shape.h"

class Robot
{
protected:
    shape::circle shape_;
public:
    shape::circle get_circle() const;
};


// -------------------- Neutraliseur --------------------

class Neutraliseur: public Robot
{
private:
    double orientation_;
    int coordination_type_;
    bool breakdown_;
    int k_update_breakdown_;
public:
    Neutraliseur(std::vector<double> &input, int &vector_pos);
    bool is_ok(std::vector<Neutraliseur> neutraliseur_list) const;
};


// -------------------- Reparateur --------------------

class Reparateur: public Robot
{
private:
    shape::S2d destination;

public:
    Reparateur(double x, double y);
    /**
     * @brief check if a particule is ok with the project directive
     * 
     * @param particule_list std::vector<Paricule>
     * @return true/false
     */
    bool is_ok(std::vector<Reparateur> reparateur_list) const;
};


// -------------------- Spatial --------------------

class Spatial: public Robot
{
private:
    int nbUpdate_;
    int nbNr_; // nombre de neutraliseur en reserve
    int nbNs_; // nombre de neutraliseur en service
    int nbNd_; // nombre de neutraliseur detruit
    int nbRr_; // nombre de reparateur en reserve
    int nbRs_; // nombre de reparateur en service

public:
    /**
     * @return the total number of neutraliseur (nbNr + nbNs + nbNd)
     */
    int get_nbr_neutraliseur() const;
    /** 
     * @return the total number of reparateur (nbRr + nbRs)
     */
    int get_nbr_reparateur() const;
    int get_nbNs() const;
    int get_nbRs() const;

    /**
     * @brief pass the value from a raw data vector to the attributes
     * 
     * @param input vector<double> such as raw_data_input_
     * @param vector_pos position to start -1
     */
    void init(std::vector<double> &input, int &vector_pos);

    /**
     * @brief check superposition between neutraliseur and reparateur robots
     * 
     * @param n_ls 
     * @param r_ls 
     * @return true if there is no superposition between them
     */
    bool neutra_repa_ok(std::vector<Neutraliseur> neutra_list, 
                        std::vector<Reparateur> repa_list) const;
};



#endif /* ROBOT_H */