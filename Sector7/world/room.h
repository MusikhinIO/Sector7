#pragma once

#include <string>

#include "../entities/enemy.h"

// класс комнаты
class Room {
 public:
  Room();
  Room(const std::string& id, const std::string& name,
       const std::string& description, const std::string& north_id,
       const std::string& south_id, const std::string& east_id,
       const std::string& west_id, const std::string& enemy_id,
       const std::string& item_id, const std::string& env_action);

  // информация о комнате
  std::string Id() const { return id_; }
  std::string Name() const { return name_; }
  std::string Description() const { return description_; }

  // соседние комнаты
  std::string NorthId() const { return north_id_; }
  std::string SouthId() const { return south_id_; }
  std::string EastId() const { return east_id_; }
  std::string WestId() const { return west_id_; }

  // враги и предметы в комнате
  std::string EnemyId() const { return enemy_id_; }
  bool HasActiveEnemy() const { return has_active_enemy_; }
  std::string ItemId() const { return item_id_; }

  Enemy* GetActiveEnemy() {
    return has_active_enemy_ ? &active_enemy_ : nullptr;
  }

  void SetActiveEnemy(const Enemy& enemy_template) {
    active_enemy_ = enemy_template;
    has_active_enemy_ = true;
  }

  void ClearActiveEnemy() { has_active_enemy_ = false; }

  void SetEnemyId(const std::string& id) { enemy_id_ = id; }
  void SetItemId(const std::string& id) { item_id_ = id; }

  // механика использования окружения
  std::string EnvAction() const { return env_action_; }
  bool IsEnvUsed() const { return env_used_; }
  void SetEnvUsed(bool used) { env_used_ = used; }

 private:
  std::string id_;
  std::string name_;
  std::string description_;
  std::string north_id_;
  std::string south_id_;
  std::string east_id_;
  std::string west_id_;
  std::string enemy_id_;
  std::string item_id_;

  std::string env_action_;
  bool env_used_ = false;

  Enemy active_enemy_;
  bool has_active_enemy_ = false;
};
