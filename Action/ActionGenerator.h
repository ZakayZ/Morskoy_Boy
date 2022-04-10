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
  [[nodiscard]] static bool IsValidString(const string&) ;
  [[nodiscard]] static shared_ptr<Action> GenerateFromString(uint8_t, const string&) ;
 private:
  [[nodiscard]] static vector<string> SplitIntoWords(const string&) ;
  static std::optional<shared_ptr<Action>> CreateAction(const string&);
  static std::optional<shared_ptr<Action>> CreateRotateAction(const vector<string>&);
  static std::optional<shared_ptr<Action>> CreateMoveAction(const vector<string>&);
  static std::optional<shared_ptr<Action>> CreateFireAction(const vector<string>&);
};