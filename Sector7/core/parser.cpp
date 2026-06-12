#include "parser.h"

#include <fstream>
#include <iostream>
#include <sstream>

std::vector<std::string> Parser::SplitString(const std::string& str,
                                             char delimiter) {
  std::vector<std::string> tokens;
  std::stringstream ss(str);
  std::string token;

  while (std::getline(ss, token, delimiter)) {
    tokens.push_back(token);
  }
  return tokens;
}

bool Parser::ParseItems(const std::string& filename, std::vector<Item>& items) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Critical error: Failed to open " << filename << ". Exiting."
              << std::endl;
    return false;
  }

  std::string line;
  int line_number = 0;  // дл€ вы€влени€ битой строки в файле

  while (std::getline(file, line)) {
    line_number++;

    if (line.empty() || line[0] == '#') {
      continue;
    }

    std::vector<std::string> data = SplitString(line, kDelimiter);

    if (data.size() == kItemColumnCount) {
      const std::string& item_id = data[0];
      const std::string& name = data[1];
      const std::string& type = data[2];
      const int value = std::stoi(data[3]);
      const std::string& description = data[4];
      const int spawn_chance = std::stoi(data[5]);

      items.emplace_back(item_id, name, type, value, description, spawn_chance);
    } else {
      std::cerr << "Warning: Malformed item data at line " << line_number
                << " in " << filename << ". Skipping." << std::endl;
    }
  }

  file.close();
  return true;
}

bool Parser::ParseEnemies(const std::string& filename,
                          std::vector<Enemy>& enemies) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Critical error: Failed to open " << filename << ". Exiting."
              << std::endl;
    return false;
  }

  std::string line;
  int line_number = 0;  // дл€ вы€влени€ битой строки в файле

  while (std::getline(file, line)) {
    line_number++;
    if (line.empty() || line[0] == '#') {
      continue;
    }

    std::vector<std::string> data = SplitString(line, kDelimiter);

    if (data.size() == kEnemyColumnCount) {
      const std::string& enemy_id = data[0];
      const std::string& name = data[1];
      const int hp = std::stoi(data[2]);
      const int damage = std::stoi(data[3]);
      const std::string& description = data[4];
      const int spawn_chance = std::stoi(data[5]);

      enemies.emplace_back(enemy_id, name, hp, damage, description,
                           spawn_chance);
    } else {
      std::cerr << "Warning: Malformed enemy data at line " << line_number
                << " in " << filename << ". Skipping." << std::endl;
    }
  }

  file.close();
  return true;
}

bool Parser::ParseRooms(const std::string& filename, std::vector<Room>& rooms) {
  std::ifstream file(filename);
  if (!file.is_open()) {
    std::cerr << "Critical error: Failed to open " << filename << ". Exiting."
              << std::endl;
    return false;
  }

  std::string line;
  int line_number = 0;  // дл€ вы€влени€ битой строки в файле

  while (std::getline(file, line)) {
    line_number++;
    if (line.empty() || line[0] == '#') {
      continue;
    }

    std::vector<std::string> data = SplitString(line, kDelimiter);

    if (data.size() == kRoomColumnCount) {
      const std::string& room_id = data[0];
      const std::string& name = data[1];
      const std::string& description = data[2];
      const std::string& north_id = data[3];
      const std::string& south_id = data[4];
      const std::string& east_id = data[5];
      const std::string& west_id = data[6];
      const std::string& enemy_id = data[7];
      const std::string& item_id = data[8];
      const std::string& env_action = data[9];

      rooms.emplace_back(room_id, name, description, north_id, south_id,
                         east_id, west_id, enemy_id, item_id, env_action);
    } else {
      std::cerr << "Warning: Malformed room data at line " << line_number
                << " in " << filename << ". Skipping." << std::endl;
    }
  }

  file.close();
  return true;
}
