#include "player.h"

Player::Player()
    : name_("Unknown"),
      hp_(100),
      max_hp_(100),
      damage_(10),
      is_defending_(false),
      is_charging_(false) {}

Player::Player(const std::string& name, int hp, int damage)
    : name_(name),
      hp_(hp),
      max_hp_(hp),
      damage_(damage),
      is_defending_(false),
      is_charging_(false) {}

void Player::AddItem(const Item& item) { inventory_.push_back(item); }

bool Player::HasItemOfType(const std::string& type) const {
  for (size_t i = 0; i < inventory_.size(); ++i) {
    if (inventory_[i].Type() == type) {
      return true;
    }
  }
  return false;
}

void Player::RemoveItemOfType(const std::string& type) {
  for (size_t i = 0; i < inventory_.size(); ++i) {
    if (inventory_[i].Type() == type) {
      inventory_.erase(inventory_.begin() + i);
      return;
    }
  }
}
