#ifndef GUI_H
#define GUI_H

#include <gtkmm/window.h>
#include <gtkmm/button.h>

class MyWindow : public Gtk::Window 
{
public:
	MyWindow();

protected:
    // Signal handlers
    void exit_button_clicked();


    //Member widgets:
    Gtk::Button exit_button;
};


#endif /* GUI_H */
