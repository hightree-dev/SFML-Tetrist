#include "GameScene.hpp"
#include "IntroScene.hpp"
#include "GameOverScene.hpp"
#include "SceneManager.hpp"

GameOverScene::GameOverScene(int score) :
restartButton{0,175.f, 100.f, 50.f, "Restart"},
introButton{0, 100.f, 100.f, 50.f, "Intro"}
{
  font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf");
  
  gameOverText.setFont(font);
  gameOverText.setCharacterSize(32);
  gameOverText.setString("GameOver");
  gameOverText.setFillColor(sf::Color::Black);
  gameOverText.setStyle(sf::Text::Bold);
  gameOverText.setPosition(0, 0);

  scoreText.setFont(font);
  scoreText.setCharacterSize(32);
  scoreText.setString("Score : " + std::to_string(score));
  scoreText.setFillColor(sf::Color::Black);
  scoreText.setStyle(sf::Text::Bold);
  scoreText.setPosition(0.f, 50.f);
}

void GameOverScene::handleEvent(sf::Event& event)
{
}

void GameOverScene::handleUIEvent(sf::RenderWindow& window)
{ 
  if (restartButton.isClicked(window))
    SceneManager::getInstance().setScene(std::make_shared<GameScene>());
  else if (introButton.isClicked(window))
    SceneManager::getInstance().setScene(std::make_shared<IntroScene>());
}

void GameOverScene::update(float deltaTime)
{ 
}

void GameOverScene::render(sf::RenderWindow& window)
{
  window.clear(sf::Color::White);
  window.draw(gameOverText);
  window.draw(scoreText);
  introButton.draw(window);
  restartButton.draw(window);
  window.display();
}