#include "Novella/Core/Engine.hpp"
#include <exception>
#include <iostream>

int main(){

    Novella::Engine::create("/home/line/Projects/Novella/Test/Window.nvp");

    auto& engine = Novella::Engine::instance();

    const std::filesystem::path source = "/home/line/Projects/Novella/Test/Hallway.nsc";

    try{

    engine.loadSceneFromFile(source);

    engine.audio().play("bgm");
    
    engine.run();

    }catch(std::exception& e){

        std::cerr << e.what();
    }
    
    return 0;
} 

