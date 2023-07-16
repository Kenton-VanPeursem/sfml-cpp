#pragma once

#include "SFML/Graphics/Texture.hpp"
#include "SFML/Graphics/Sprite.hpp"

class TileFactory {
private:
  sf::Texture texture;
  int size;

public:
  TileFactory(sf::Texture, int);
  ~TileFactory();
  sf::Sprite getTile(int, int);
  sf::Sprite getTile(int);
};
