#pragma once

#include "../entities/enemy.h"
#include "../player/player.h"
#include "../world/room.h"

class CombatSystem {
 public:
  static void ResolveAttack(Player& player, Enemy* enemy, Room* room);
  static void ResolveDefend(Player& player, Enemy* enemy);
  static void ResolveCharge(Player& player);
  static void ResolveInteract(Player& player, Enemy* enemy, Room* room);

  static void ProcessEnemyTurn(Player& player, Enemy* enemy);

 private:
  static constexpr float kDefendDamageReduction = 0.4;
  static constexpr int kDefendHealValue = 5;
  static constexpr int kChargeDamageMultiplier = 3;
};
