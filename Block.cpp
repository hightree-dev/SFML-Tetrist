#include "Block.hpp"
#include "Painter.hpp"

Block::Block(const std::array<int , 4>& figure, const sf::Color& color) : color(color)
{
  for (int i = 0; i < 4; ++i)
  {
    positions[i].x = figure[i] % 2;
    positions[i].y = figure[i] / 2;
  }
  prevPositions = positions;
}

const std::array<sf::Vector2f, 4>& Block::getPosisitons() const
{
  return positions;
}

const sf::Color& Block::getColor() const
{
  return color;
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

void Block::back()
{
  positions = prevPositions;
}

void Block::draw(sf::RenderWindow& window)
{
  for (const auto& pos : positions )
    Painter::getInstance().draw(window, pos, color);
}