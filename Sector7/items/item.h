#pragma once

#include <string>

// класс предмета
class Item {
 public:
  Item();
  Item(const std::string& id, const std::string& name, const std::string& type,
       int value, const std::string& description, int spawn_chance);

  std::string Id() const { return id_; }
  std::string Name() const { return name_; }
  std::string Type() const { return type_; }
  int Value() const { return value_; }
  std::string Description() const { return description_; }
  int SpawnChance() const { return spawn_chance_; }

 private:
  std::string id_;
  std::string name_;
  std::string type_;
  int value_;
  std::string description_;
  int spawn_chance_;
};
