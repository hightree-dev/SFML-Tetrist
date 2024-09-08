#include "GameScene.hpp"
#include "GameOverScene.hpp"
#include "SceneManager.hpp"

GameOverScene::GameOverScene() :
restartButtonShape({200.f, 50.f})
{
  font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf");
  
  gameOverText.setFont(font);
  gameOverText.setCharacterSize(50);
  gameOverText.setString("GameOver");
  gameOverText.setFillColor(sf::Color::Black);
  gameOverText.setStyle(sf::Text::Bold);
  gameOverText.setPosition(0, 0);

  restartButtonShape.setOutlineColor(sf::Color::Black);
  restartButtonShape.setOutlineThickness(2.f);
  restartButtonShape.setPosition({0.f, 100.f});
}

void GameOverScene::handleEvent(sf::Event& event)
{
}

void GameOverScene::handleUIEvent(sf::RenderWindow& window)
{ 
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    if (restartButtonShape.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
      SceneManager::getInstance().setScene(std::make_shared<GameScene>());
}

void GameOverScene::update(float deltaTime)
{ 
}

void GameOverScene::render(sf::RenderWindow& window)
{
  window.clear(sf::Color::White);
  window.draw(gameOverText);
  window.draw(restartButtonShape);
  window.display();
}