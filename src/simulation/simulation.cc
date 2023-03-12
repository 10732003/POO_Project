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
#include "../message/message.h"


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
                int int_val = std::stod(value);
                data_vector.push_back(int_val);
            }
        }
    }

    #ifdef DEBUG
    void print_raw_input(std::vector<double> &raw_data_input_)
    {
        std::cout << "The vector raw_data_input_ contains the following : \n";
        for (size_t i(0); i<raw_data_input_.size(); ++i)
        {
            std::cout << raw_data_input_[i] << "\n";
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
    nbr_particules_ = input[vector_pos];

    for (int i(0); i < nbr_particules_; ++i)
    {
        Particule p(input[vector_pos+1], input[vector_pos+2], input[vector_pos+3]);
        particule_list_.push_back(p);
        vector_pos += 3;
    }
}

// -------------------- public --------------------

Simulation::Simulation(std::string filename): 
    filename_(filename), 
    raw_data_input_(),
    nbr_particules_(0),
    particule_list_()
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

    init_values(raw_data_input_);

    error_handler(message::success());
}


Simulation::~Simulation()
    {}
