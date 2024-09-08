#include "GameScene.hpp"
#include "IntroScene.hpp"
#include "SceneManager.hpp"

IntroScene::IntroScene() :
gameStartButton{{200.f, 50.f}}
{
  font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf");
  gameStartButton.setOutlineColor(sf::Color::Black);
  gameStartButton.setOutlineThickness(2.f);
}

void IntroScene::handleEvent(sf::Event& event)
{
}

void IntroScene::handleUIEvent(sf::RenderWindow& window)
{ 
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
    if (gameStartButton.getGlobalBounds().contains(static_cast<sf::Vector2f>(sf::Mouse::getPosition(window))))
      SceneManager::getInstance().setScene(std::make_shared<GameScene>());
}

void IntroScene::update(float deltaTime)
{ 
}

void IntroScene::render(sf::RenderWindow& window)
{
  window.clear(sf::Color::White);
  window.draw(gameStartButton);
  window.display();
}