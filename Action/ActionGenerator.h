#pragma once

#include "Action.h"
#include <memory>
#include <vector>
#include <string>
#include <optional>

using std::string;
using std::vector;
using std::shared_ptr;

class ActionGenerator {
 public:
  [[nodiscard]] static bool IsValidString(const string&, uint8_t player_num);
  [[nodiscard]] static shared_ptr<Action> GenerateFromString(uint8_t player_num, const string&);
 private:
  [[nodiscard]] static vector<string> SplitIntoWords(const string& input);
  static std::optional<shared_ptr<Action>> CreateAction(const string& command, uint8_t player_num);
  static std::optional<shared_ptr<Action>> CreateRotateAction(const vector<string>& command, uint8_t player_num);
  static std::optional<shared_ptr<Action>> CreateMoveAction(const vector<string>& command, uint8_t player_num);
  static std::optional<shared_ptr<Action>> CreateFireAction(const vector<string>& command, uint8_t player_num);
  static std::optional<shared_ptr<Action>> CreateConstructAction(const vector<string>& command, uint8_t player_num);
  static std::optional<shared_ptr<Action>> CreateTranslateAction(const vector<string>& command, uint8_t player_num);
};