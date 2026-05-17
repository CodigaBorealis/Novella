#include "Novella/Audio/AudioResource.hpp"
#include "Novella/Components/Background.hpp"
#include "Novella/Components/Character.hpp"
#include "Novella/Engine.hpp"
#include "Novella/Math/Vector2x.hpp"
#include "Novella/Window/WindowFlags.hpp"

int main(){

    Novella::Engine engine(1000, 1000, "test", 60, "/home/line/projects/Novel/Test/backgroundTest.png",Novella::WindowFlags::Resizable);

    engine.resources().loadTexture("character", "/home/line/projects/Novel/Test/test.png");

    engine.resources().loadTexture("background", "/home/line/projects/Novel/Test/backgroundTest.png");

    engine.scene().createScene();

    engine.scene().addObject<Novella::Components::Background>(

        "background",
        engine.resources().getTexture("background")

    );

    engine.scene().addObject<Novella::Components::Character>(

        "character",
        engine.resources().getTexture("character"),
        Novella::Math::Vector2i{500, 500}

    );
    
    engine.audio().createResource("audio", "/home/line/projects/Novel/Test/bgm.ogg", Novella::Audio::AssetType::Music);

    engine.audio().play("audio");

    engine.window().setTitle("hola");

    engine.run();

    return 0;
} 