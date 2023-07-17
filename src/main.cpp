#include "SFML/Graphics.hpp"
#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/Graphics/Sprite.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/ContextSettings.hpp"
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "tilefactory.h"

#define TILE_MAP "assets/tiles_packed.png"
#define TILE_SIZE 18
#define HALF_TILE_SIZE 9
#define WINDOW_WIDTH_TILES 30
#define WINDOW_HEIGHT_TILES 20
#define SELECTION_PADDING 6
#define SELECTION_ALPHA 0.75

void resetOrigin(sf::Sprite *sprite, int rotation) {
  switch (rotation) {
  case 0:
    sprite->setOrigin(sf::Vector2f(0.f, 0.f));
    break;
  case 1:
    sprite->setOrigin(sf::Vector2f(0.f, TILE_SIZE));
    break;
  case 2:
    sprite->setOrigin(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    break;
  case 3:
    sprite->setOrigin(sf::Vector2f(TILE_SIZE, 0.f));
    break;
  default:
    break;
  }
}

int main() {
  sf::Texture texture;
  if (!texture.loadFromFile(TILE_MAP)) {
    std::cout << "Failed to load texture from " << TILE_MAP << std::endl;
    return EXIT_FAILURE;
  }

  sf::Vector2u mapSize = sf::Vector2u(TILE_SIZE * WINDOW_WIDTH_TILES,
                                      TILE_SIZE * WINDOW_HEIGHT_TILES);
  size_t width, height;
  if (mapSize.y < texture.getSize().y) {
    height = texture.getSize().y;
  } else {
    height = mapSize.y;
  }
  width = TILE_SIZE * WINDOW_WIDTH_TILES + texture.getSize().x;


  // Window setup -------------------------------------------------------------
  sf::ContextSettings contextSettings;
  contextSettings.antialiasingLevel = 8;
  sf::RenderWindow window(sf::VideoMode(width, height), "My Window",
                          sf::Style::Default, contextSettings);
  window.setFramerateLimit(60);
  //---------------------------------------------------------------------------

  sf::Sprite selectionArea(texture);
  // center the selection area vertically
  float selectionAreaPadding = float(height - texture.getSize().y) / 2;
  selectionArea.setPosition(0.f, selectionAreaPadding);

  sf::RectangleShape selectionBackground;
  selectionBackground.setSize(sf::Vector2f(texture.getSize().x, height));
  selectionBackground.setFillColor(sf::Color(58, 65, 83, 200));

  TileFactory tileFactory(texture, TILE_SIZE);

  std::vector<int> pos{0, 4, 8, 88};

  sf::Sprite pointer = sf::Sprite(tileFactory.getTile(0));
  pointer.setColor(sf::Color(255, 255, 255, SELECTION_ALPHA * 255));
  int rotation = 0;

  std::vector<sf::Sprite> placedTiles;
  sf::Color clearColor = sf::Color::White;

  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        std::cout << "Direct: Escape key is pressed" << std::endl;
        window.close();
      }

      if (event.type == sf::Event::Closed) {
        window.close();
      }

      // handle mouse clicks
      if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          // check if mouse is in the selectable area
          sf::Vector2f mousePosition(event.mouseButton.x, event.mouseButton.y);
          bool selectableAreaClicked =
              selectionArea.getGlobalBounds().contains(mousePosition);

          if (selectableAreaClicked) {
            int tileX = int(mousePosition.x) / TILE_SIZE;
            int tileY = int(mousePosition.y - selectionAreaPadding) / TILE_SIZE;
            pointer = tileFactory.getTile(tileX, tileY);
            pointer.setColor(sf::Color(255, 255, 255, SELECTION_ALPHA * 255));
            rotation = 0; // reset rotation
          } else if (!selectionBackground.getGlobalBounds().contains(
                         mousePosition)) {
            sf::Sprite csprite(pointer);
            sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
            // get the nearest position to put the csprite on a grid
            int x = mousePosition.x - (mousePosition.x % TILE_SIZE);
            int y = mousePosition.y - (mousePosition.y % TILE_SIZE);
            csprite.setPosition(sf::Vector2f(x, y));
            csprite.setColor(sf::Color::White);
            placedTiles.push_back(csprite);
          }
        } else if (event.mouseButton.button == sf::Mouse::Right &&
                   placedTiles.size() > 0) {
          // check if mouse is over a placed tile and delete that tile from the
          // vector
          for (size_t i = 0; i < placedTiles.size(); i++) {
            sf::FloatRect bounds = placedTiles[i].getGlobalBounds();
            if (bounds.contains(
                    sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
              placedTiles.erase(placedTiles.begin() + i);
              break;
            }
          }
        }
      }

      // pointer updates with mouse movement
      if (event.type == sf::Event::MouseMoved) {
        // get the nearest position to put the sprite on a grid
        int x = event.mouseMove.x - (event.mouseMove.x % TILE_SIZE);
        int y = event.mouseMove.y - (event.mouseMove.y % TILE_SIZE);
        sf::Vector2f pos(x, y);
        pointer.setRotation(rotation * 90);
        resetOrigin(&pointer, rotation);
        pointer.setPosition(pos);
      }

      if (event.type == sf::Event::KeyPressed) {
        if (event.key.code == sf::Keyboard::R) {
          rotation = (rotation + 1) % 4;
          sf::Vector2f pos(pointer.getPosition());
          pointer.setRotation(rotation * 90);
          resetOrigin(&pointer, rotation);
          pointer.setPosition(pos);
        }
      }
    }

    window.clear(clearColor);

    for (size_t i = 0; i < placedTiles.size(); i++) {
      window.draw(placedTiles[i]);
    }

    window.draw(pointer);

    // UI is drawn last
    window.draw(selectionBackground);
    window.draw(selectionArea);

    window.display();
  }
  return 0;
}
