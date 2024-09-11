#include "GameScene.hpp"
#include "GameOverScene.hpp"
#include "SceneManager.hpp"
#include "ScoreDB.hpp"
#include <iostream>
#include <SFML/Graphics.hpp>

GameScene::GameScene() : 
figures{{ 0, 1, 3, 5 },
        { 0, 1, 2, 3 },
        { 1, 3, 2, 5 },
        { 1, 3, 5, 7 }},
colors{sf::Color::Red,
       sf::Color::Green,
       sf::Color::Blue,
       sf::Color::Yellow,
       sf::Color::Cyan,
       sf::Color::Magenta},
board{10, 20}, 
block{figures[std::rand() % figures.size()], colors[std::rand() % colors.size()]},
score{0}, timer{0.f}, delay{0.5f},
gameOverButton(200.f, 200.f, 100.f, 50.f, "Game Over")
{
  font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf");
  scoreText.setFont(font);
  scoreText.setCharacterSize(20);
  scoreText.setString("Score : " + std::to_string(score));
  scoreText.setFillColor(sf::Color::Black);
  scoreText.setPosition(210, 10);
}

void GameScene::handleEvent(sf::Event& event)
{
  if (sf::Event::KeyPressed != event.type) return;

  if (event.key.code == sf::Keyboard::Left) block.move({-1.f, 0.f});
  else if (event.key.code == sf::Keyboard::Right) block.move({1.f, 0.f});
  else if (event.key.code == sf::Keyboard::Up) block.rotate();
  else if (event.key.code == sf::Keyboard::Down) delay = 0.05f;
  if (board.isCollision(block.getPosisitons()))
    block.back();
}

void GameScene::handleUIEvent(sf::RenderWindow& window)
{
  if (gameOverButton.isClicked(window))
    gameOver();
}

void GameScene::update(float deltaTime) 
{
  timer += deltaTime;
  if (timer > delay)
  {
    block.move({0.f, 1.f});
    if (board.isCollision(block.getPosisitons()))
    {
      block.back();
      if (board.isCollision(block.getPosisitons()))
      {
        gameOver();
      }
      else
      {
        for (const auto& pos : block.getPosisitons())
          board.setColor(pos.x, pos.y, block.getColor());
        int clearedLineCount = board.clearLine();
        score += clearedLineCount;
        scoreText.setString("Score : " + std::to_string(score));
        block = Block(figures[std::rand() % figures.size()], colors[std::rand() % colors.size()]);
      } 
    }
    timer = 0.f;
    delay = 0.5f;
  }
}

void GameScene::render(sf::RenderWindow& window) 
{
    window.clear(sf::Color::White);
    gameOverButton.draw(window);
    board.draw(window);
    block.draw(window);
    window.draw(scoreText);
    window.display();
}

void GameScene::gameOver()
{
  try
  {
    ScoreDB::getInstance().addScore(score);
  }
  catch(const std::exception& e)
  {
    std::cerr << "Eception: " << e.what() << std::endl;
  }
  
  SceneManager::getInstance().setScene(std::make_shared<GameOverScene>(score));
}