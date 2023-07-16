#include "tilefactory.h"

TileFactory::TileFactory(sf::Texture texture, int size) {
  this->texture = texture;
  this->size = size;
}

TileFactory::~TileFactory() {}

sf::Sprite TileFactory::getTile(int x, int y) {
  return sf::Sprite(this->texture, sf::IntRect(size * x, size * y, size, size));
}

sf::Sprite TileFactory::getTile(int num) {
  int width = texture.getSize().x / size;
  int x = num % width;
  int y = num / width;
  return getTile(x, y);
}

