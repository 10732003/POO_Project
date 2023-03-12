/**
 * @file simulation.h
 * @author E.Dutruy 355726
 * @date 2023-03-07
 * @version 0.1
 * @brief simulation module interface
 */

#ifndef SIMULATION_H
#define SIMULATION_H

#include <vector>
#include "particule.h"
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

    void get_data_from_file(std::ifstream &file);
    void init_values(std::vector<double> &data_input);

public:
    Simulation(std::string filename);
    ~Simulation();
};


#endif /* SIMULATION_H */
