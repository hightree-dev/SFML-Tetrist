#pragma once

#include <SFML/Graphics.hpp>

class Block
{
public:
  Block(int* figure, sf::Color color);
  void move(sf::Vector2f v);
  void rotate();
  void draw(sf::RenderWindow& window);
private:
  sf::Color color;
  std::array<sf::Vector2f, 4> positions;
  std::array<sf::Vector2f, 4> prevPositions;
};