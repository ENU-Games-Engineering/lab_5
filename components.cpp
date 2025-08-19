#include "components.hpp"
#include "level_system.hpp"
#include "system_renderer.hpp"

using ls = LevelSystem;

void ShapeComponent::update(double dt) {
  _shape->setPosition(_parent->get_position());
}

void ShapeComponent::render() { Renderer::queue(_shape.get()); }

sf::Shape& ShapeComponent::get_shape() const { return *_shape; }

ShapeComponent::ShapeComponent(Entity* p) : Component(p), _shape(std::make_shared<sf::CircleShape>()) {}



using namespace sf;

void ActorMovementComponent::update(double dt) {}

ActorMovementComponent::ActorMovementComponent(Entity* p)
    : _speed(100.0f), Component(p) {}

bool ActorMovementComponent::valid_move(const sf::Vector2f& pos) {
  return (ls::getTileAt(pos) != ls::WALL);
}

void ActorMovementComponent::move(const sf::Vector2f& p) {
  sf::Vector2f new_pos = _parent->get_position() + p;
  if (valid_move(new_pos)) {
    _parent->set_position(new_pos);
  }
}

void ActorMovementComponent::move(float x, float y) {
  move(Vector2f(x, y));
}
float ActorMovementComponent::get_speed() const { return _speed; }
void ActorMovementComponent::set_speed(float speed) { _speed = speed; }

PlayerMovementComponent::PlayerMovementComponent(Entity* p)
	: ActorMovementComponent(p) {}

void PlayerMovementComponent::update(double dt){
  sf::Vector2f new_pos(_parent->get_position().x,_parent->get_position().y);
  
  //Move up
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    move(0,-_speed*dt);
  
  //Move down
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    move(0,_speed*dt);
  
  //Move left
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    move(-_speed*dt,0);

  //Move Right
  if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    move(_speed*dt,0);

}