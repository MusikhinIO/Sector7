#include "combat_system.h"

#include <iostream>

#include "../core/text_manager.h"

void CombatSystem::ResolveAttack(Player& player, Enemy* enemy, Room* room) {
  if (!enemy || !enemy->IsAlive()) return;

  int player_dmg = player.Damage();

  if (player.IsCharging()) {
    player_dmg *= kChargeDamageMultiplier;
    enemy->AddStunTurns(1);
    std::cout << TextManager::Get("CHARGED_ATTACK_PREFIX") << player_dmg
              << TextManager::Get("CHARGED_ATTACK_SUFFIX") << "\n";
    player.SetCharging(false);
  } else {
    std::cout << TextManager::Get("ATTACK_PREFIX") << player_dmg
              << TextManager::Get("ATTACK_SUFFIX") << "\n";
  }

  enemy->SetHp(enemy->Hp() - player_dmg);

  if (!enemy->IsAlive()) {
    std::cout << enemy->Name() << TextManager::Get("DEFEATED") << "\n";
    room->ClearActiveEnemy();
  } else {
    ProcessEnemyTurn(player, enemy);
  }
}

void CombatSystem::ResolveDefend(Player& player, Enemy* enemy) {
  player.SetDefending(true);
  std::cout << TextManager::Get("DEFEND_MSG") << "\n";
  ProcessEnemyTurn(player, enemy);
}

void CombatSystem::ResolveCharge(Player& player) {
  player.SetCharging(true);
  std::cout << TextManager::Get("CHARGE_MSG") << "\n";
}

void CombatSystem::ResolveInteract(Player& player, Enemy* enemy, Room* room) {
  if (room->EnvAction() == "NONE" || room->IsEnvUsed()) {
    std::cout << TextManager::Get("ENV_NO_USE") << "\n";
    return;
  }

  room->SetEnvUsed(true);

  if (room->EnvAction() == "CABINET") {
    std::cout << TextManager::Get("USE_CABINET_MSG") << "\n";
    enemy->SetHp(enemy->Hp() - 40);
  } else if (room->EnvAction() == "VENT") {
    std::cout << TextManager::Get("USE_VENT_MSG") << "\n";
    player.SetDefending(true);
    return;
  } else if (room->EnvAction() == "STEAM") {
    std::cout << TextManager::Get("USE_STEAM_MSG") << "\n";
    enemy->SetHp(enemy->Hp() - 20);
    enemy->AddStunTurns(2);
    return;
  } else if (room->EnvAction() == "CABLE") {
    std::cout << TextManager::Get("USE_CABLE_MSG") << "\n";
    enemy->SetHp(enemy->Hp() - 25);
    enemy->AddStunTurns(1);
  }

  if (!enemy->IsAlive()) {
    std::cout << enemy->Name() << TextManager::Get("DEFEATED") << "\n";
    room->ClearActiveEnemy();
  } else {
    ProcessEnemyTurn(player, enemy);
  }
}

void CombatSystem::ProcessEnemyTurn(Player& player, Enemy* enemy) {
  if (!enemy || !enemy->IsAlive()) return;

  if (enemy->StunTurns() > 0) {
    std::cout << enemy->Name() << TextManager::Get("ENEMY_STUNNED") << "\n";
    enemy->SetStunTurns(enemy->StunTurns() - 1);
    return;
  }

  int enemy_dmg = enemy->Damage();

  if (player.IsDefending()) {
    int reduced_dmg = static_cast<int>(enemy_dmg * kDefendDamageReduction);
    std::cout << TextManager::Get("DEFEND_PREFIX") << reduced_dmg
              << TextManager::Get("ATTACK_SUFFIX") << "\n";
    player.SetHp(player.Hp() - reduced_dmg);

    int heal = kDefendHealValue;
    if (player.Hp() + heal > player.MaxHp())
      heal = player.MaxHp() - player.Hp();
    player.SetHp(player.Hp() + heal);
    std::cout << TextManager::Get("DEFEND_HEALING") << heal << " HP.\n";

    player.SetDefending(false);
  } else {
    std::cout << enemy->Name() << TextManager::Get("ENENY_ATTACK") << enemy_dmg
              << TextManager::Get("ATTACK_SUFFIX") << "\n";
    player.SetHp(player.Hp() - enemy_dmg);
  }

  std::cout << TextManager::Get("HP_NOW") << player.Hp() << "/"
            << player.MaxHp() << ".\n";

  if (player.Hp() <= 0) {
    std::cout << TextManager::Get("DEATH_MSG") << "\n";
  }
}
