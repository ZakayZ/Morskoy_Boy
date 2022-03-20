#pragma once

#include "../includes.h"

#ifndef MORSKOY_BOY_MORSKOY_BOY_INTERFACE_ACTIONGENERATOR_H_
#define MORSKOY_BOY_MORSKOY_BOY_INTERFACE_ACTIONGENERATOR_H_

class ActionGenerator {
 public:
  [[nodiscard]] bool IsValidValidString(const string&) const;
  [[nodiscard]] std::shared_ptr<Action> GenerateFromString(uint8_t, const string&) const;
 private:
  [[nodiscard]] vector<string> SplitIntoWords(const string&) const;
};

#endif //MORSKOY_BOY_MORSKOY_BOY_INTERFACE_ACTIONGENERATOR_H_
