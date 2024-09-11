#pragma once

#include "Scene.hpp"
#include "Button.hpp"
#include <SFML/Graphics.hpp>

class IntroScene : public Scene 
{
public:
	IntroScene();
	void handleEvent(sf::Event& event) override;
	void handleUIEvent(sf::RenderWindow& window) override;
	void update(float deltaTime) override;
	void render(sf::RenderWindow& window) override;
private:
	sf::Font font;
	Button startButton;
};