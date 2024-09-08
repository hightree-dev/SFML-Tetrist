#include "Block.hpp"
#include "Board.hpp"
#include <SFML/Graphics.hpp>

/*
0 1
2 3
4 5
6 7
*/

int figure[4] = { 0, 1, 3, 5};

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "Tetris");

  Board board(10, 20);
  Block block(figure, sf::Color::Green);

  while (window.isOpen())
  {
    sf::Event event;
    while (window.pollEvent(event))
    {
      switch (event.type)
      {
      case sf::Event::Closed:
        window.close();
        break;
      case sf::Event::KeyPressed:
        if (event.key.code == sf::Keyboard::Left) block.move({-1.f, 0.f});
        else if (event.key.code == sf::Keyboard::Right) block.move({1.f, 0.f});
        else if (event.key.code == sf::Keyboard::Up) block.rotate();
        else if (event.key.code == sf::Keyboard::Down) block.move({0.f, 1.f});
        if (board.isCollision(block.getPosisitons()))
          block.back();
        break;
      default:
        break;
      }
    }
    
    window.clear(sf::Color::White);
    board.draw(window);
    block.draw(window);
    window.display();
  }
}