/**
 * @file simulation.cc
 * @author E.Dutruy 355726
 * @date 2023-03-07
 * @version 0.1
 * @brief src code for simulation module
 */

#include <iostream>
#include <fstream>
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
} // namespace


Simulation::Simulation(std::string filename): 
    filename_(filename)
    {}

Simulation::~Simulation()
    {}


Simulation simu::read(std::string filename)
{
    // check if we can open the file
    std::ifstream file(filename);
    if (file.fail())
    {
        error_handler(filename + " does not exist or does not open correctly");
    }

    Simulation simulation(filename);
    return simulation;
}