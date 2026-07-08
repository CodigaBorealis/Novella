#include "../Novella/Scripting/API/TextModule.hpp"

namespace Novella::NScript::Modules::Text {

    void setText(Runtime::Context& context, Handle handle, const std::string& text){


    }
    
    std::string getText(Runtime::Context& context, Handle handle){

        return "";
    }
    
    void setFont(Runtime::Context& context, Handle handle, const std::string& name){


    }
    
    void setFontSize(Runtime::Context& context, Handle handle, double size){


    }
    
    void setFontColor(Runtime::Context& context, Handle handle, double r, double g, double b, double a){


    }
    
    std::string getFont(Runtime::Context& context, Handle handle){

        return "";
    }
    
    double getFontSize(Runtime::Context& context, Handle handle){

        return 0;
    }
    
}