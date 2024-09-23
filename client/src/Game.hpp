#pragma once

#include <SFML/Graphics.hpp>
#include "SceneManger.hpp"
#include "GameScene.hpp"
#include "MultiGameScene.hpp"

class Game
{
public:
  Game();
  void run();
private:
  void handleEvents();
  void handleUIEvents();
  void handleNetwork();
  void update(const sf::Time& deltaTime);
  void updateStatistics(const sf::Time& deltaTime);
  void render();
  
private:
  const sf::Time timerPerFrame;
  
  sf::RenderWindow window;
  SceneManager& sceneManager;

  sf::Font font;
  sf::Text statisticsText;
  sf::Time statisticsTime;
  size_t   statisticFrameNum;
};


#include "Game.hpp"

Game::Game()
: window(sf::VideoMode(800, 600), "Tetris")
, timerPerFrame(sf::seconds(1.f / 60.f))
, sceneManager(SceneManager::getInstance())
{
  std::srand(std::time(nullptr));

  if(!font.loadFromFile("../resource/Arial.ttf"))
    throw std::runtime_error("Failed to load font");

  statisticsText.setFont(font);
  statisticsText.setCharacterSize(12);
  statisticsText.setPosition(sf::Vector2f(0.5f, 0.5f));
  statisticsText.setFillColor(sf::Color::White);
  statisticsText.setString("FPS : ");

  sceneManager.setScene(std::make_shared<MultiGameScene>());
}

void Game::run()
{
  sf::Clock clock;
  sf::Time timeSinceLastUpdate = sf::Time::Zero;
  while (window.isOpen())
  {
    sf::Time elapsedTime = clock.restart();
    timeSinceLastUpdate += elapsedTime;
    while (timeSinceLastUpdate > timerPerFrame) 
    {
      timeSinceLastUpdate -= timerPerFrame;
      handleEvents();
      handleUIEvents();
      update(timerPerFrame);
      handleNetwork();
    }
    updateStatistics(elapsedTime);
    render();
  }
}

void Game::handleEvents()
{
  sf::Event event;
  while (window.pollEvent(event))
    if (event.type == sf::Event::Closed) window.close();
    else sceneManager.handleEvent(event);
  
}

void Game::handleUIEvents()
{
  sceneManager.handleUIEvent(window);
}

void Game::handleNetwork()
{
  sceneManager.handleNetowrk();
}

void Game::update(const sf::Time& deltaTime)
{
  sceneManager.update(deltaTime);
}

void Game::updateStatistics(const sf::Time& deltaTime)
{
  statisticsTime += deltaTime;
  ++statisticFrameNum;
  if (statisticsTime > sf::seconds(1.f))
  {
    statisticsText.setString("FPS : " + std::to_string(statisticFrameNum));
    statisticsTime -= sf::seconds(1.f);
    statisticFrameNum = 0;
  }
}

void Game::render()
{
  window.clear(sf::Color::White);
  sceneManager.render(window);
  window.draw(statisticsText);
  window.display();
}