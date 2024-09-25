#include <iostream>
#include <list>
#include <queue>
#include <SFML/Network.hpp>

class Room
{
public:
  Room(std::unique_ptr<sf::TcpSocket> a, std::unique_ptr<sf::TcpSocket> b)
  : p1(std::move(a)), p2(std::move(b)), running(true)
  {
    std::cout << "Created Room" << std::endl;
  }

  ~Room() 
  {
    std::cout << "Distroyed Room" << std::endl;
  }
  bool isRunning() 
  {
    return running;
  }

  void handlePacket(sf::SocketSelector& selector)
  {
    if (!selector.wait())
      return;

    if (selector.isReady(*p1)) {
      sf::Packet packet;
      auto status = p1->receive(packet);
      if (status == sf::Socket::Done) {
        auto status = p2->send(packet);
        if (status == sf::Socket::Disconnected) {
          running = false;
        }
      } else if (status == sf::Socket::Disconnected) {
        running = false;
      }
    }
    
    if (selector.isReady(*p2)) {
      sf::Packet packet;
      auto status = p2->receive(packet);
      if (status == sf::Socket::Done) {
        auto status = p1->send(packet);
        if (status == sf::Socket::Disconnected) {
          running = false;
        }
      } else if (status == sf::Socket::Disconnected) {
        running = false;
      }
    }
  }
private:
  bool running;
  std::unique_ptr<sf::TcpSocket> p1;
  std::unique_ptr<sf::TcpSocket> p2;
};

int main()
{
  sf::SocketSelector selector;
  sf::TcpListener listener;
  listener.listen(8000);
  
  selector.add(listener);

  std::queue<std::unique_ptr<sf::TcpSocket>> clients;
  std::list<std::unique_ptr<Room>> rooms;

  
  while (true) {
    if (selector.wait()) {
      if (selector.isReady(listener)) {
        auto client = std::make_unique<sf::TcpSocket>();
        listener.accept(*client);
        selector.add(*client);
        client->setBlocking(false);
        if (clients.empty()) {
          clients.push(std::move(client));
        } else {
          std::unique_ptr<Room> room = std::make_unique<Room>(std::move(clients.front()), std::move(client));
          rooms.push_back(std::move(room));
          clients.pop();
        }
      }
    } 
    for (auto& room : rooms)
      room->handlePacket(selector);
  }
}