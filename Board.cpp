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

int Board::clearLine()
{
  int count = 0;
  for (int y = height - 1; y >= 0; --y)
  {
    bool isFull = true;
    for (int x = 0; x < width; ++x)
    {
      if (colors[y][x] == sf::Color::White)
      {
        isFull = false;
        break;
      }
    }
    if (isFull)
    {
      for (int curY = y; curY > 0; --curY)
        colors[curY] = colors[curY - 1];
      colors[0] = std::vector<sf::Color>(width, sf::Color::White);
      ++y;
      ++count;
    }
  }
  return count;
}

void Board::draw(sf::RenderWindow& window)
{
  for (int y = 0; y < height; ++y)
    for (int x = 0; x < width; ++x)
      Painter::getInstance().draw(window, sf::Vector2f(x, y), colors[y][x]);
}