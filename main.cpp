#include "Interface/Interface.h"

int main() {
  const size_t width = 1000;
  const size_t height = 1000;
  const size_t actions = 3;
  GraphicalInterface interface(width, height, actions);
  sf::Thread visual_thread(&GraphicalInterface::Game, &interface);
  visual_thread.launch();
  interface.Display();
  visual_thread.terminate();
}