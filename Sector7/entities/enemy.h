#pragma once

#include <string>

// класс врага
class Enemy {
 public:
  Enemy();
  Enemy(const std::string& id, const std::string& name, int hp, int damage,
        const std::string& description, int spawn_chance);

  std::string Id() const { return id_; }
  std::string Name() const { return name_; }
  int Hp() const { return hp_; }
  void SetHp(int hp) { hp_ = hp; }
  int MaxHp() const { return max_hp_; }
  int Damage() const { return damage_; }
  std::string Description() const { return description_; }
  int SpawnChance() const { return spawn_chance_; }

  int StunTurns() const { return stun_turns_; }
  void SetStunTurns(int turns) { stun_turns_ = turns; }
  void AddStunTurns(int turns) { stun_turns_ += turns; }
  bool IsAlive() const { return hp_ > 0; }

 private:
  std::string id_;
  std::string name_;
  int hp_;
  int max_hp_;
  int damage_;
  std::string description_;
  int spawn_chance_;

  int stun_turns_;
};
