#pragma once

namespace Novella::Input::Target{

    static constexpr const char* SELF = "@SELF";

    static constexpr const char* ALL = "@ALL";//Dont use this unless you are sure all objects in the scene
    //Support the command you want to use i.e changing the sprite moving the object applying a colorMask etc.

    //targets all components of an specific type on the scene
    //will crash if you try and use a command that is not supported by the specified type
    //dont do that.
    
    static constexpr const char* ALL_BACKGROUNDS = "@COMPONENT:BACKGROUND";

    static constexpr const char* ALL_BUTTONS = "@COMPONENT:BUTTON";

    static constexpr const char* ALL_CHARACTERS = "@COMPONENT:CHARACTER";

    static constexpr const char* ALL_DIALOGUE_BOXES = "@COMPONENT:DIALOGUEBOX";

    static constexpr const char* ALL_LABELS = "@COMPONENT:LABEL";

    static constexpr const char* ALL_MENUS = "@COMPONENT:LABEL";

}