#include <iostream>
#include "game_system.hpp"
#include "game_parameters.hpp"
#include "level_system.hpp"
#include "pacman.hpp"
#include "system_renderer.hpp"

using sc = Scenes;
using ls = LevelSystem;
std::shared_ptr<Scene> sc::game;
std::shared_ptr<Scene> sc::menu;
std::shared_ptr<Scene> sc::active;

void GameSystem::Load() {
  // Load Scene-Local Assets
  sc::game = std::make_unique<GameScene>();
  sc::menu = std::make_unique<MenuScene>();
  sc::game->load();
  sc::menu->load();
  // Start at main menu
  sc::active = sc::menu;
}

void GameSystem::Clean(){
  sc::game.reset();
  sc::menu.reset();
}

void GameSystem::Update(sf::RenderWindow &window){
  static sf::Clock clock;
  float dt = clock.restart().asSeconds();
  sf::Event event;
  while (window.pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
        window.close();
        return;
    }
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
    sc::active = sc::menu;
  }
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    sc::active = sc::game;
  }
  sc::active->update(dt);

}

void GameSystem::Render(sf::RenderWindow &window){
  sc::active->render();
  Renderer::render();
}
