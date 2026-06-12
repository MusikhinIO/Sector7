#pragma once

#include <string>
#include <vector>

// классы данных
#include "../entities/enemy.h"
#include "../items/item.h"
#include "../world/room.h"

// класс парсера
class Parser {
 public:
  static constexpr char kDelimiter = '|';             // разделитель
  static constexpr const char* kEmptyValue = "NONE";  // нулевое значение

  static constexpr int kItemColumnCount = 6;
  static constexpr int kEnemyColumnCount = 6;
  static constexpr int kRoomColumnCount = 10;

  static bool ParseItems(const std::string& filename, std::vector<Item>& items);
  static bool ParseEnemies(const std::string& filename,
                           std::vector<Enemy>& enemies);
  static bool ParseRooms(const std::string& filename, std::vector<Room>& rooms);

 private:
  static std::vector<std::string> SplitString(const std::string& str,
                                              char delimiter);
};
