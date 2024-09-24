#include <iostream>
#include <SFML/Network.hpp>

int main()
{
  sf::TcpListener listener;
  listener.listen(8000);
  listener.setBlocking(false);

  std::vector<std::unique_ptr<sf::TcpSocket>> sockets;

  while (true) {
    auto socket = std::make_unique<sf::TcpSocket>();
    socket->setBlocking(false);
    if (listener.accept(*socket) == sf::Socket::Done) {
      std::cout << "connected" << std::endl;
      sockets.push_back(std::move(socket));
    }

    for (auto& socket : sockets) {
      sf::Packet packet;
      if (socket->receive(packet) == sf::Socket::Done)
        socket->send(packet);
    }
  }
}