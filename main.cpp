#include "GameScene.hpp"
#include <SFML/Graphics.hpp>

int main()
{
  std::srand(std::time(0));

  sf::RenderWindow window(sf::VideoMode(800, 600), "Tetris");

  sf::Clock clock;

  GameScene scene;

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (sf::Event::Closed == event.type) window.close();
      scene.handleEvent(event);
    }
    float deltaTime = clock.getElapsedTime().asSeconds();
    clock.restart();
    scene.update(deltaTime);
    scene.render(window);
  }
}