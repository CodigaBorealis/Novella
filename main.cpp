#include "Novella/Core/Engine.hpp"
#include <exception>
#include <filesystem>
#include <iostream>

int main(){

    const std::filesystem::path projectConfigFile = "docs/Examples/MinimalProject/Window.nvp";
    const std::filesystem::path sceneFile = "Scenes/Hallway.nsc";

    auto& engine = Novella::Engine::create(projectConfigFile);

    try{

        engine.loadSceneFromFile(sceneFile);

        engine.audio().play("bgm");
        
        engine.run();

    }catch(std::exception& e){

        std::cerr << e.what();
    }
    
    return 0;
} 

//TODO:
//Make if statements work
//Make variables work
//Make operators work
//make returns work