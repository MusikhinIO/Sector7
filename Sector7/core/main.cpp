#include <cstdlib>
#include <ctime>
#include <iostream>

#include "game.h"

int main() {
  setlocale(LC_ALL, "Russian");

  std::srand(static_cast<unsigned int>(std::time(nullptr)));

  std::cout << "========================================\n";
  std::cout << "       PROTOCOL: DERELICT v1.0        \n";
  std::cout << "========================================\n\n";

  Game game;

  if (!game.Initialize()) {
    return 1;
  }

  game.Run();

  std::cout << "\nКонец игры\n";
  return 0;
}
