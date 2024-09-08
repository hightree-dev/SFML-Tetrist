#pragma once

#include <SFML/Graphics.hpp>

class Block
{
public:
  Block(const int* figure, const sf::Color& color);
  void move(const sf::Vector2f& v);
  void rotate();
  void draw(sf::RenderWindow& window);
private:
  sf::Color color;
  std::array<sf::Vector2f, 4> positions;
  std::array<sf::Vector2f, 4> prevPositions;
};