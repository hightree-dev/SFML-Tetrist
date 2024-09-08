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
	void update(float deltaTime);
	void render(sf::RenderWindow& window);
private:
	SceneManager();
	std::shared_ptr<Scene> currentScene;
};