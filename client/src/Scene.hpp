#pragma once

#include <SFML/Graphics.hpp>

class Scene 
{
public:
  virtual void handleEvent(sf::Event& event) = 0;
  virtual void handleUIEvent(sf::RenderWindow& window) = 0;
  virtual void update(const sf::Time& deltaTime) = 0;
  virtual void render(sf::RenderWindow& window) = 0;
};

