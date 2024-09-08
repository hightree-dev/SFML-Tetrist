#pragma once

#include <SFML/Graphics.hpp>

class Board
{
public:
  Board(const int width, const int height);
  void setColor(const int x, const int y, const sf::Color& color);
  bool isCollision(const std::array<sf::Vector2f, 4>& positions) const;
  void draw(sf::RenderWindow& window);
private:
  int width;
  int height;
  std::vector<std::vector<sf::Color>> colors;
};