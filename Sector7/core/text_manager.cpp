#include "text_manager.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::unordered_map<std::string, std::string> TextManager::strings_;

bool TextManager::LoadStrings(const std::string& filename) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Critical error: Failed to open " << filename << std::endl;
    return false;
  }

  std::string line;
  while (std::getline(file, line)) {
    if (line.empty() || line[0] == '#') continue;

    std::stringstream ss(line);
    std::string key, text;

    if (std::getline(ss, key, '|') && std::getline(ss, text)) {
      strings_[key] = text;
    }
  }
  return true;
}

std::string TextManager::Get(const std::string& key) {
  auto it = strings_.find(key);
  if (it != strings_.end()) {
    return it->second;
  }
  // Защита от опечаток в коде: если ключа нет, увидим это в консоли
  return "MISSING_STRING: " + key;
}
