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

/**
 * @brief Simulation class is used to represent all the simulation context.
 */
class Simulation
{
private:
    std::string filename_;
    std::vector<int> raw_data_input_;
    int nbr_particules;

    void error_handler(std::string msg);
    void get_data_from_file(std::ifstream &file);

public:
    Simulation(std::string filename);
    ~Simulation();
    void print(){
        for (size_t i(0); i < raw_data_input_.size(); ++i)
        {
            std::cout << raw_data_input_[i] << "\n";
        }
    }
};


#endif /* SIMULATION_H */
