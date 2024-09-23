#pragma once

#include "Scene.hpp"
#include <SFML/Graphics.hpp>

class SceneManager 
{
public:
	static SceneManager& getInstance();
  
  SceneManager(const SceneManager&) = delete;
  SceneManager& operator=(const SceneManager&) = delete;

	void setScene(std::shared_ptr<Scene> scene);
	void handleEvent(sf::Event& event);
	void handleUIEvent(sf::RenderWindow& window);
  void handleNetowrk();
	void update(const sf::Time& deltaTime);
	void render(sf::RenderWindow& window);
private:
	SceneManager();
	std::shared_ptr<Scene> currentScene;
};

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

void SceneManager::handleNetowrk()
{
  if (currentScene) currentScene->handleNetwork();
}

void SceneManager::update(const sf::Time& deltaTime) 
{
  if (currentScene) currentScene->update(deltaTime);
}

void SceneManager::render(sf::RenderWindow& window) 
{
  if (currentScene) currentScene->render(window);
}