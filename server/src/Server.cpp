#include <iostream>
#include <SFML/Network.hpp>

int main()
{
  sf::TcpListener listener;
  listener.listen(8000);
  listener.setBlocking(false);

  std::vector<std::unique_ptr<sf::TcpSocket>> sockets;

  while (true) {
    if (sockets.size() < 2) {
      auto socket = std::make_unique<sf::TcpSocket>();
      socket->setBlocking(false);
      if (listener.accept(*socket) == sf::Socket::Done) {
        std::cout << "connected" << std::endl;
        sockets.push_back(std::move(socket));
      }
    }
    else {
      {
        sf::Packet packet;
        if (sockets[0]->receive(packet) == sf::Socket::Done)
          sockets[1]->send(packet);
      }
      {
        sf::Packet packet;
        if (sockets[1]->receive(packet) == sf::Socket::Done)
          sockets[0]->send(packet);
      }
    }
  }
}