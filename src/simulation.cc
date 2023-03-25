/**
 * @file simulation.cc
 * @author J.Ropars 364156 and E.Dutruy 355726
 * @date 2023-03-07
 * @version Rendu1
 * @brief src code for simulation module
 */

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "simulation.h"
#include "message.h"
#include "particule.h"
#include "robot.h"


namespace
{
    void error_handler(std::string msg)
    {
        std::cout << msg;
        if (msg != message::success())
        {
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
                double double_val = std::stod(value);
                data_vector.push_back(double_val);
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
    
    if (raw_data_input_.empty())
    {
        error_handler("File is empty");
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
        p.is_ok(particule_list_, false);
        particule_list_.push_back(p); // important to check validity before push_back
        vector_pos += 3;
    }
    // manage robots
    space_robot_.init(input, vector_pos); // vector_pos is updated as well here
    space_robot_.robot_particule_collision(particule_list_, false);
    
    // init all neutra/repa robots
    space_robot_.data_analysis(vector_pos, input, particule_list_, 
                        reparateur_list_, neutraliseur_list_);
    
    space_robot_.neutra_repa_ok(neutraliseur_list_, reparateur_list_);

    #ifdef DEBUG 
    std::cout << "Simulation is set up and ready \n";
    #endif
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


void Simulation::write_file(std::string ofile)
{
    std::string content("# Actual state of the simulation\n#\n");
    content += "# Nom du scenario de test: " + filename_ + "\n#\n";
    content += "# nombre de particules puis les donnees d une particule par ligne\n";

    content += std::to_string(nbr_particules_) + "\n";
    for (size_t i(0); i < particule_list_.size(); ++i)
    {
        content += particule_list_[i].info();
    }
    
    content += "\n# donnees du robot spatial\n";
    content += space_robot_.info();

    content += "\n# donnees des nbRs robots reparateurs en service (un par ligne)\n";
    for (size_t i(0); i < reparateur_list_.size(); ++i)
    {
        content += reparateur_list_[i].info();
    }

    content += "\n";
    content += "# donnees des nbNs robots neutraliseurs en service (un par ligne)";
    content += "\n";
    for (size_t i(0); i < neutraliseur_list_.size(); ++i)
    {
        content += neutraliseur_list_[i].info();
    }

    std::ofstream file(ofile);
    file << content;
    file.close();

    #ifdef DEBUG
    std::cout << "Simulation has been reported in a file";
    #endif
}