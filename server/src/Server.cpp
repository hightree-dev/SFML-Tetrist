#include <iostream>
#include <list>
#include <SFML/Network.hpp>

int main()
{
  sf::SocketSelector selector;

  sf::TcpListener listener;
  if (listener.listen(8000) != sf::Socket::Done) 
    return 1;
  selector.add(listener);

  // 과연 랜덤 액세스를 할 일이 있을까?
  // 물론 빡세게 고려하지 않아도 됨. 왜냐하면 stl 컨테이너라 컨테이너만 갈아끼우면 되기 때문임.
  // 소켓 컨테이너는 랜덤 액세스보다 연결 끊어져서 erase 하는 케이스가 더 많을 듯 함.
  std::list<std::unique_ptr<sf::TcpSocket>> clients;

  while (true) {
    if (!selector.wait())
      continue;
    
    if (selector.isReady(listener)) {
      std::unique_ptr<sf::TcpSocket> client = std::make_unique<sf::TcpSocket>();
      if (listener.accept(*client) == sf::Socket::Done) {
        std::cout << "connected" << std::endl;
        selector.add(*client);
        clients.push_back(std::move(client));
      }
    }

    for (auto it = clients.begin(); it != clients.end(); ++it) {
      auto& client = **it;
      if (!selector.isReady(client)) 
        continue;
      
      sf::Packet packet;
      auto status = client.receive(packet);
      
      if (status == sf::Socket::Done) {
        auto status = client.send(packet);
        if (status == sf::Socket::Disconnected) {
          selector.remove(client);
          client.disconnect();
          it = clients.erase(it);  
        }
      } else if (status == sf::Socket::Disconnected) {
        selector.remove(client);
        client.disconnect();
        it = clients.erase(it);
      }
    }
  }
}