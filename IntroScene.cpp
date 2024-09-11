#include "GameScene.hpp"
#include "IntroScene.hpp"
#include "SceneManager.hpp"

IntroScene::IntroScene() :
startButton{0.f, 0.f, 100.f, 50.f, "Start!"}
{
  
}

void IntroScene::handleEvent(sf::Event& event)
{
}

void IntroScene::handleUIEvent(sf::RenderWindow& window)
{ 
  if (startButton.isClicked(window))
    SceneManager::getInstance().setScene(std::make_shared<GameScene>());  
}

void IntroScene::update(float deltaTime)
{ 
}

void IntroScene::render(sf::RenderWindow& window)
{
  window.clear(sf::Color::White);
  startButton.draw(window);
  window.display();
}