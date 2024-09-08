#pragma once

#include <SFML/Graphics.hpp>

class Block
{
public:
  Block(const std::array<int , 4>& figure, const sf::Color& color);
  const std::array<sf::Vector2f, 4>& getPosisitons() const;
  const sf::Color& getColor() const;
  void move(const sf::Vector2f& v);
  void rotate();
  void back();
  void draw(sf::RenderWindow& window);
private:
  sf::Color color;
  std::array<sf::Vector2f, 4> positions;
  std::array<sf::Vector2f, 4> prevPositions;
};