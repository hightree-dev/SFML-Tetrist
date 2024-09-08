#pragma once

#include "Board.hpp"
#include "Block.hpp"
#include "Scene.hpp"
#include <SFML/Graphics.hpp>

class GameScene : public Scene
{
public:
  GameScene();
  void handleEvent(sf::Event& event) override;
  void handleUIEvent(sf::RenderWindow& window) override;
  void update(float deltaTime) override;
  void render(sf::RenderWindow& window) override;
private:
  int score;
  float timer;
  float delay;

  std::vector<std::array<int, 4>> figures;
  std::vector<sf::Color> colors;

  Board board;
  Block block;

  sf::Font font;
  sf::Text scoreText;
};