#pragma once
#include <vector>
#include <SFML/Graphics.hpp>
#include "scene.hpp"
#include "pacman.hpp"

struct Scenes{
  static std::shared_ptr<Scene> game;
  static std::shared_ptr<Scene> menu;
  static std::shared_ptr<Scene> active;
};

struct GameSystem{
    static void Load();
    static void Clean();
    static void Update(sf::RenderWindow &window);
    static void Render(sf::RenderWindow &window);
};