#include "Novella/Core/Engine.hpp"
#include <exception>
#include <filesystem>
#include <iostream>

int main(){

    const std::filesystem::path projectConfigFile = "Test/Window.nvp";
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

