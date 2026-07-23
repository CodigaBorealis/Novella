#include "Novella/Core/Engine.hpp"
#include <exception>
#include <filesystem>
#include <iostream>

int main(){

    const std::filesystem::path projectConfigFile = "Test/Window.nvp";

    auto& engine = Novella::Engine::create(projectConfigFile);

    try{

        engine.loadScene("mainMenu");
        
        engine.run();

    }catch(std::exception& e){

        std::cerr << e.what();
    }
    
    return 0;
} 
//TODO:
//Save/load: moderately annoying
//Generic Builder for components: easy enough
//Add more components: relies on the feature above
//Editor: nightmare fuel
