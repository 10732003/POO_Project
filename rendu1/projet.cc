/**
 * @file main.cc
 * @author J.Ropars 364156 and E.Dutruy 355726
 * @date 2023-03-07
 * @version Rendu1
 * @brief main file of the project
 */

#include <iostream>
#include "simulation.h"

int main(int argc, char *argv[])
{ 
    #ifdef DEBUG
    std::cout << "!!! DEBUG flag is define !!! \nPlease enter 'make clean' "
    << "and then 'make' if you want the standard version\n\n";
    #endif

    // check if there is an argument
    if (argc <= 1)
    {
        return 0;
    }
    
    Simulation simulation(argv[1]);
    simulation.init();

    return 0;
}