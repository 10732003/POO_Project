#include <gtkmm/window.h>
#include <gtkmm/button.h>
#include <gtkmm/application.h>
#include <iostream>

#include "gui.h"

MyWindow::MyWindow() :
	exit_button("exit")
{
	/*set_title("Série4 niveau 0");
	set_default_size(500, 500);*/

	exit_button.set_margin(10);
	exit_button.signal_clicked().connect(sigc::mem_fun(*this,
			                    &MyWindow::exit_button_clicked));
	set_child(exit_button_clicked);
}



// --------------- Signal handlers ----------------
void MyWindow::exit_button_clicked()
{
	static unsigned count(0);
	
	std::cout << ++count << " Hello World \a" << std::endl;
	//close();
}