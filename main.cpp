#include "Novella/Audio/AudioResource.hpp"
#include "Novella/Components/Background.hpp"
#include "Novella/Components/Button.hpp"
#include "Novella/Components/Character.hpp"
#include "Novella/Engine.hpp"
#include "Novella/Layout/Anchor.hpp"
#include "Novella/Layout/SizeMode.hpp"
#include "Novella/Layout/Layout.hpp"
#include "Novella/Window/WindowFlags.hpp"
#include "Novella/Components/Label.hpp"
#include "Novella/Input/Mouse.hpp"
#include "Novella/Commands/Alias.hpp"
#include <iostream>

int main(){

    Novella::Engine engine(1920, 1200, "test", 60, "/home/line/projects/Novella/Test/2026-05-27_17-52.png",Novella::WindowFlags::Resizable);

    engine.resources().loadTexture("character", "/home/line/projects/Novella/Test/2026-05-27_17-52.png");

    engine.resources().loadTexture("button", "/home/line/projects/Novella/Test/2026-05-27_18-51.png");

    engine.resources().loadTexture("background", "/home/line/projects/Novella/Test/2026-05-27_18-59.png");

    engine.resources().loadTexture("button2", "/home/line/projects/Novella/Test/135284394.png");

    engine.resources().loadFont("font", "/home/line/projects/Novella/Test/test.ttf");
    
    engine.scene().createScene();

    auto& bg= engine.scene().addObject<Novella::Components::Background>(

        engine.resources().getTexture("background"),
        Novella::Layout{            
            .anchor = Novella::Anchor::TopLeft,
            .widthMode = Novella::SizeMode::FitWidth,
            .heightMode = Novella::SizeMode::FitHeight
        },
        -12        

    );

    auto& c = engine.scene().addObject<Novella::Components::Character>(

        engine.resources().getTexture("character"),
        Novella::Layout{}

    );
    
    c.setRenderLayer(-1000);

    engine.scene().addObject<Novella::Components::Label>(

        engine.resources().getFont("font"),
        50,
        "did you know that sometimes you may or you may not or you could or you",
        Novella::Layout{
            .anchor = Novella::Anchor::Center,
            .offset = {10, 23}
        },
        1000
    );
//Label breaks if you use the constructor with the render label somehow
    auto& button = engine.scene().addObject<Novella::Components::Button>(

        engine.resources().getTexture("button"),
        Novella::Layout{
            .anchor = Novella::Anchor::Center,
            .widthMode = Novella::SizeMode::Fixed,
            .heightMode = Novella::SizeMode::Fixed,
            .width = 500,
            .height = 1000,
            .offset = {10, 20}
        },200

    );
    
    button.setRenderLayer(22);

    std::cout << button.getID();

    //auto* label = engine.scene().getCurrentScene().getObjectAs<Novella::Components::Label>(0);
    
    //label->setColor({100,0,100,255});
    
    engine.audio().createResource("audio", "/home/line/projects/Novella/Test/bgm.ogg", Novella::Audio::AssetType::Music);

    engine.audio().play("audio");

    engine.window().setTitle("hola");

    engine.run();

    return 0;
} 

