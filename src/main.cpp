#include "SFML/Graphics.hpp"
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
#define WINDOW_HEIGHT_TILES 30
#define WINDOW_WIDTH_TILES 20
#define SELECTION_PADDING 6
#define SELECTION_ALPHA 0.75

int main() {
  sf::ContextSettings contextSettings;
  contextSettings.antialiasingLevel = 8;

  sf::RenderWindow window(sf::VideoMode(TILE_SIZE * WINDOW_HEIGHT_TILES,
                                        TILE_SIZE * WINDOW_WIDTH_TILES),
                          "My Window", sf::Style::Default, contextSettings);
  window.setFramerateLimit(60);

  sf::Texture texture;
  if (!texture.loadFromFile(TILE_MAP)) {
    std::cout << "Failed to load texture from " << TILE_MAP << std::endl;
    return EXIT_FAILURE;
  }

  TileFactory tileFactory(texture, TILE_SIZE);

  std::vector<int> pos{0, 4, 8, 88};

  std::vector<sf::Sprite> selectable;
  size_t active = 0;
  sf::Sprite ptr_tile;
  for (size_t i = 0; i < 4; i++) {
    ptr_tile = tileFactory.getTile(pos[i]);
    ptr_tile.setPosition(TILE_SIZE * (i + 1),
                         TILE_SIZE * (WINDOW_WIDTH_TILES - 1));
    selectable.push_back(ptr_tile);
  }

  sf::Sprite pointer = sf::Sprite(selectable[active]);
  pointer.setColor(sf::Color(255, 255, 255, SELECTION_ALPHA * 255));

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
      } else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          // check if mouse is over a selectable
          bool selectableClicked = false;
          for (size_t i = 0; i < selectable.size(); i++) {
            sf::FloatRect bounds = selectable[i].getGlobalBounds();
            if (bounds.contains(
                    sf::Vector2f(event.mouseButton.x, event.mouseButton.y))) {
              active = i;
              selectableClicked = true;
              break;
            }
          }

          if (!selectableClicked) {
            sf::Sprite csprite(selectable[active]);
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
      } else if (event.type == sf::Event::MouseMoved) {
        // get the nearest position to put the sprite on a grid
        int x = event.mouseMove.x - (event.mouseMove.x % TILE_SIZE);
        int y = event.mouseMove.y - (event.mouseMove.y % TILE_SIZE);
        pointer.setPosition(sf::Vector2f(x, y));
      }
    }

    window.clear(clearColor);

    for (size_t i = 0; i < placedTiles.size(); i++) {
      window.draw(placedTiles[i]);
    }

    window.draw(pointer);

    // UI is drawn last
    for (size_t i = 0; i < selectable.size(); i++) {
      if (i == active) {
        selectable[i].setColor(sf::Color::White);
        pointer.setTextureRect(selectable[i].getTextureRect());
      } else {
        selectable[i].setColor(
            sf::Color(255, 255, 255, int(SELECTION_ALPHA * 255)));
      }
      window.draw(selectable[i]);
    }

    window.display();
  }
  return 0;
}
