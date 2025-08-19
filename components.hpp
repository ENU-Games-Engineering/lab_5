#pragma once
#include "ecm.hpp"

class ShapeComponent : public Component {
protected:
  std::shared_ptr<sf::Shape> _shape;
public:
  ShapeComponent() = delete;
  explicit ShapeComponent(Entity *p);

  void update(double dt) override;
  void render() override;

  sf::Shape &get_shape() const;

  template <typename T, typename... Targs>
  void set_shape(Targs... params) {
    _shape.reset(new T(params...));
  }
};

class ActorMovementComponent : public Component {
protected:
  bool valid_move(const sf::Vector2f&);
  float _speed;

public:
  explicit ActorMovementComponent(Entity* p);
  ActorMovementComponent() = delete;

  float get_speed() const;
  void set_speed(float _speed);

  void move(const sf::Vector2f&);
  void move(float x, float y);

  void render() override {}
  void update(double dt) override;
};

class PlayerMovementComponent : public ActorMovementComponent{
public:
  PlayerMovementComponent() = delete;
  PlayerMovementComponent(Entity* p);

  void update(double dt) override;
};

class EnemyAIComponent : public ActorMovementComponent {
protected:  
  static const sf::Vector2i directions[];
  sf::Vector2f _direction;
  enum state {ROAMING, ROTATING, ROTATED };
  state _state = ROAMING;
public:
  EnemyAIComponent() = delete;
  EnemyAIComponent(Entity* p);
  void update(double dt) override;
};

class PickupComponent : public Component {
protected:
  bool _big;

public:
  explicit PickupComponent(Entity* p, bool big);
  PickupComponent() = delete;

  void render() override {}
  void update(double dt) override;
};