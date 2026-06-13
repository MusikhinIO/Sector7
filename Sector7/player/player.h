#pragma once

#include <string>
#include <vector>

#include "../items/item.h"

// класс игрока
class Player {
 public:
  Player();
  Player(const std::string& name, int hp, int damage);

  std::string Name() const { return name_; }
  int Hp() const { return hp_; }
  void SetHp(int hp) { hp_ = hp; }
  int MaxHp() const { return max_hp_; }
  int Damage() const { return damage_; }
  void SetDamage(int damage) { damage_ = damage; }

  bool IsDefending() const { return is_defending_; }
  void SetDefending(bool defending) { is_defending_ = defending; }

  bool IsCharging() const { return is_charging_; }
  void SetCharging(bool charging) { is_charging_ = charging; }

  // инвентарь
  std::vector<Item>& Inventory() { return inventory_; }
  const std::vector<Item>& Inventory() const { return inventory_; }
  void AddItem(const Item& item);

 private:
  std::string name_;
  int hp_;
  int max_hp_;
  int damage_;
  std::vector<Item> inventory_;

  // состояния
  bool is_defending_;
  bool is_charging_;
};
