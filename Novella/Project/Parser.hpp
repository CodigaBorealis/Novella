#pragma once
#include <cstddef>
#include <unordered_map>
#include <unordered_set>
#include <variant>
#include <vector>
#include "Token.hpp"
#include "../Windowing/WindowFlags.hpp"

namespace Novella{

    struct EngineConfig;

}

namespace Novella::Project{
    
    using ValueData = std::variant<std::string, int>;

    struct Value{

        ValueData data;

        bool isInt() const{return std::holds_alternative<int>(data);}
        bool isString() const{return std::holds_alternative<std::string>(data);}

        template<typename T>

        const T& as() const{

            return std::get<T>(data);
        }

        template<typename T>

        T& as(){

            return std::get<T>(data);
        }
    };

    enum class Section : unsigned short{

        Window,
        Scenes,
        Unknown
    };

    struct ParseRegistry{

        ParseRegistry() = delete;

        explicit ParseRegistry(bool optional)
            :
            optional(optional)
            {}

        int firstDefinitionIndex = -1;

        unsigned int evalCount = 0;

        bool optional;            
            
        static constexpr std::string sectionToString(Section section){

            switch(section){

                case Section::Window: return "Window";

                default: return "Unknown";

            }
        }

        static constexpr Section stringToSection(const std::string& section){

            if(section == "Window") return Section::Window;
            
            if(section == "Scenes") return Section::Scenes;

            return Section::Unknown;

        }
    };
        
    class Lexer;

    class Parser{

        public:

        explicit Parser(Lexer& lexer);

        EngineConfig parse();

        void parseWindow(EngineConfig& config);
        
        void parseScenes(EngineConfig& config);

        void parseFlags(EngineConfig& config);

        void parseWindowProperty(EngineConfig& config);
        
        private:
        
        void registerSeenSection(const std::string& section);
        std::vector<Token> tokens;
        size_t position = 0;

        Token& current();
        Token& peek(size_t offset);
        
        void consume();
        void expect(Token::Type type);
        
        Value parseValue();

        std::unordered_map<Section, ParseRegistry> parseRegistry{

            {Section::Window, ParseRegistry{false}},
            {Section::Scenes, ParseRegistry{false}}
        };

        std::unordered_set<std::string> seenProperties;

        const std::unordered_map<std::string, WindowFlags> optionalFlags{

            {"fullscreen", WindowFlags::Fullscreen},
            {"resizable", WindowFlags::Resizable},
            {"undecorated", WindowFlags::Undecorated},
            {"hidden", WindowFlags::Hidden},
            {"minimized", WindowFlags::Minimized},
            {"maximized", WindowFlags::Maximized},
            {"unfocused", WindowFlags::Unfocused},
            {"topmost", WindowFlags::Topmost},
            {"alwaysrun", WindowFlags::AlwaysRun},
            {"transparent", WindowFlags::Transparent},
            {"highDPI", WindowFlags::HighDPI},
            {"vsync", WindowFlags::VSync},
            {"MSAA4X", WindowFlags::MSAA4X},
            {"interlaced", WindowFlags::Interlaced}
        };

    };  
}