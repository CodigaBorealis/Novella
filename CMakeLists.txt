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

    
)

target_link_libraries(Novella
    PRIVATE
        raylib
)

target_include_directories(Novella
    PRIVATE
        ${CMAKE_SOURCE_DIR}/Include
)