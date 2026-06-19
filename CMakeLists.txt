cmake_minimum_required(VERSION 4.2.3)

project(Novel LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(raylib 5.0 REQUIRED)


add_executable(Novella
    main.cpp
    
    src/Window.cpp
    
    src/Font.cpp
    src/Image.cpp
    src/Texture.cpp

    src/Renderer.cpp
    src/ResourceManager.cpp

    src/AudioBackend.cpp
    src/AudioSystem.cpp

    src/Scene.cpp
    src/SceneManager.cpp
    src/SceneWatcher.cpp
    
    src/Sprite.cpp
    src/Label.cpp
    src/Button.cpp
    
    src/LayoutSystem.cpp
    
    src/InputSystem.cpp
    src/InteractionSystem.cpp

    src/AudioCommands.cpp
    src/InputCommands.cpp
    src/SceneCommands.cpp
    src/TransformationCommands.cpp
    src/WindowCommands.cpp
    src/DebuggingCommands.cpp
    src/CommandTable.cpp

    src/FileReader.cpp

    src/SceneLoader.cpp
    src/ComponentBuilder.cpp
    src/InputBuilder.cpp

    src/Lexer.cpp
    src/Parser.cpp
    src/NLexer.cpp
    src/NParser.cpp

    src/Interpreter.cpp
    src/ScriptLoader.cpp
    src/ModuleResolver.cpp
    src/ExpressionEvaluator.cpp
    src/RuntimeEnvironment.cpp
    src/StatementEvaluator.cpp
    src/EventHandler.cpp
    src/Converter.cpp
    
    src/Engine.cpp
    
)

target_link_libraries(Novella
    PRIVATE
        raylib
)

target_include_directories(Novella
    PRIVATE
        ${CMAKE_SOURCE_DIR}/Include
)