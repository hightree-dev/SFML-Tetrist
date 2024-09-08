#include "Block.hpp"
#include "Painter.hpp"

Block::Block(const int* figure, const sf::Color& color) : color(color)
{
  for (int i = 0; i < 4; ++i)
  {
    positions[i].x = figure[i] % 2;
    positions[i].y = figure[i] / 2;
  }
}

void Block::move(const sf::Vector2f& v)
{
  prevPositions = positions;
  for (auto& pos : positions)
    pos += v;
}

void Block::rotate()
{
  prevPositions = positions;
  const auto& center = positions[1];
  for (auto& pos : positions)
  {
    const auto& v = pos - center;
    pos.x = center.x - v.y;
    pos.y = center.y + v.x;
  }
}

void Block::draw(sf::RenderWindow& window)
{
  for (const auto& pos : positions )
    Painter::getInstance().draw(window, pos, color);
}