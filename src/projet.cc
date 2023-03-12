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
    #ifdef DEBUG
    std::cout << "!!! DEBUG flag is define !!! \nPlease enter 'make clean'"
    << "if you want the standard version\n";
    #endif

    // check if there is an argument
    if (argc <= 1)
    {
        return 0;
    }
    
    Simulation simulation(argv[1]);

    return 0;
}