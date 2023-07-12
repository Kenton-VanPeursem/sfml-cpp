#include "SFML/Graphics/RectangleShape.hpp"
#include "SFML/Graphics/Shape.hpp"
#include "SFML/System/Vector2.hpp"
#include "SFML/Window/ContextSettings.hpp"
#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>

struct Player {
  sf::Vector2f position;
  sf::Vector2f size;
  sf::Color color;
  float speed;

  Player() {
    this->position = sf::Vector2f(0.f, 0.f);
    this->size = sf::Vector2f(50.f, 50.f);
    this->color = sf::Color::Black;
    this->speed = 5.f;
  }

  void move(sf::Vector2f delta) {
    this->position += (this->speed * delta);
  }
};

int main() {
  sf::ContextSettings contextSettings;
  contextSettings.antialiasingLevel = 8;

  sf::RenderWindow window(sf::VideoMode(800, 600), "My Window", sf::Style::Default, contextSettings);
  // window.setVerticalSyncEnabled(true);
  window.setFramerateLimit(30);

  std::cout << "Window is focused? " << window.hasFocus() << std::endl;
  sf::Vector2u size = window.getSize();
  std::cout << "Window size? (x=" << size.x << " y=" << size.y << ")"
            << std::endl;
  sf::Vector2i pos = window.getPosition();
  std::cout << "Window position? (x=" << pos.x << " y=" << pos.y << ")"
            << std::endl;

  Player player;

  sf::Color clearColor = sf::Color::White;
  while (window.isOpen()) {
    sf::Event event;
    
    while (window.pollEvent(event)) {
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
        std::cout << "Direct: Escape key is pressed" << std::endl;
      }

      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        std::cout << "Direct: Left key is pressed" << std::endl;
        player.move(sf::Vector2f(-1.f, 0.f));
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        std::cout << "Direct: Right key is pressed" << std::endl;
        player.move(sf::Vector2f(1.f, 0.f));
      }
      if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        std::cout << "Direct: Down key is pressed" << std::endl;
        player.move(sf::Vector2f(0.f, 1.f));
      } else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        std::cout << "Direct: Up key is pressed" << std::endl;
        player.move(sf::Vector2f(0.f, -1.f));
      }

      if (event.type == sf::Event::Closed) {
        window.close();
      } else if (event.type == sf::Event::LostFocus) {
        std::cout << "Window is focused? " << window.hasFocus() << std::endl;
      } else if (event.type == sf::Event::GainedFocus) {
        std::cout << "Window is focused? " << window.hasFocus() << std::endl;
      } else if (event.type == sf::Event::Resized) {
        std::cout << "Window resized: x=" << window.getSize().x
                  << " y=" << window.getSize().y << std::endl;
      } else if (event.type == sf::Event::MouseButtonPressed) {
        if (event.mouseButton.button == sf::Mouse::Left) {
          std::cout << "Mouse button pressed: LEFT" << std::endl;
          clearColor = sf::Color::Green;
        } else if (event.mouseButton.button == sf::Mouse::Right) {
          std::cout << "Mouse button pressed: RIGHT" << std::endl;
          clearColor = sf::Color::Blue;
        }
      } else if (event.type == sf::Event::MouseMoved) {
        std::cout << "Mouse moved: x=" << event.mouseMove.x
                  << " y=" << event.mouseMove.y << std::endl;
      } else if (event.type == sf::Event::TextEntered) {
        std::cout << "Text entered: " << std::string(sf::String(event.text.unicode)) << std::endl;
      }
    }

    window.clear(clearColor);

    sf::RectangleShape shape(player.size);
    shape.setFillColor(sf::Color::Black);
    shape.setPosition(player.position);
    window.draw(shape);

    window.display();
  }
  return 0;
}
