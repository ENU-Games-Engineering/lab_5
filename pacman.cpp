#include "pacman.hpp"
#include "game_parameters.hpp"
#include "components.hpp"
#include "system_renderer.hpp"

using sc = Scenes;

std::shared_ptr<Scene> sc::game;
std::shared_ptr<Scene> sc::menu;
std::shared_ptr<Scene> sc::active;

void MenuScene::update(double dt) {
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    sc::active = sc::game;
  }
  Scene::update(dt);
  text.setString("Almost Pacman");
}

void MenuScene::render() {
  Renderer::queue(&text);
  Scene::render();
}

void MenuScene::load() {
  font.loadFromFile("resources/fonts/RobotoMono-Regular.ttf");
  text.setFont(font);
  text.setCharacterSize(60);
}

void GameScene::update(double dt){
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Tab)) {
        sc::active = sc::menu;
    }
    Scene::update(dt);
}

void GameScene::render(){
  Scene::render();
  _ents.render();

}

void GameScene::load() {
  {
    std::shared_ptr<Entity> player = std::make_shared<Entity>();
    std::shared_ptr<ShapeComponent> shape = player->add_component<ShapeComponent>();
    shape->set_shape<sf::CircleShape>(entity_size);
    shape->get_shape().setFillColor(sf::Color::Yellow);
    shape->get_shape().setOrigin(sf::Vector2f(entity_size, entity_size));  

    std::shared_ptr<PlayerMovementComponent> comp = 
      player->add_component<PlayerMovementComponent>();
    comp->set_speed(player_speed);

    _ents.list.push_back(player);
  }

  const sf::Color ghost_cols[]{{208, 62, 25},    // red Blinky
                               {219, 133, 28},   // orange Clyde
                               {70, 191, 238},   // cyan Inky
                               {234, 130, 229}}; // pink Pinky

  for(int i = 0; i < number_ghosts; i++){
    std::shared_ptr<Entity> ghost = std::make_shared<Entity>();
    std::shared_ptr<ShapeComponent> shape = ghost->add_component<ShapeComponent>();
    shape->set_shape<sf::CircleShape>(entity_size);
    shape->get_shape().setFillColor(ghost_cols[i % number_ghosts]);
    shape->get_shape().setOrigin(sf::Vector2f(entity_size, entity_size));

    _ents.list.push_back(ghost);
  }
}
