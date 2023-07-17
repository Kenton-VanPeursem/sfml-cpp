#include "tileplacer.h"
#include "SFML/System/Vector2.hpp"

void TilePlacer::resetOrigin() {
  switch (this->rotation) {
  case 1:
    this->tile.setOrigin(sf::Vector2f(0.f, TILE_SIZE));
    break;
  case 2:
    this->tile.setOrigin(sf::Vector2f(TILE_SIZE, TILE_SIZE));
    break;
  case 3:
    this->tile.setOrigin(sf::Vector2f(TILE_SIZE, 0.f));
    break;
  default:
    this->tile.setOrigin(sf::Vector2f(0.f, 0.f));
    break;
  }
}

void TilePlacer::setActive(sf::Sprite sprite) {
  this->tile = sprite;
  this->tile.setColor(sf::Color(255, 255, 255, SELECTION_ALPHA * 255));
  this->rotation = 0;
}

void TilePlacer::rotateClockwise() {
  sf::Vector2f pos = this->tile.getPosition();
  this->rotation = (this->rotation + 1) % 4;
  this->tile.rotate(this->getRotation());
  this->resetOrigin();
  this->setPosition(pos);
}

void TilePlacer::rotateCounterClockwise() {
  sf::Vector2f pos = this->tile.getPosition();
  this->rotation = (this->rotation - 1) % 4;
  this->tile.rotate(this->getRotation());
  this->resetOrigin();
  this->setPosition(pos);
}

float TilePlacer::getRotation() { return this->rotation * 90.f; }

void TilePlacer::mirror() {
  this->tile.scale(this->tile.getScale().x * -1.f, 1.f);
}

bool TilePlacer::isMirror() { return this->tile.getScale().x == -1.f; }

void TilePlacer::setPosition(sf::Vector2f position) {
  this->tile.setRotation(this->getRotation());
  this->resetOrigin();
  this->tile.setPosition(position);
}

sf::Vector2f TilePlacer::getPosition() { return this->tile.getPosition(); }

sf::Sprite TilePlacer::getSprite() { return this->tile; }
