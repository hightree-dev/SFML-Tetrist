#pragma once

#include <SFML/Graphics.hpp>

class Scene 
{
public:
  virtual void handleEvent(sf::Event& event) = 0;
  virtual void update(float deltaTime) = 0;
  virtual void render(sf::RenderWindow& window) = 0;
};

