#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "scene.hpp"
#include "pacman.hpp"


struct GameSystem{
    static void Load();
    static void Clean();
    static void Update(sf::RenderWindow &window);
    static void Render(sf::RenderWindow &window);
};