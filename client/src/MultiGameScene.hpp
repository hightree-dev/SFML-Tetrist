#pragma once

#include <array>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/Network.hpp>

#include "Tetromino.hpp"
#include "Board.hpp"

class MultiGameScene : public Scene
{
public:
  MultiGameScene();
  void handleEvent(sf::Event& event) override;
  void handleUIEvent(sf::RenderWindow& window) override;
  void handleNetwork() override;
  void update(const sf::Time& deltaTime) override;
  void render(sf::RenderWindow& window) override;
private:
  void resetTetromino();
private:
  sf::TcpSocket socket;

  sf::Time timer;

  sf::Time duration;
  sf::Time tempDuration;

  const float blockSize;

  std::vector<std::array<int, 4>> figures;
  std::vector<sf::Color> tetrominoColors;

  Board board;
  Tetromino tetromino;
  Tetromino nextTetromino;

  Board board2;
  Tetromino tetromino2;
};

/*
0 1
2 3
4 5
6 7
*/

MultiGameScene::MultiGameScene()
: timer(sf::seconds(0.f))
, duration(sf::seconds(0.5f))
, tempDuration(duration)
, blockSize(20.f)
, figures {
  {0, 1, 3, 5},
  {0, 1, 2, 3},
  {1, 3, 5, 2}
}
, tetrominoColors {
  sf::Color::Red,
  sf::Color::Green,
  sf::Color::Blue,
}
, board(20, 10, sf::Color::Black)
, tetromino(figures[std::rand() % figures.size()], tetrominoColors[std::rand() % tetrominoColors.size()])
, nextTetromino(figures[std::rand() % figures.size()], tetrominoColors[std::rand() % tetrominoColors.size()])
, board2(20, 10, sf::Color::Black)
, tetromino2({0, 0, 0, 0}, sf::Color::Transparent)
{
  socket.connect("127.0.0.1", 8000);
  // if(socket.connect("127.0.0.1", 8000))
    // throw std::runtime_error("Failed to connect the server");
}

void MultiGameScene::handleEvent(sf::Event& event) 
{
  if (event.type != sf::Event::KeyPressed) return;
  
  if (event.key.code == sf::Keyboard::Right) tetromino.move({1.0f, 0.f});
  else if (event.key.code == sf::Keyboard::Left) tetromino.move({-1.0f, 0.f});
  else if (event.key.code == sf::Keyboard::Up) tetromino.rotate();
  else if (event.key.code == sf::Keyboard::Down) {
    tempDuration = duration;
    duration = sf::seconds(0.1f);
  }

  if (board.isCollision(tetromino.getPositions()))
    tetromino.undo();
}

void MultiGameScene::handleUIEvent(sf::RenderWindow& window) 
{
  
}

void MultiGameScene::handleNetwork()
{
  sf::Packet packet;
  packet << board;
  packet << tetromino;
  socket.send(packet);

  packet.clear();
  socket.receive(packet);
  packet >> board2;
  packet >> tetromino2;
}

void MultiGameScene::update(const sf::Time& deltaTime) 
{ 
  timer += deltaTime;

  if (timer > duration) {
    timer -= duration;
    tetromino.move({0.f, 1.f});
    const auto& positions = tetromino.getPositions();
    if (board.isCollision(positions)) {
      tetromino.undo();
      board.fixTetromino(positions, tetromino.getColor());
      board.clearLine();
      tetromino = nextTetromino;
      nextTetromino = Tetromino(figures[std::rand() % figures.size()], tetrominoColors[std::rand() % tetrominoColors.size()]);
    }
  }
  duration = tempDuration;
}

void MultiGameScene::render(sf::RenderWindow& window)
{
  board.render(window, sf::Vector2f(0.f, 0.f), blockSize);
  tetromino.render(window, sf::Vector2f(0.f, 0.f), blockSize);
  nextTetromino.render(window, sf::Vector2f(220.f, 20.f), blockSize);

  board2.render(window, sf::Vector2f(300.f, 0.f), blockSize);
  tetromino2.render(window, sf::Vector2(300.f, 0.f), blockSize);
}