#pragma once

#include <SFML/Graphics.hpp>

class Board
{
public:
  Board(const int width, const int height);
  int getWidth() const;
  int getHeight() const;
  sf::Color getColor(const int x, const int y) const;
  void setColor(const int x, const int y, const sf::Color& color);
  void draw(sf::RenderWindow& window);
private:
  int width;
  int height;
  std::vector<std::vector<sf::Color>> colors;
};