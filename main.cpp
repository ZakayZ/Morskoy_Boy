#include "Renderer/ImageStorage.h"
#include "Interface/Interface.h"

int main() {
  const size_t width = 2500;
  const size_t height = 1900;
  const size_t actions = 3;
  auto storage = std::make_shared<ImageStorage>();
  GraphicalInterface interface(width, height, actions, storage);
  sf::Thread visual_thread(&GraphicalInterface::Game, &interface);
  visual_thread.launch();
  interface.Display();
  visual_thread.terminate();
}