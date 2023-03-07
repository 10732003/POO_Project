/**
 * @file main.cc
 * @author E.Dutruy 355726
 * @date 2023-03-07
 * @version 0.1
 * @brief main file of the project
 */

#include <iostream>
#include "simulation/simulation.h"

int main(int argc, char *argv[])
{ 
    // check if there is an argument
    if (argc > 1)
    {
        Simulation simulation = simu::read(std::string(argv[1]));
    }

    return 0;
}