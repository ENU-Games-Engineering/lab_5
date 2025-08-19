#include <cmath>
#include "pacman.hpp"
#include "game_parameters.hpp"
#include "components.hpp"
#include "system_renderer.hpp"
#include "level_system.hpp"

using ls = LevelSystem;

void MenuScene::update(double dt) {
  Scene::update(dt);
  _text.setString("Almost Pacman");
}

void MenuScene::render() {
  Renderer::queue(&_text);
  Scene::render();
}

void MenuScene::load() {
  _font.loadFromFile("/home/leni/git/set09121_labs/lab_5/resources/fonts/RobotoMono-Regular.ttf");
  _text.setFont(_font);
  _text.setCharacterSize(60);
}


void GameScene::update(double dt){

    auto vect_distance = [](sf::Vector2f a,sf::Vector2f b) -> float{
      return sqrt((a.x - b.x)*(a.x - b.x) + (a.y - b.y)*(a.y - b.y));
    };
    for (size_t i = 1; i < _ents.list.size(); i++) {
      if (vect_distance(_ents.list[i]->get_position(), _player->get_position()) < 30.0f) {
        respawn();
      }
    }
    Scene::update(dt);
    _nibbles.update(dt);
}

void GameScene::render(){
  ls::Render(Renderer::getWindow());
  Scene::render();
  _ents.render();
  _nibbles.render();

}

void GameScene::load() {

  ls::loadLevelFile("/home/leni/git/set09121_labs/lab_5/resources/levels/pacman.txt",tile_size);

  {
    std::shared_ptr<Entity> player = std::make_shared<Entity>();
    std::shared_ptr<ShapeComponent> shape = player->add_component<ShapeComponent>();
    shape->set_shape<sf::CircleShape>(entity_size);
    shape->get_shape().setFillColor(sf::Color::Yellow);
    shape->get_shape().setOrigin(sf::Vector2f(entity_size, entity_size));  

    player->add_component<PlayerMovementComponent>();
    player->set_position(ls::getStartPosition());
    _ents.list.push_back(player);
    _player = _ents.list.back();
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
    ghost->add_component<EnemyAIComponent>();

    _ents.list.push_back(ghost);
  }
  respawn();
}

void GameScene::respawn() {
 _player->set_position(ls::getStartPosition());
 _player->get_compatible_components<ActorMovementComponent>()[0]
            ->set_speed(player_speed);

 std::vector<sf::Vector2i> ghost_spawns = ls::findTiles(ls::ENEMY);
 for (size_t i = 1; i < _ents.list.size(); i++) {
    std::shared_ptr<Entity> &ghost = _ents.list[i];
    ghost->set_position(
        ls::getTilePosition(ghost_spawns[rand() % ghost_spawns.size()]));
    ghost->get_compatible_components<ActorMovementComponent>()[0]->set_speed(ghost_speed);
 }
 
  //clear any remaining nibbles
  for (auto n : _nibbles.list) {
    n->set_for_delete();
    n.reset();
  }
  _nibbles.list.clear();

    //white nibbles
  auto nibbleLoc = LevelSystem::findTiles(LevelSystem::EMPTY);
  for (const auto& nl : nibbleLoc) {
    auto cherry = make_nibble(nl, false);
    //add to _wnts and nibbles list
    _nibbles.list.push_back(cherry);
  }
  //blue nibbles
  nibbleLoc = LevelSystem::findTiles(LevelSystem::WAYPOINT);
  for (const auto& nl : nibbleLoc) {
    auto cherry = make_nibble(nl, true);
    _nibbles.list.push_back(cherry);
  }
}

std::shared_ptr<Entity> GameScene::make_nibble(const sf::Vector2i& pos, bool big) {
  std::shared_ptr<Entity> cherry = std::make_shared<Entity>();
  std::shared_ptr<ShapeComponent> s = cherry->add_component<ShapeComponent>();
  //set colour
  if(big){
    s->set_shape<sf::CircleShape>(big_nibble_size);
    s->get_shape().setFillColor(sf::Color::Blue);
    s->get_shape().setOrigin(big_nibble_size,big_nibble_size);
  }else{
    s->set_shape<sf::CircleShape>(small_nibble_size);
    s->get_shape().setFillColor(sf::Color::White);
    s->get_shape().setOrigin(small_nibble_size,small_nibble_size);
  }
  
  cherry->add_component<PickupComponent>(big);
  cherry->set_position(ls::getTilePosition(pos) + sf::Vector2f(10.f, 10.f));
  return cherry;
}