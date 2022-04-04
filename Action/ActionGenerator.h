#pragma once

#include "../includes.h"

class ActionGenerator {
 public:
  [[nodiscard]] bool IsValidValidString(const string&) const;
  [[nodiscard]] std::shared_ptr<Action> GenerateFromString(uint8_t, const string&) const;
 private:
  [[nodiscard]] vector<string> SplitIntoWords(const string&) const;
};