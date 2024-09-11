#include <SFML/Graphics.hpp>

class Button 
{
public:
  Button(float x, float y, float width, float height);
  Button(float x, float y, float width, float height, std::string textString);
  void draw(sf::RenderWindow& window);
  bool isClicked(sf::RenderWindow& window);
private:
  sf::RectangleShape shape;
  sf::Font font;
  sf::Text text;
  float thickness;
  bool wasClick;
};