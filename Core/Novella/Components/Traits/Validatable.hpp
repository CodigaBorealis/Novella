#pragma once

namespace Novella::Traits{

    struct Validatable{

        virtual void validate() const = 0;
    };

}