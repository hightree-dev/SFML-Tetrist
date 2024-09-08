#include "SceneManager.hpp"

SceneManager& SceneManager::getInstance()
{
  static SceneManager instance;
  return instance;
}
SceneManager::SceneManager() { }

void SceneManager::setScene(std::shared_ptr<Scene> scene) 
{
  currentScene = scene;
}

void SceneManager::handleEvent(sf::Event& event) 
{
  if (currentScene) currentScene->handleEvent(event);
}


void SceneManager::handleUIEvent(sf::RenderWindow& window)
{
  if (currentScene) currentScene->handleUIEvent(window);
}

void SceneManager::update(const float deltaTime) 
{
  if (currentScene) currentScene->update(deltaTime);
}

void SceneManager::render(sf::RenderWindow& window) 
{
  if (currentScene) currentScene->render(window);
}