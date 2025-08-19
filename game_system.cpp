#include <iostream>
#include "game_system.hpp"
#include "game_parameters.hpp"
#include "level_system.hpp"
#include "pacman.hpp"
#include "system_renderer.hpp"

using sc = Scenes;

void GameSystem::Load() {
  // Load Scene-Local Assets
  sc::game.reset(new GameScene());
  sc::menu.reset(new MenuScene());
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
  sc::active->update(dt);

}

void GameSystem::Render(){
  sc::active->render();
  Renderer::render();
}
