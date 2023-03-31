/**
 * @file main.cc
 * @author J.Ropars 364156 and E.Dutruy 355726
 * @date 2023-03-07
 * @version Rendu1
 * @brief main file of the project
 */

#include <iostream>
#include <gtkmm/application.h>
#include "simulation.h"
#include "gui.h"

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
    simulation.write_file("xxx.txt");
    
    auto app = Gtk::Application::create("org.gtkmm.examples");
	
	return app->make_window_and_run<MyWindow>(1, argv);
}