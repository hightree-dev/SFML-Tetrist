#pragma once

#include <SFML/Graphics.hpp>

class Painter
{
public:
  static Painter& getInstance();
  
  Painter(const Painter&) = delete;
  Painter& operator=(const Painter&) = delete;

  void draw(sf::RenderWindow& window, sf::Vector2f pos, sf::Color color);

private:
  Painter();

private:
  float size;
  float thickness;
  sf::RectangleShape shape;
};