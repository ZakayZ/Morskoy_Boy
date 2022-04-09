#pragma once

#include "Action.h"
#include <memory>
#include <vector>
#include <string>
using std::string;
using std::vector;
using std::shared_ptr;

class ActionGenerator {
 public:
  [[nodiscard]] bool IsValidValidString(const string&) const;
  [[nodiscard]] shared_ptr<Action> GenerateFromString(uint8_t, const string&) const;
 private:
  [[nodiscard]] vector<string> SplitIntoWords(const string&) const;
};