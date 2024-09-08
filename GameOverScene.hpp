#pragma once

#include "Scene.hpp"
#include <SFML/Graphics.hpp>

class GameOverScene : public Scene 
{
public:
  GameOverScene();
  void handleEvent(sf::Event& event) override;
  void update(float deltaTime) override;
  void render(sf::RenderWindow& window) override;
private:
  sf::Font font;
  sf::Text gameOverText;
};