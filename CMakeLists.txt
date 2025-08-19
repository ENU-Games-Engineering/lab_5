project(pacman)
cmake_minimum_required(VERSION 3.11)
# Require modern C++
set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#### Setup Directories ####
#Main output directory
SET(OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin/")
# Ouput all DLLs from all libs into main build folder
SET(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_DIRECTORY})

#### Add External Dependencies ####
add_subdirectory("lib/SFML")
set(SFML_INCS "lib/SFML/include")
link_directories("${CMAKE_BINARY_DIR}/lib/SFML/lib")


#### level system ####
add_library(tile_level SHARED tile_level_loader/level_system.cpp)
target_include_directories(tile_level INTERFACE tile_level_loader)
target_link_libraries(tile_level sfml-graphics)

#### executable ####
add_executable(pacman 
    main.cpp 
    game_system.cpp
    components.cpp
    ecm.cpp
    pacman.cpp
    system_renderer.cpp
    scene.cpp)
target_include_directories(pacman PRIVATE ${SFML_INCS} tile_level_loader)
target_link_libraries(pacman sfml-graphics tile_level)
