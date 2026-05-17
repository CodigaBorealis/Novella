#include "Novella/Audio/AudioResource.hpp"
#include "Novella/Components/Character.hpp"
#include "Novella/Engine.hpp"
#include "Novella/Math/Vector2x.hpp"

int main(){

    Novella::Engine engine(1000, 1000, "test", 60);

    engine.resources().loadTexture("character", "/home/line/projects/Novel/Test/test.png");

    engine.scene().createScene();

    engine.scene().addObject<Novella::Components::Character>(

        "character",
        engine.resources().getTexture("character"),
        Novella::Math::Vector2i{500, 500}

    );
    
    engine.audio().createResource("audio", "/home/line/projects/Novel/Test/bgm.ogg", Novella::Audio::AssetType::Music);

    engine.audio().play("audio");

    engine.run();

    return 0;
} 