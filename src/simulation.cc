/**
 * @file simulation.cc
 * @author E.Dutruy 355726
 * @date 2023-03-07
 * @version 0.1
 * @brief src code for simulation module
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "simulation.h"
#include "message.h"
#include "particule.h"


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

    void line_analysis(std::string line, std::vector<double> &data_vector)
    {
        if (line[0] == '#')
        {
            return;
        }
        
        std::istringstream data(line);
        std::string value;
        while (data >> value)
        {
            if (value[0] == '#')
            {
                break;
            }
            if (value == "true")
            {
                data_vector.push_back(1.0);
            }
            else if (value == "false")
            {
                data_vector.push_back(0.0);
            }
            else
            {
                double int_val = std::stod(value);
                data_vector.push_back(int_val);
            }
        }
    }

    #ifdef DEBUG
    /**
     * @brief this is a debug function
     */
    void print_raw_input(std::vector<double> &raw_data_input_)
    {
        std::cout << "The vector raw_data_input_ contains the following : \n";
        for (size_t i(0); i<raw_data_input_.size(); ++i)
        {
            std::cout << raw_data_input_[i] << " ";
        }
        std::cout << "\n";
    }
    #endif //DEBBUG

} // namespace


// -------------------- private --------------------

void Simulation::get_data_from_file(std::ifstream& file)
{
    std::string line;
    while (std::getline(file >> std::ws, line))
    {
        line_analysis(line, raw_data_input_);
    }
}

void Simulation::init_values(std::vector<double> &input)
{
    int vector_pos(0);

    // manage particules
    nbr_particules_ = input[vector_pos];
    for (int i(0); i < nbr_particules_; ++i)
    {
        Particule p(input[vector_pos+1], input[vector_pos+2], input[vector_pos+3]);
        p.is_ok(particule_list_);
        particule_list_.push_back(p); // important to check validity before push_back
        vector_pos += 3;
    }

    // manage robots
    space_robot_.init(input, vector_pos); // vector_pos is updated as well here
    
    for (int i(0); i < space_robot_.get_nbRs(); ++i)
    {
        Reparateur robot_rep(input[vector_pos+1], input[vector_pos+2]);
        robot_rep.is_ok(reparateur_list_); // check validity before push_back
        reparateur_list_.push_back(robot_rep);
        vector_pos += 2;
    }

    for (int i(0); i < space_robot_.get_nbNs(); ++i)
    {
        Neutraliseur robot_neutra(input, vector_pos); // vector_pos is updated here
        robot_neutra.is_ok(neutraliseur_list_); // check validity before push_back
        neutraliseur_list_.push_back(robot_neutra);
    }

    space_robot_.neutra_repa_ok(neutraliseur_list_, reparateur_list_);
}

// -------------------- public --------------------

Simulation::Simulation(std::string filename): 
    filename_(filename), 
    raw_data_input_({}),
    nbr_particules_(0),
    particule_list_({}),
    reparateur_list_({}), 
    neutraliseur_list_({})
{
    // check if we can open the file
    std::ifstream file(filename);
    if (file.fail())
    {
        error_handler(filename + " does not exist or does not open correctly");
    }
    get_data_from_file(file);
    file.close();

    #ifdef DEBUG
    print_raw_input(raw_data_input_);
    #endif
}


bool Simulation::init()
{
    init_values(raw_data_input_);

    error_handler(message::success());

    return true;
}
