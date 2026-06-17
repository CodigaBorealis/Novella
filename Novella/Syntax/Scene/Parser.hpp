#pragma once
#include "SceneDefinition.hpp"
#include "Token.hpp"
#include <cstddef>
#include <unordered_map>
#include <vector>

namespace Novella::Syntax::Scene{

    class Lexer;

    struct SceneDefinition;

    struct ObjectDefinition;

    struct Property;

    struct Value;

    class Parser{

        public:
        
        explicit Parser(Lexer& lexer);

        SceneDefinition parse();

        private:

        enum class Section : unsigned short{
                
                Window,
                Resources,
                Components,
                Scripts,
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
                    case Section::Resources: return "Resources";
                    case Section::Components: return "Components";
                    case Section::Scripts: return "Scripts";

                    default: return "Unknown";

                }
            }

            static constexpr Section stringToSection(const std::string& section){

                if(section == "Window") return Section::Window;
                if(section == "Resources") return Section::Resources;
                if(section == "Components") return Section::Components;
                if(section == "Scripts") return Section::Scripts;

                return Section::Unknown;

            }
        };

        std::vector<Token> tokens;
        size_t position = 0;
        //Could be a vector but this is better for readability
        std::unordered_map<Section, ParseRegistry> parseRegistry{

            {Section::Window, ParseRegistry{false}},
            {Section::Resources, ParseRegistry{false}},
            {Section::Components, ParseRegistry{false}},
            {Section::Scripts, ParseRegistry{true}}


        };

        Token& current();
        Token& peek(size_t offset);

        void consume();
        void expect(Token::Type type);

        void parseResources(SceneDefinition& scene);
        void parseWindow(SceneDefinition& scene);
        void parseComponents(SceneDefinition& scene);
        void parseScripts(SceneDefinition& scene);

        void registerSeenSection(const std::string& section);

        SceneDefinition parseScene();
        ObjectDefinition parseObject();
        Property parseProperty();
        Value parseValue();

        void checkIntegrity(const std::unordered_map<Section, ParseRegistry>& parseRegistry);
    };

}