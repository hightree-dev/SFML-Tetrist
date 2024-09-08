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
  sf::Clock clock;

  Board board(10, 20);
  Block block(figure, sf::Color::Green);

  float timer = 0.f;
  float delay = 0.5f;

  while (window.isOpen())
  {
    timer += clock.getElapsedTime().asSeconds();
    clock.restart();

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
        else if (event.key.code == sf::Keyboard::Down) delay = 0.05f;
        if (board.isCollision(block.getPosisitons()))
          block.back();
        break;
      default:
        break;
      }
    }

    if (timer > delay)
    {
      block.move({0.f, 1.f});
      if (board.isCollision(block.getPosisitons()))
          block.back();
      timer = 0.f;
      delay = 0.5f;
    }
    
    window.clear(sf::Color::White);
    board.draw(window);
    block.draw(window);
    window.display();
  }
}