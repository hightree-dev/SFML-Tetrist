#include <iostream>
#include "Game.hpp"

int main()
{
  std::srand(std::time(nullptr));
  Game game;
  game.run();
}