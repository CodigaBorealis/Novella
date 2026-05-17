#include "Novella/Audio/AudioResource.hpp"
#include "Novella/Components/Background.hpp"
#include "Novella/Components/Button.hpp"
#include "Novella/Components/Character.hpp"
#include "Novella/Engine.hpp"
#include "Novella/Math/Vector2x.hpp"
#include "Novella/Window/WindowFlags.hpp"
#include "Novella/Components/Label.hpp"

int main(){

    Novella::Engine engine(1000, 1000, "test", 60, "/home/line/projects/Novel/Test/backgroundTest.png",Novella::WindowFlags::Resizable);

    engine.resources().loadTexture("character", "/home/line/projects/Novel/Test/test.png");

    engine.resources().loadTexture("background", "/home/line/projects/Novel/Test/backgroundTest.png");

    engine.resources().loadTexture("button", "/home/line/projects/Novel/Test/MainMenu.png");

    engine.resources().loadFont("font", "/home/line/projects/Novel/Test/font.otf");
    
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

    engine.scene().addObject<Novella::Components::Label>(

        "label",
        engine.resources().getFont("font"),
        Novella::Math::Vector2i{500, 500},
        25,
        "did you know that sometimes you may or you may not or you could or you"
    );

    auto button = engine.scene().addObject<Novella::Components::Button>(

        "button",
        engine.resources().getTexture("button"),
        Novella::Math::Vector2i{50,50},
        Novella::Math::Vector2i{300,300}

    );

    auto* label = engine.scene().getCurrentScene().getObjectAs<Novella::Components::Label>("label");
    
    label->setColor({100,0,100,255});
    
    engine.audio().createResource("audio", "/home/line/projects/Novel/Test/bgm.ogg", Novella::Audio::AssetType::Music);

    engine.audio().play("audio");

    engine.window().setTitle("hola");

    engine.run();

    return 0;
} 