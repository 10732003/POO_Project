/**
 * @file simulation.h
 * @author E.Dutruy 355726
 * @date 2023-03-07
 * @version 0.1
 * @brief simulation module interface
 */

#ifndef SIMULATION_H
#define SIMULATION_H

#include <iostream>

/**
 * @brief Simulation class is used to represent all the simulation context.
 */
class Simulation
{
private:
    std::string filename_;

public:
    Simulation(std::string filename);
    ~Simulation();
};


namespace simu
{
    Simulation read(std::string filename);
} // namespace simu

#endif /* SIMULATION_H */
