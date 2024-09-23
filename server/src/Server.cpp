#include <iostream>
#include <SFML/Network.hpp>

int main()
{
  sf::TcpListener listener;
  listener.listen(8000);
  
  std::vector<std::unique_ptr<sf::Thread>> threads;

  while (true) {
    auto socket = std::make_shared<sf::TcpSocket>();
    listener.accept(*socket);
    
    std::cout << "connected" << std::endl;

    auto thread = std::make_unique<sf::Thread>([socket](){
      while (true) {
        sf::Packet packet;
        socket->receive(packet);
        socket->send(packet);
      }
    });
    thread->launch();

    threads.emplace_back(std::move(thread));
  }
}