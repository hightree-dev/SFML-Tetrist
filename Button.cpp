#include "Button.hpp"

Button::Button(float x, float y, float width, float height) :
thickness{1.f}, wasClick{false}
{
  

  shape.setPosition(x + thickness, y + thickness);
  shape.setSize({width - 2 * thickness, height - 2 * thickness});
  shape.setOutlineColor(sf::Color::Black);
  shape.setOutlineThickness(thickness);
  shape.setFillColor(sf::Color::White);
}

Button::Button(float x, float y, float width, float height, std::string textString) : Button(x, y, width, height)
{
  if (!font.loadFromFile("/System/Library/Fonts/Supplemental/Arial.ttf"))
    throw std::runtime_error("Failed to load font");
  text.setFont(font);
  text.setString(textString);
  text.setFillColor(sf::Color::Black);
  text.setCharacterSize(16);

  sf::FloatRect textRect = text.getLocalBounds();
  text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2.0f);
  text.setPosition(x + width / 2.0f, y + height / 2.0f);
}

void Button::draw(sf::RenderWindow& window)
{
  window.draw(shape);
  window.draw(text);
}

bool Button::isClicked(sf::RenderWindow& window)
{
  if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
  {
    sf::Vector2i mousePos = sf::Mouse::getPosition(window);
    if (shape.getGlobalBounds().contains(static_cast<sf::Vector2f>(mousePos)))
    {
      if(wasClick) 
        return false;
      wasClick = true;
      return true;
    }
  }
  wasClick = false;
  return false;
}