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
    src/SoundRegistry.cpp

    src/Scene.cpp
    src/SceneManager.cpp
    src/SceneBuilder.cpp
    src/ObjectFactory.cpp

    src/JsonSerializer.cpp
    src/JsonValidator.cpp

    src/Character.cpp
    src/Background.cpp
    src/Label.cpp
    src/Button.cpp
    
    src/LayoutSystem.cpp
    
    src/InputSystem.cpp
    src/InteractionSystem.cpp
    src/CommandDispatcher.cpp

    
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