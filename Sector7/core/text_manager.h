#pragma once

#include <string>
#include <unordered_map>

class TextManager {
 public:
  static bool LoadStrings(const std::string& filename);
  static std::string Get(const std::string& key);

 private:
  static std::unordered_map<std::string, std::string> strings_;
};
