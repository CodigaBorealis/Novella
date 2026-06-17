#include "Novella/Engine.hpp"
#include <exception>
#include <iostream>

int main(){

    Novella::Engine engine;

    const std::filesystem::path source = "/home/line/projects/Novella/Test/Hallway.nsc";

    try{

    engine.loadSceneFromFile(source);

    engine.audio().play("bgm");
    
    engine.run();

    }catch(std::exception& e){

        std::cerr << e.what();
    }
    
    return 0;
} 

