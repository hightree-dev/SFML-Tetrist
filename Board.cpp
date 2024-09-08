#include "Board.hpp"
#include "Painter.hpp"

Board::Board(const int width, const int height) : width{width}, height{height} 
{ 
  colors.reserve(height);
  for (int i = 0; i < height; ++i)
    colors[i] = std::vector<sf::Color>(width, sf::Color::White);
}

void Board::setColor(const int x, const int y, const sf::Color& color)
{
  colors[y][x] = color;
}

bool Board::isCollision(const std::array<sf::Vector2f, 4>& positions) const
{
  for (const auto& pos : positions)
    if (pos.x < 0 || pos.x >= width) return true;
    else if (pos.y < 0 || pos.y >= height) return true;
    else if (sf::Color::White != colors[pos.y][pos.x]) return true;
  return false;
}

void Board::draw(sf::RenderWindow& window)
{
  for (int i = 0; i < height; ++i)
    for (int j = 0; j < width; ++j)
      Painter::getInstance().draw(window, sf::Vector2f(j, i), colors[i][j]);
}