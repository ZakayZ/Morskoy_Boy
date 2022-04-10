#include "ActionGenerator.h"

bool ActionGenerator::IsValidString(const string& input) {
  auto result = CreateAction(input);
  if (result == std::nullopt) {
    return false;
  }
  return true;
}

shared_ptr<Action> ActionGenerator::GenerateFromString(uint8_t player, const string& input) {
  auto result = CreateAction(input);
  return result.value();
}

vector<string> ActionGenerator::SplitIntoWords(const string& input) {
  size_t start = 0;
  vector<string> words;
  for (size_t i = 0; i < input.size(); ++i) {
    if (input[i] == ' ' && i - start > 1) {
      words.push_back(input.substr(start + 1, i - start - 1));
    }
    start = i;
  }
  return words;
}

std::optional<shared_ptr<Action>> ActionGenerator::CreateAction(const string& input) {
  auto words = SplitIntoWords(input);
  auto result = std::optional<shared_ptr<Action>>{};
  if (!words.empty()) {
    if (words[0] == "pass") {
      result = std::make_shared<EndTurnAction>();
    }
    if (words[0] == "mv" || words[0] == "move") {
      result = CreateMoveAction(words);
    }
    if (words[0] == "fr" || words[0] == "fire") {
      result = CreateFireAction(words);
    }
    if (words[0] == "rt" || words[0] == "rotate") {
      result = CreateRotateAction(words);
    }
  }
  return result;
}

std::optional<shared_ptr<Action>> ActionGenerator::CreateRotateAction(const vector<string>& command) {
  if (command.size() != 4) {
    return {};
  }
  Coords pivot;
  pivot.x = stoul(command[1]);
  pivot.y = stoul(command[2]);
  size_t clockwise = stoul(command[3]);
  if (clockwise > 1) {
    return {};
  }

  if (clockwise == 1) {
    return std::make_shared<RotateClockwiseAction>(pivot);
  } else {
    return std::make_shared<RotateCounterClockwiseAction>(pivot);
  }
}

std::optional<shared_ptr<Action>> ActionGenerator::CreateMoveAction(const vector<string>& command) {
  if (command.size() != 4) {
    return {};
  }
  Coords ship{};
  ship.x = stoul(command[1]);
  ship.y = stoul(command[2]);
  int distance = stoi(command[3]);
  return std::make_shared<MoveAction>(ship, distance);
}

std::optional<shared_ptr<Action>> ActionGenerator::CreateFireAction(const vector<string>& command) {
  if (command.size() != 5) {
    return {};
  }
  Coords ship;
  ship.x = stoul(command[1]);
  ship.y = stoul(command[2]);
  Coords land;
  land.x = stoul(command[3]);
  land.y = stoul(command[4]);

  return std::make_shared<FireAction>(ship, land, 0);
}
