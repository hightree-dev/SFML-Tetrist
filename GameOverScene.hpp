#pragma once

#include "Scene.hpp"
#include "Button.hpp"
#include <SFML/Graphics.hpp>

class GameOverScene : public Scene 
{
public:
  GameOverScene(int score);
  void handleEvent(sf::Event& event) override;
  void handleUIEvent(sf::RenderWindow& window) override;
  void update(float deltaTime) override;
  void render(sf::RenderWindow& window) override;
private:
  sf::Font font;
  sf::Text gameOverText;
  sf::Text scoreText;
  sf::Text maxScoreText;

  Button introButton;
  Button restartButton;
};