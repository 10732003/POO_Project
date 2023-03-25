/**
 * @file simulation.h
 * @author J.Ropars 364156 and E.Dutruy 355726
 * @date 2023-03-07
 * @version Rendu1
 * @brief simulation module interface
 */

#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "particule.h"
#include "robot.h"
/**
 * @brief Simulation class is used to represent all the simulation context.
 */
class Simulation
{
private:
    std::string filename_;
    std::vector<double> raw_data_input_;
    int nbr_particules_;
    std::vector<Particule> particule_list_;
    std::vector<Reparateur> reparateur_list_;
    std::vector<Neutraliseur> neutraliseur_list_;

    Spatial space_robot_;

    void get_data_from_file(std::ifstream &file);
    void init_values(std::vector<double> &data_input);

public:
    Simulation(std::string filename);

    /**
     * @brief initialize a new simulation
     * 
     * @return true if everything went well
     */
    bool init();

    /**
     * @brief write a text file indicating the current state of the simulation
     * 
     * @param ofile string, name of the output file 
     */
    void write_file(std::string ofile);
};


#endif /* SIMULATION_H */
