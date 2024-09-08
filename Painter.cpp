#include "Painter.hpp"

Painter::Painter() : 
size{20.f}, thickness{2.f}, 
shape(sf::Vector2f(size - 2 * thickness, size - 2 * thickness))
{
  shape.setOutlineColor(sf::Color::Black);
  shape.setOutlineThickness(thickness);
}

Painter& Painter::getInstance()
{
  static Painter instance;
  return instance;
}

void Painter::draw(sf::RenderWindow& window, sf::Vector2f pos, sf::Color color)
{
  shape.setPosition(pos + sf::Vector2f(thickness, thickness));
  shape.setFillColor(color);
  window.draw(shape);
}