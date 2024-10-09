#include <iostream>
#include <unistd.h> // For UNIX sleep function; deprectaded but could be useful for OpenBSD port
#include <cmath>

#include "../include/AudioSystem.hpp"
#include "../include/LowPass.hpp"
#include "../include/Window.hpp"

int main(int argc, char *argv[]) {
    // GUI stuff bt is disabled right now bec it is not needed and not implemented
    auto app = Gtk::Application::create("org.gtkmm.examples.base");
    app->make_window_and_run<MainWindow>(argc, argv);
    return EXIT_SUCCESS;
}