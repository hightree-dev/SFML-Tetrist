#include <iostream>
#include <SFML/Network.hpp>
#include <SFML/Graphics.hpp>

#include "Board.hpp"
#include "Tetromino.hpp"

int main()
{
  sf::RenderWindow window(sf::VideoMode(800, 600), "Server");

  Board board(20, 10, sf::Color::Black);
  Tetromino tetromino({0, 0, 0, 0}, sf::Color::Transparent);

  std::unique_ptr<sf::Thread> thread = std::make_unique<sf::Thread>([&board, &tetromino]{
    sf::TcpListener listener;
    listener.listen(8000);
    
    sf::TcpSocket socket;
    listener.accept(socket);
   
    std::cout << "connected" << std::endl;

    while (true) {
      sf::Packet packet;
      socket.receive(packet);
      packet >> board;
      packet >> tetromino;
      socket.send(packet);
    }
  });

  thread->launch();

  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event))
      if (event.type == sf::Event::Closed)
        window.close();
    window.clear(sf::Color::White);
    board.render(window, sf::Vector2f(0.f, 0.f), 20.f);
    tetromino.render(window);
    window.display();
  }

  
}