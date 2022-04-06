#include "includes.h"

int main() {
  auto window = std::make_shared<sf::RenderWindow>(sf::VideoMode(1000, 1000), "Morskoy Boy");
  window->setFramerateLimit(3);
  SFMLRenderer sfml_renderer(window);
  vector<Ship> fleet;
  Shipyard factory;
  fleet.push_back(factory.MakeFrigate());
  fleet.back().Translate({2, 2});
  fleet.push_back(factory.MakeFrigate());
  fleet.back().Translate({8, 8});
  fleet.push_back(factory.MakeMothership());
  fleet.back().Translate({4, 4});
  Player player(3, {10, 10}, fleet);
  while (window->isOpen()) {
    sf::Event event;
    while (window->pollEvent(event)) {
      if (event.type == sf::Event::Closed)
        window->close();
    }
    window->clear();
    sfml_renderer.Render(player, {0, 0}, true);
    player.Rotate({2, 2}, {2, 2}, false);
    player.Rotate({8, 8}, {8, 8}, true);
    player.Rotate({5, 5}, {5, 5}, false);
    window->display();
  }

//  auto window = std::make_shared<ConsoleWindow>(size_t(10), size_t(10));
//  ConsoleRenderer console_renderer(window);
//  vector<Ship> fleet;
//  Shipyard factory;
//  fleet.push_back(factory.MakeFrigate());
//  fleet.back().Translate({2, 2});
//  fleet.push_back(factory.MakeFrigate());
//  fleet.back().Translate({8, 8});
//  fleet.push_back(factory.MakeMothership());
//  fleet.back().Translate({4, 4});
//  Player player(3, {10, 10}, fleet);
//  while (true) {
//    window->Clear();
//    console_renderer.Render(player, {0, 0}, true);
//    player.Rotate({2, 2}, {2, 2}, false);
//    player.Rotate({8, 8}, {8, 8}, true);
//    player.Rotate({5, 5}, {5, 5}, false);
//    window->Display();
//    break;
//  }
}