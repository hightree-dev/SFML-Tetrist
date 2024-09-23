#pragma once

#include <array>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class Tetromino
{
public:
  Tetromino(const std::array<int, 4>& figure, const sf::Color& color);
  void move(const sf::Vector2f& movement);
  void rotate();
  void render(sf::RenderWindow& window, const sf::Vector2f& renderPos = sf::Vector2f(0.f, 0.f), const float size = 20.f);
  const std::array<sf::Vector2f, 4>& getPositions();
  void undo();
  const sf::Color& getColor();
  
  friend sf::Packet& operator<<(sf::Packet& packet, Tetromino& rhs)
  {
    packet << rhs.color.toInteger();
    for (const auto& pos : rhs.positions)
      packet << pos.x << pos.y;
    return packet;
  }

  friend sf::Packet& operator>>(sf::Packet& packet, Tetromino& rhs)
  {
    sf::Uint32 color;
    packet >> color;
    rhs.color = sf::Color(color);
    for (auto& pos : rhs.positions)
      packet >> pos.x >> pos.y;
    return packet;
  }

private:
  sf::Color color;
  std::array<sf::Vector2f, 4> positions;
  std::array<sf::Vector2f, 4> prevPositions;
};

Tetromino::Tetromino(const std::array<int, 4>& figure, const sf::Color& color)
: color(color)
, positions()
, prevPositions()
{
  for (int i = 0; i < figure.size(); ++i)
    positions[i] = sf::Vector2f(figure[i] % 2, figure[i] / 2);
  prevPositions = positions;
}

void Tetromino::move(const sf::Vector2f& movement)
{
  prevPositions = positions;
  for (sf::Vector2f& pos : positions)
    pos += movement;
}

void Tetromino::rotate()
{
  prevPositions = positions;
  const sf::Vector2f& center = positions[1];
  for (sf::Vector2f& pos : positions) {
    const sf::Vector2f bias = pos - center;
    pos.x = center.x - bias.y;
    pos.y = center.y + bias.x;
  }
}

void Tetromino::render(sf::RenderWindow& window, const sf::Vector2f& renderPos, const float size)
{
  sf::RectangleShape shape(sf::Vector2f(size, size));
  shape.setFillColor(color);
  for (const sf::Vector2f& pos : positions) {
    shape.setPosition(pos * size + renderPos);
    window.draw(shape);
  }
}

void Tetromino::undo()
{
  positions = prevPositions;
}

const std::array<sf::Vector2f, 4>& Tetromino::getPositions()
{
  return positions;
}

const sf::Color& Tetromino::getColor()
{
  return color;
}