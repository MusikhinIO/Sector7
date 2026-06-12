#pragma once

#include <iostream>
#include <string>
#include <vector>

#include "../entities/enemy.h"
#include "../items/item.h"
#include "../player/player.h"
#include "../systems/combat_system.h"
#include "../world/room.h"
#include "parser.h"
#include "text_manager.h"

// класс игрового цикла
class Game {
 public:
  Game();

  bool Initialize();
  void Run();

  static constexpr int kDefendHealValue = 5;
  static constexpr float kDefendDamageAbsorb = 0.4f;
  static constexpr float kChargeDamageMultiply = 3.0f;

 private:
  // состояние игры
  bool is_running_;
  std::string current_room_id_;
  Player player_;

  // данные
  std::vector<Room> rooms_;
  std::vector<Enemy> enemies_;
  std::vector<Item> items_;

  Room* GetCurrentRoom();
  Enemy* FindEnemyById(const std::string& id);
  Item* FindItemById(const std::string& id);

  // обработка команд
  void ProcessCommand(const std::string& command);

  void PrintHelp() const;
  void Stats() const;
  void ShowInventory() const;
  void Look();
  void Go(const std::string& direction);
  void TakeItem();
  void UseItem(int item_index);

  void Attack();
  void Defend();
  void Charge();
  void Interact();

  std::string ToLower(std::string str) const;
};
