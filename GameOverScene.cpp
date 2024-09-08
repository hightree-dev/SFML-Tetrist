#include "GameOverScene.hpp"

GameOverScene::GameOverScene()
{
  font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf");
  gameOverText.setFont(font);
  gameOverText.setCharacterSize(50);
  gameOverText.setString("GameOver");
  gameOverText.setFillColor(sf::Color::Black);
  gameOverText.setStyle(sf::Text::Bold);
  gameOverText.setPosition(0, 0);
}

void GameOverScene::handleEvent(sf::Event& event)
{

}
void GameOverScene::update(float deltaTime)
{
  
}
void GameOverScene::render(sf::RenderWindow& window)
{
  window.clear(sf::Color::White);
  window.draw(gameOverText);
  window.display();
}