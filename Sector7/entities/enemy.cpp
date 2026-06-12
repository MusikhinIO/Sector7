#include "enemy.h"

Enemy::Enemy()
    : id_(""),
      name_(""),
      hp_(0),
      max_hp_(0),
      damage_(0),
      description_(""),
      spawn_chance_(100),
      stun_turns_(0) {}

Enemy::Enemy(const std::string& id, const std::string& name, int hp, int damage,
             const std::string& description, int spawn_chance)
    : id_(id),
      name_(name),
      hp_(hp),
      max_hp_(hp),
      damage_(damage),
      description_(description),
      spawn_chance_(spawn_chance),
      stun_turns_(0) {}
