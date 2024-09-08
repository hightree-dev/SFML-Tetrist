#include "Board.hpp"
#include "Painter.hpp"

Board::Board(const int width, const int height) : width{width}, height{height} 
{ 
  colors.reserve(height);
  for (int i = 0; i < height; ++i)
    colors[i] = std::vector<sf::Color>(width, sf::Color::White);
}

int Board::getWidth() const
{
  return width;
}

int Board::getHeight() const
{
  return height;
}

sf::Color Board::getColor(const int x, const int y) const
{
  return colors[y][x];
}

void Board::setColor(const int x, const int y, const sf::Color& color)
{
  colors[y][x] = color;
}

void Board::draw(sf::RenderWindow& window)
{
  for (int i = 0; i < height; ++i)
    for (int j = 0; j < width; ++j)
      Painter::getInstance().draw(window, sf::Vector2f(j, i), colors[i][j]);
}