#include "Novella/Engine.hpp"

int main(){

    Novella::Engine engine(1920, 1200, "test", 60, "/home/line/projects/Novella/Test/2026-05-27_17-52.png",Novella::WindowFlags::Resizable);

    std::filesystem::path source = "/home/line/projects/Novella/Test/Hallway.nsc";

    engine.loadSceneFromFile(source);

    engine.run();
    
    return 0;
} 

