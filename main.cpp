#include "Novella/Core/Engine.hpp"
#include <exception>
#include <filesystem>
#include <iostream>

int main(){

    const std::filesystem::path projectConfigFile = "Test/Window.nvp";

    auto& engine = Novella::Engine::create(projectConfigFile);

    try{

        engine.loadSceneFromName("other");

        engine.audio().play("bgm");
        
        engine.run();

    }catch(std::exception& e){

        std::cerr << e.what();
    }
    
    return 0;
} 

