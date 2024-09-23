#pragma once

#include <iostream>
#include <array>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

class Board
{
public:
  Board(const int row, const int col, const sf::Color& backgroundColor);
  void render(sf::RenderWindow& window, const sf::Vector2f& pos, const float blockSize);
  const sf::Color& getColor(const int x, const int y);
  void setColor(const int x, const int y, const sf::Color& color);
  int clearLine();
  bool isCollision(const std::array<sf::Vector2f, 4>& positions);
  void fixTetromino(const std::array<sf::Vector2f, 4>& positions, const sf::Color& color);

  friend sf::Packet& operator<<(sf::Packet& packet, Board& rhs)
  {
    for (int y = 0; y < rhs.row; ++y)
      for (int x = 0; x < rhs.col; ++x)
        packet << rhs.colors[y][x].toInteger();
    return packet;
  }

  friend sf::Packet& operator>>(sf::Packet& packet, Board& rhs)
  {
    for (int y = 0; y < rhs.row; ++y) {
      for (int x = 0; x < rhs.col; ++x) {
        sf::Uint32 color;
        packet >> color;
        rhs.colors[y][x] = sf::Color(color);
      }
    }
    return packet;
  }

private:
  int row;
  int col;

  sf::Color backgroundColor;
  std::vector<std::vector<sf::Color>> colors;
};

Board::Board(const int row, const int col, const sf::Color& backgroundColor)
: row(row), col(col), backgroundColor(backgroundColor)
{
  for (int i = 0; i < row; ++i)
    colors.push_back(std::vector<sf::Color>(col, backgroundColor));
}

void Board::render(sf::RenderWindow& window, const sf::Vector2f& pos, const float blockSize = 20.f)
{
  sf::RectangleShape shape(sf::Vector2(blockSize, blockSize));

  for (int i = 0; i < row; ++i) {
    for (int j = 0; j < col; ++j) {
      shape.setPosition(sf::Vector2f(20.f * j, 20.f * i) + pos);
      shape.setFillColor(colors[i][j]);
      window.draw(shape);
    }
  }
}

const sf::Color& Board::getColor(const int x, const int y)
{
  return colors[y][x];
}

void Board::setColor(const int x, const int y, const sf::Color& color)
{
  colors[y][x] = color;
}

int Board::clearLine()
{ 
  int lineCount = 0;
  for (int y = row - 1; y > 0; --y) { // 마지막 줄이 꽉차는 케이스는 존재 X
    int count = 0;
    for (int x = 0; x < col; ++x) {
      if (colors[y][x] == backgroundColor)
        break;
      count++;
    }

    if (count == col) {
      // 라인 클리어 알고리즘
      ++lineCount;
      for (int ty = y; ty > 0; --ty)
        colors[ty] = colors[ty - 1];
      colors[0] = std::vector<sf::Color>(col, backgroundColor);
    }
  }
  return lineCount;
}

bool Board::isCollision(const std::array<sf::Vector2f, 4>& positions)
{
  for (const auto& p : positions)
    if (p.x < 0 || p.x >= 10 || p.y < 0 || p.y >= 20) return true;
    else if (colors[p.y][p.x] != backgroundColor) return true;
  return false;
}

void Board::fixTetromino(const std::array<sf::Vector2f, 4>& positions, const sf::Color& color)
{
  for (const auto& p : positions)
    colors[p.y][p.x] = color;
}