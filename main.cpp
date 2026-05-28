#include "Novella/Audio/AudioResource.hpp"
#include "Novella/Components/Background.hpp"
#include "Novella/Components/Button.hpp"
#include "Novella/Components/Character.hpp"
#include "Novella/Engine.hpp"
#include "Novella/Input/ActionCommand.hpp"
#include "Novella/Input/Target.hpp"
#include "Novella/Layout/Anchor.hpp"
#include "Novella/Layout/SizeMode.hpp"
#include "Novella/Layout/Layout.hpp"
#include "Novella/Window/WindowFlags.hpp"
#include "Novella/Components/Label.hpp"
#include "Novella/Input/Mouse.hpp"

int main(){

    Novella::Engine engine(1920, 1200, "test", 60, "/home/line/projects/Novel/Test/MainMenu.png",Novella::WindowFlags::Resizable);

    engine.resources().loadTexture("character", "/home/line/projects/Novel/Test/character_1.png");

    engine.resources().loadTexture("button", "/home/line/projects/Novel/Test/dialogueBG.png");

    engine.resources().loadTexture("background", "/home/line/projects/Novel/Test/backgroundTest.png");

    engine.resources().loadTexture("button2", "/home/line/projects/Novel/Test/backgroundTest2.png");

    engine.resources().loadFont("font", "/home/line/projects/Novel/Test/font.otf");
    
    engine.scene().createScene();

    auto& bg= engine.scene().addObject<Novella::Components::Background>(

        "background",
        engine.resources().getTexture("background"),
        Novella::Layout{            
            .anchor = Novella::Anchor::TopLeft,
            .widthMode = Novella::SizeMode::FitWidth,
            .heightMode = Novella::SizeMode::FitHeight
        },
        -12        

    );

    auto& c = engine.scene().addObject<Novella::Components::Character>(

        "character",
        engine.resources().getTexture("character"),
        Novella::Layout{}

    );
    
    c.setRenderLayer(-1000);

    engine.scene().addObject<Novella::Components::Label>(

        "label",
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

        "button",
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

    button.addMouseBind(Novella::Input::Mouse::Button::Left, Novella::Input::ActionCommand{"test", nlohmann::json(), Novella::Input::Target::self});

    auto* label = engine.scene().getCurrentScene().getObjectAs<Novella::Components::Label>("label");
    
    label->setColor({100,0,100,255});
    
    engine.audio().createResource("audio", "/home/line/projects/Novel/Test/bgm.ogg", Novella::Audio::AssetType::Music);

    engine.audio().play("audio");

    engine.window().setTitle("hola");

    engine.run();

    return 0;
} 

