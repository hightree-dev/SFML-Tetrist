#include "IntroScene.hpp"
#include "GameScene.hpp"
#include "SceneManager.hpp"
#include <SFML/Graphics.hpp>

int main()
{
  std::srand(std::time(0));

  sf::RenderWindow window(sf::VideoMode(800, 600), "Tetris");

  sf::Clock clock;

  SceneManager& sceneManager = SceneManager::getInstance();
  sceneManager.setScene(std::make_shared<GameScene>());

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      if (sf::Event::Closed == event.type) window.close();
      sceneManager.handleEvent(event);
    }
    float deltaTime = clock.getElapsedTime().asSeconds();
    clock.restart();
    sceneManager.handleUIEvent(window);
    sceneManager.update(deltaTime);
    sceneManager.render(window);
  }
}