#include "Interface.h"

Interface::Interface(size_t actions) : active_(true), game_(actions) {}

Error Interface::ProcessSetupAction(const string& command, uint8_t player_num, bool& player_finished) {
  auto action = ActionGenerator::GenerateFromString(player_num, command);
  auto error = game_.CheckAction(*action);
  if (action->GetActionType() == ActionType::EndTurn || Error::kOutOfActions == error) {
    player_finished = true;
    return error;
  }
  if (action->GetActionType() == ActionType::Fire) {
    error = Error::kInvalidTarget;
  }
  if (error == Error::kNoError) {
    game_.ManageAction(*action);
  }
  return error;
}

Error Interface::ProcessTurnAction(const string& command, uint8_t player_num, bool& player_finished) {
  auto action = ActionGenerator::GenerateFromString(player_num, command);
  auto error = game_.CheckAction(*action);
  if (action->GetActionType() == ActionType::EndTurn) {
    game_.ManageAction(*action);
    player_finished = true;
    return error;
  }
  if (error == Error::kOutOfActions) {
    game_.ManageAction(EndTurnAction(player_num));
    player_finished = true;
  }
  if (error == Error::kNoError) {
    game_.ManageAction(*action);
  }
  return error;
}

void Interface::SetupMessage(Error error) {
  switch (error) {
    case Error::kOutOfActions: {
      cout << "How I ended up here! \n";
      break;
    }
    case Error::kNoError: {
      cout << "Success!\n";
      break;
    }
    case Error::kInvalidShip: {
      cout << "No ship with this coordinates! \n";
      break;
    }
    case Error::kInvalidTarget: {
      cout << "Can't fire in this stage! \n";
      break;
    }
    case Error::kShipIsDead: {
      cout << "This ship is dead! \n";
      break;
    }
    case Error::kIntersectsFieldBoundary: {
      cout << "This position is out of field! \n";
      break;
    }
    case Error::kIntersectsShip: {
      cout << "This position intersect other ship! \n";
      break;
    }
    case Error::kWeaponOnCooldown: {
      cout << "Ship's weapons are reloading! \n";
      break;
    }
    case Error::kOutOfMoney: {
      cout << "You can't buy ships now! \n";
      break;
    }
  }
}

void Interface::TurnMessage(Error error) {
  switch (error) {
    case Error::kOutOfActions: {
      cout << "No Actions left, change! \n";
      break;
    }
    case Error::kNoError: {
      cout << "Success!\n";
      break;
    }
    case Error::kInvalidShip: {
      cout << "No ship with this coordinates! \n";
      break;
    }
    case Error::kInvalidTarget: {
      cout << "Invalid target! \n";
      break;
    }
    case Error::kShipIsDead: {
      cout << "This ship is dead! \n";
      break;
    }
    case Error::kIntersectsFieldBoundary: {
      cout << "This position is out of field! \n";
      break;
    }
    case Error::kIntersectsShip: {
      cout << "This position intersect other ship! \n";
      break;
    }
    case Error::kWeaponOnCooldown: {
      cout << "Ship's weapons are reloading! \n";
      break;
    }
    case Error::kOutOfMoney: {
      cout << "You can't buy ships now! \n";
      break;
    }
  }
}

GraphicalInterface::GraphicalInterface(
    size_t width, size_t height, size_t actions, std::shared_ptr<ImageStorage>& storage)
    : Interface(actions),
      windows_({std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), "Ships1"),
                std::make_shared<sf::RenderWindow>(sf::VideoMode(width, height), "Ships2")}),
      renderers_({SFMLRenderer(windows_[0], storage), SFMLRenderer(windows_[1], storage)}),
      animations_() {
  windows_[0]->setFramerateLimit(15);
  windows_[1]->setFramerateLimit(15);
}

GraphicalInterface::~GraphicalInterface() = default;

void GraphicalInterface::Setup() {
//  cout << "Enter first player name: ";
//  std::string first_player_name;
//  cin >> first_player_name;
//  cout << "Enter second player name: ";
//  std::string second_player_name;
//  cin >> second_player_name;
//  game_.MakeNewGame(first_player_name, second_player_name);
  cout << "First player can setup his fleet:\n";
  Setup(1);
  std::system("clear");
  cout << "Second player can setup his fleet:\n";
  Setup(2);
  std::system("clear");
}

void GraphicalInterface::Game() {
  Setup();
  while (Running()) {
    GameCycle();
  }
}

void GraphicalInterface::Display(const std::array<const Player*, 2>& players, uint8_t player) {
  sf::Event event;
  while (windows_[player]->pollEvent(event)) {
    if (event.type == sf::Event::Closed) {
      windows_[player]->close();
      windows_[(player + 1) % 2]->close();
    }
  }

  windows_[player]->clear();
  renderers_[player].Render(*players[player], {0, 0}, true);
  renderers_[player].Render(*players[(player + 1) % 2], {900, 0}, false);
  for (size_t i = 0; i < animations_[player].size(); ++i) {
    if (animations_[player][i].IsExpired()) {
      animations_[player].erase(animations_[player].begin() + i);
      --i;
    } else {
      renderers_[player].Render(animations_[player][i], {0, 0}, true);
    }
  }
  for (size_t i = 0; i < animations_[(player + 1) % 2].size(); ++i) {
    if (animations_[(player + 1) % 2][i].IsExpired()) {
      animations_[(player + 1) % 2].erase(animations_[(player + 1) % 2].begin() + i);
      --i;
    } else {
      renderers_[player].Render(animations_[(player + 1) % 2][i], {900, 0}, true);
    }
  }
  windows_[player]->display();
}

void GraphicalInterface::GameCycle() {
  std::system("clear");
  cout << "First player's turn:\n";
  Turn(1);
  std::system("clear");
  cout << "Second player's turn:\n";
  Turn(2);

  game_.NextTurn();
  auto projectiles = game_.GetLanding();
  for (const auto&[center, player_num] : projectiles) {
    animations_[player_num % 2].emplace_back(AnimationFactory::MakeBoomAnimation(center));
  }

  cout << "EndTurn!\n";
}

bool GraphicalInterface::Running() const {
  return windows_[0]->isOpen() && windows_[1]->isOpen();
}

void GraphicalInterface::Setup(uint8_t player_num) {
  bool player_finished = false;
  std::string command;
  while (!player_finished) {
    std::getline(cin, command);
    if (!ActionGenerator::IsValidString(command, player_num)) {
      std::cout << "invalid input\n";
      continue;
    }
    auto error = ProcessSetupAction(command, player_num, player_finished);
    SetupMessage(error);
  }
}

void GraphicalInterface::Turn(uint8_t player_num) {
  bool player_finished = false;
  std::string command;
  while (!player_finished) {
    std::getline(cin, command);
    if (!ActionGenerator::IsValidString(command, player_num)) {
      continue;
    }
    auto error = ProcessTurnAction(command, player_num, player_finished);
    TurnMessage(error);
  }
}

void GraphicalInterface::Display() {
  std::array<const Player*, 2> players = {&game_.GetPlayer(1), &game_.GetPlayer(2)};
  while (Running()) {
    Display(players, 0);

    Display(players, 1);

    AdvanceAnimations();
  }
}

void GraphicalInterface::AdvanceAnimations() {
  for (auto& animation : animations_[0]) {
    animation.AdvanceFrame();
  }
  for (auto& animation : animations_[1]) {
    animation.AdvanceFrame();
  }
}
