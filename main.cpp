#include "Novella/Core/Window/Window.hpp"
#include <raylib.h>

int main(){

    auto window = Novella::Window(1000,1000, "2", 60);

    while(window.isOpen()){

        window.beginFrame();

        window.clear({0, 255, 255, 255});

        window.endFrame();
    }

    return 0;
} 