#pragma once

namespace Novella::Traits{

    struct Updatable{

        virtual void update(float dt) = 0;
    };

}