#include "ActionGenerator.h"

bool ActionGenerator::IsValidString(const string& input, uint8_t player_num) {
  auto result = CreateAction(input, player_num);
  if (result == std::nullopt) {
    return false;
  }
  return true;
}

shared_ptr<Action> ActionGenerator::GenerateFromString(uint8_t player_num, const string& input) {
  auto result = CreateAction(input, player_num);
  return result.value();
}

vector<string> ActionGenerator::SplitIntoWords(const string& input) {
  ssize_t start = -1;
  vector<string> words;
  for (size_t i = 0; i < input.size(); ++i) {
    if (input[i] == ' ' && i - start > 1) {
      words.push_back(input.substr(start + 1, i - start - 1));
    }
    if (input[i] == ' ') {
      start = i;
    }
  }
  if (input.size() - start > 1) {
    words.push_back(input.substr(start + 1, input.size() - start - 1));
  }
  return words;
}

std::optional<shared_ptr<Action>> ActionGenerator::CreateAction(const string& input, uint8_t player_num) {
  auto words = SplitIntoWords(input);
  auto result = std::optional<shared_ptr<Action>>{};
  if (!words.empty()) {
    if (words[0] == "pass") {
      result = std::make_shared<EndTurnAction>(player_num);
    }
    if (words[0] == "mv" || words[0] == "move") {
      result = CreateMoveAction(words, player_num);
    }
    if (words[0] == "fr" || words[0] == "fire") {
      result = CreateFireAction(words, player_num);
    }
    if (words[0] == "rt" || words[0] == "rotate") {
      result = CreateRotateAction(words, player_num);
    }
  }
  return result;
}

std::optional<shared_ptr<Action>> ActionGenerator::CreateRotateAction(const vector<string>& command, uint8_t player_num) {
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
    return std::make_shared<RotateClockwiseAction>(pivot, player_num);
  } else {
    return std::make_shared<RotateCounterClockwiseAction>(pivot, player_num);
  }
}

std::optional<shared_ptr<Action>> ActionGenerator::CreateMoveAction(const vector<string>& command, uint8_t player_num) {
  if (command.size() != 4) {
    return {};
  }
  Coords ship{};
  ship.x = stoul(command[1]);
  ship.y = stoul(command[2]);
  int distance = stoi(command[3]);
  return std::make_shared<MoveAction>(ship, distance, player_num);
}

std::optional<shared_ptr<Action>> ActionGenerator::CreateFireAction(const vector<string>& command, uint8_t player_num) {
  if (command.size() != 5) {
    return {};
  }
  Coords ship;
  ship.x = stoul(command[1]);
  ship.y = stoul(command[2]);
  Coords land;
  land.x = stoul(command[3]);
  land.y = stoul(command[4]);

  return std::make_shared<FireAction>(ship, land, player_num);
}
