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


// -------------------- private --------------------

void Simulation::error_handler(std::string msg)
{
    std::cout << msg;
    if (msg == message::success())
    {
        exit(0);
    } else {
        exit(EXIT_FAILURE);
    }
}


void Simulation::get_data_from_file(std::ifstream& file)
{
    std::string line;
    while (std::getline(file >> std::ws, line))
    {
        if (line[0] == '#')
        {
            continue;
        }

        std::istringstream data(line);
        std::string value;
        while (data >> value)
        {
            bool is_valid_value = true;
            for (char c : value)
            {
                if (!isdigit(c) && c != '-' && c != '+' && c != 'e' && c != 'E')
                {
                    is_valid_value = false;
                    break;
                }
            

            if (is_valid_value)
            {
                try
                {
                    int int_value = std::stoi(value);
                    raw_data_input_.push_back(int_value);
                }
                catch (const std::invalid_argument&)
                {
                    if (value == "true")
                    {
                        raw_data_input_.push_back(1);
                    }
                    else if (value == "false")
                    {
                        raw_data_input_.push_back(0);
                    }
                    else
                    {
                        std::cout << "Invalid value: " << value << "\n";
                    }
                }
            }
            else
            {
                std::cout << "Invalid value: " << value << "\n";
            }
        }
    }
}

/*
void Simulation::get_data_from_file(std::ifstream &file)
{
    std::string line;
    while (std::getline(file >> std::ws, line))
    {
        if(line[0] == '#')
        {
            continue;
        }

        std::istringstream data(line);
        std::string value;
        while (data >> value)
        {
            if (value == "true")
            {
                raw_data_input_.push_back(1);
                std::cout << 1 << "\n";
            }
            else if (value == "false")
            {
                raw_data_input_.push_back(0);
                std::cout << 0 << "\n";
            }
            else
            {
                try
                {
                    int int_value = std::stoi(value);
                    raw_data_input_.push_back(int_value);
                    std::cout << int_value << "\n";
                }
                catch (const std::invalid_argument& error)
                {
                    std::cout << "invalid argument \n";
                }
                
                
            }
        }
    }
}*/

// -------------------- public --------------------

Simulation::Simulation(std::string filename): 
    filename_(filename), raw_data_input_()
{
    // check if we can open the file
    std::ifstream file(filename);
    if (file.fail())
    {
        error_handler(filename + " does not exist or does not open correctly");
    }
    
    get_data_from_file(file);

    file.close();
}


Simulation::~Simulation()
    {}
