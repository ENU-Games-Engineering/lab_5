#include "level_system.hpp"
#include <fstream>
#include <iostream>


std::unique_ptr<LevelSystem::TILE[]> LevelSystem::_tiles;
int LevelSystem::_width;
int LevelSystem::_height;
sf::Vector2f LevelSystem::_offset(0.0f, 0.0f);

float LevelSystem::_tileSize(100.f);
std::vector<std::unique_ptr<sf::RectangleShape>> LevelSystem::_sprites;

std::map<LevelSystem::TILE, sf::Color> LevelSystem::_colours{ {WALL, sf::Color::White}, {END, sf::Color::Red} };

int LevelSystem::getHeight(){return _height;}
int LevelSystem::getWidth(){return _width;}

sf::Color LevelSystem::getColor(LevelSystem::TILE t) {
  auto it = _colours.find(t);
  if (it == _colours.end()) {
    _colours[t] = sf::Color::Transparent;
  }
  return _colours[t];
}

void LevelSystem::setColor(LevelSystem::TILE t, sf::Color c) {
  _colours[t] = c;
}

void LevelSystem::loadLevelFile(const std::string& path, float tileSize) {
  _tileSize = tileSize;
  size_t w = 0, h = 0;
  std::string buffer;

  // Load in file to buffer
  std::ifstream f(path);
  if (f.good()) {
    f.seekg(0, std::ios::end);
    buffer.resize(f.tellg());
    f.seekg(0);
    f.read(&buffer[0], buffer.size());
    f.close();
  } else {
    throw std::string("Couldn't open level file: ") + path;
  }

  std::vector<TILE> temp_tiles;
  for (int i = 0; i < buffer.size(); ++i) {
    const char c = buffer[i];
    switch (c) {
    case 'w':
      temp_tiles.push_back(WALL);
      break;
    case 's':
      temp_tiles.push_back(START);
      break;
    case 'e':
      temp_tiles.push_back(END);
      break;
    case ' ':
      temp_tiles.push_back(EMPTY);
      break;
    case '+':
      temp_tiles.push_back(WAYPOINT);
      break;
    case 'n':
      temp_tiles.push_back(ENEMY);
      break;
    case '\n':      // end of line
      if (w == 0) { // if we haven't written width yet
        w = i;      // set width
      }
      h++; // increment height
      break;
    default:
      std::cout << c << std::endl; // Don't know what this tile type is
    }
  }
  if (temp_tiles.size() != (w * h)) {
    throw std::string("Can't parse level file") + path;
  }
  _tiles = std::make_unique<TILE[]>(w * h);
  _width = w; //set static class vars
  _height = h;
  std::copy(temp_tiles.begin(), temp_tiles.end(), &_tiles[0]);
  std::cout << "Level " << path << " Loaded. " << w << "x" << h << std::endl;
  buildSprites();
}

void LevelSystem::buildSprites() {
  _sprites.clear();
  for (size_t y = 0; y < LevelSystem::getHeight(); ++y) {
    for (size_t x = 0; x < LevelSystem::getWidth(); ++x) {
      std::unique_ptr<sf::RectangleShape> s = std::make_unique<sf::RectangleShape>();
      s->setPosition(getTilePosition({x, y}));
      s->setSize(sf::Vector2f(_tileSize, _tileSize));
      s->setFillColor(getColor(getTile({x, y})));
      _sprites.push_back(move(s));
    }
  }
}

sf::Vector2f LevelSystem::getTilePosition(sf::Vector2i p) {
  return (sf::Vector2f(p.x, p.y) * _tileSize);
}

LevelSystem::TILE LevelSystem::getTile(sf::Vector2i p) {
  if (p.x > _width || p.y > _height) {
    throw std::string("Tile out of range: ") + std::to_string(p.x) + "," + std::to_string(p.y) + ")";
  }
  return _tiles[(p.y * _width) + p.x];
}

LevelSystem::TILE LevelSystem::getTileAt(sf::Vector2f v) {
  auto a = v - _offset;
  if (a.x < 0 || a.y < 0) {
    throw std::string("Tile out of range ");
  }
  return getTile(sf::Vector2i((v - _offset) / (_tileSize)));
}

void LevelSystem::Render(sf::RenderWindow &window) {
  for (size_t i = 0; i < _width * _height; ++i) {
    window.draw(*_sprites[i]);
  }
}

