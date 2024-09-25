#include <iostream>
#include <SFML/Network.hpp>

int main()
{
  sf::SocketSelector selector;
  sf::TcpListener listener;
  listener.listen(8000);
  
  selector.add(listener);

  std::vector<std::unique_ptr<sf::TcpSocket>> sockets;

  while (true) {
    if (!selector.wait())
      continue;

    if (sockets.size() < 2 && selector.isReady(listener)) {
      auto socket = std::make_unique<sf::TcpSocket>();
      if (listener.accept(*socket) == sf::Socket::Done) {
        selector.add(*socket);
        socket->setBlocking(false);
        sockets.push_back(std::move(socket));
        std::cout << "connected " << sockets.size() << std::endl;
      }
    } else if(sockets.size() == 2){
      if (selector.isReady(*sockets[0])) {
        sf::Packet packet;
        if (sockets[0]->receive(packet) == sf::Socket::Done)
          sockets[1]->send(packet);
      }

      if (selector.isReady(*sockets[1])){
        sf::Packet packet;
        if (sockets[1]->receive(packet) == sf::Socket::Done)
          sockets[0]->send(packet);
      }
    }
  }
}