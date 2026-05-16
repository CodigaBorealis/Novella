#include "Novella/Audio/AudioResource.hpp"
#include "Novella/Core/Window/Window.hpp"
#include "Novella/Graphics/Color.hpp"
#include "Novella/Rendering/Renderer.hpp"
#include "Novella/Rendering/ResourceManager.hpp"
#include "Novella/Audio/AudioSystem.hpp"
#include <raylib.h>

int main(){

    auto window = Novella::Window(1000,1000, "2", 60);

    Novella::Rendering::ResourceManager resources;

    Novella::Rendering::Renderer renderer;

    Novella::Audio::AudioSystem audio;

    resources.loadTexture("test", "/home/line/projects/Novel/Test/test.png");

    auto& texture = *resources.getTexture("test");

    audio.createResource("test", "/home/line/projects/Novel/Test/bgm.ogg", Novella::Audio::AssetType::Music);

    audio.play("test");
    
    while(window.isOpen()){

        audio.update();
        
        window.beginFrame();
        
        window.clear(Novella::Graphics::Colors::Green);

        renderer.drawTexture(texture, 300, 300, Novella::Graphics::Colors::White);        

        window.endFrame();
    }

    return 0;
} 