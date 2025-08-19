#pragma once
#include <memory>
#include "scene.hpp"



class MenuScene : public Scene {
private:
  sf::Text _text;
  sf::Font _font;

public:
  MenuScene() = default;
  void update(double dt) override;
  void render() override;
  void load()override;
};

class GameScene : public Scene {
private:
  sf::Text _text;
  sf::Clock _score_clock;
  std::shared_ptr<Entity> _player;
  EntityManager _nibbles;
  std::shared_ptr<Entity> make_nibble(const sf::Vector2i& pos, bool big);
  void respawn();

public:
  GameScene() = default;
  void update(double dt) override;
  void render() override;
  void load() override;
};