#include "SFML/Graphics/Sprite.hpp"
#include "SFML/System/Vector2.hpp"

#define TILE_SIZE 18
#define SELECTION_ALPHA 0.5

class TilePlacer {
private:
  sf::Sprite tile;
  int rotation;

  void resetOrigin();

public:
  void setActive(sf::Sprite);

  void rotateClockwise();
  void rotateCounterClockwise();
  float getRotation();

  void mirror();
  bool isMirror();

  void setPosition(sf::Vector2f);
  sf::Vector2f getPosition();

  sf::Sprite getSprite();
};
