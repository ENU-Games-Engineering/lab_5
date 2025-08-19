#pragma once
#include <memory>
#include "scene.hpp"

struct Scenes{
  static std::shared_ptr<Scene> game;
  static std::shared_ptr<Scene> menu;
  static std::shared_ptr<Scene> active;
};

class MenuScene : public Scene {
private:
  sf::Text text;
  sf::Font font;

public:
  MenuScene() = default;
  void update(double dt) override;
  void render() override;
  void load()override;
};

class GameScene : public Scene {
private:
  sf::Text text;
  sf::Clock scoreClock;
  void respawn();

public:
  GameScene() = default;
  void update(double dt) override;
  void render() override;
  void load() override;
};