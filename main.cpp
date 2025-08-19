#include <iostream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "game_parameters.hpp"
#include "game_system.hpp"
#include "pacman.hpp"
#include "system_renderer.hpp"

sf::Texture spritesheet;

int main(){
  sf::RenderWindow window(sf::VideoMode({game_width, game_height}), "SPACE Invaders");
  Renderer::initialise(window);
  GameSystem::Load();
	while(window.isOpen()){
    window.clear();
    GameSystem::Update(window);
    GameSystem::Render();
    //Wait for Vsync
    window.display();
  }
  GameSystem::Clean();
  return 0;
}
