#include "game.h"

#include <algorithm>

Game::Game() : is_running_(false), current_room_id_("") {}

bool Game::Initialize() {
  TextManager::LoadStrings("data/strings.txt");
  if (!Parser::ParseItems("data/items.txt", items_)) return false;
  if (!Parser::ParseEnemies("data/enemies.txt", enemies_)) return false;
  if (!Parser::ParseRooms("data/rooms.txt", rooms_)) return false;

  std::cout << TextManager::Get("SYS_INIT") << "\n";

  const std::string kStartRoomId = "R01";
  bool start_room_found = false;
  for (size_t i = 0; i < rooms_.size(); ++i) {
    if (rooms_[i].Id() == kStartRoomId) {
      current_room_id_ = kStartRoomId;
      start_room_found = true;
      break;
    }
  }

  if (!start_room_found) {
    std::cerr << "Critical error: Start room '" << kStartRoomId
              << "' not found. Exiting.\n";
    return false;
  }

  for (size_t i = 0; i < rooms_.size(); ++i) {
    if (rooms_[i].EnemyId() != Parser::kEmptyValue) {
      Enemy* template_enemy = FindEnemyById(rooms_[i].EnemyId());
      if (template_enemy) {
        rooms_[i].SetActiveEnemy(*template_enemy);
        if ((std::rand() % 100) >= template_enemy->SpawnChance()) {
          rooms_[i].ClearActiveEnemy();
        }
      }
    }

    if (rooms_[i].ItemId() != Parser::kEmptyValue) {
      Item* item = FindItemById(rooms_[i].ItemId());
      if (item && (std::rand() % 100) >= item->SpawnChance()) {
        rooms_[i].SetItemId(Parser::kEmptyValue);
      }
    }
  }

  player_ = Player("Инженер", 100, 10);

  is_running_ = true;
  std::cout << TextManager::Get("SYS_WELCOME") << "\n";
  std::cout << TextManager::Get("SYS_HELP_HINT") << "\n\n";
  std::cout << "|" << TextManager::Get("SYS_LORE_THREAT") << "\n";
  std::cout << "|" << TextManager::Get("SYS_LORE_EVAC") << "\n";
  std::cout << "|" << TextManager::Get("SYS_LORE_LEAVE") << "\n";

  return true;
}

void Game::Run() {
  while (is_running_) {
    Look();
    std::cout << "\n> ";

    std::string command;
    std::getline(std::cin, command);

    ProcessCommand(command);
  }
}

Room* Game::GetCurrentRoom() {
  for (size_t i = 0; i < rooms_.size(); ++i) {
    if (rooms_[i].Id() == current_room_id_) {
      return &rooms_[i];
    }
  }
  return nullptr;
}

Enemy* Game::FindEnemyById(const std::string& id) {
  for (size_t i = 0; i < enemies_.size(); ++i) {
    if (enemies_[i].Id() == id) {
      return &enemies_[i];
    }
  }
  return nullptr;
}

Item* Game::FindItemById(const std::string& id) {
  for (size_t i = 0; i < items_.size(); ++i) {
    if (items_[i].Id() == id) {
      return &items_[i];
    }
  }
  return nullptr;
}

void Game::ProcessCommand(const std::string& command) {
  std::string cmd = ToLower(command);

  if (cmd == "help" || cmd == "h") {
    PrintHelp();
  } else if (cmd == "look" || cmd == "l") {
    Look();
  } else if (cmd == "stats") {
    Stats();
  } else if (cmd == "inventory" || cmd == "i") {
    ShowInventory();
  } else if (cmd == "go north" || cmd == "n") {
    Go("North");
  } else if (cmd == "go south" || cmd == "s") {
    Go("South");
  } else if (cmd == "go east" || cmd == "e") {
    Go("East");
  } else if (cmd == "go west" || cmd == "w") {
    Go("West");
  } else if (cmd == "attack" || cmd == "a") {
    Attack();
  } else if (cmd == "defend" || cmd == "d") {
    Defend();
  } else if (cmd == "charge" || cmd == "c") {
    Charge();
  } else if (cmd == "use env") {
    Interact();
  } else if (cmd == "take" || cmd == "t") {
    TakeItem();
  } else if (cmd.find("use ") == 0) {
    std::string num_str = cmd.substr(4);
    try {
      int item_num = std::stoi(num_str);
      UseItem(item_num);
    } catch (const std::exception&) {
      std::cout << TextManager::Get("USE_INVALID_INPUT") << "\n";
    }
  } else if (cmd == "quit" || cmd == "q") {
    std::cout << TextManager::Get("SYS_QUIT") << "\n";
    is_running_ = false;
  } else {
    std::cout << TextManager::Get("CMD_UNKNOWN") << "\n";
  }
}

void Game::PrintHelp() const {
  std::cout
      << "=== СПРАВОЧНАЯ СИСТЕМА ТЕРМИНАЛА ===\n"
      << "  stats          - Состояние игрока\n"
      << "  look (l)       - Осмотреть сектор\n"
      << "  go [dir] (n,s,e,w) - Идти на север, юг, восток, запад\n"
      << "  take (t)       - Подобрать предмет в комнате\n"
      << "  use [index]    - Использовать предмет из инвентаря\n"
      << "  inventory (i)  - Показать инвентарь\n"
      << "--- БОЕВЫЕ ПРОТОКОЛЫ ---\n"
      << "  attack (a)     - Атаковать врага\n"
      << "  defend (d)     - Встать в защиту (-60% урона, +5 HP)\n"
      << "  charge (c)     - Накопление урона (пропуск хода, x3 урон, стан)\n"
      << "  use env        - Использовать окружение\n"
      << "--- СИСТЕМА ---\n"
      << "  help (h)       - Вызвать эту справку\n"
      << "  quit (q)       - Выйти из игры\n";
}

void Game::Stats() const {
  std::cout << TextManager::Get("STATS_HEADER") << "\n";
  std::cout << TextManager::Get("STATS_NAME") << player_.Name() << "\n";
  std::cout << TextManager::Get("STATS_HP") << player_.Hp() << " / "
            << player_.MaxHp() << "\n";
  std::cout << TextManager::Get("STATS_DMG") << player_.Damage() << "\n";
}

void Game::ShowInventory() const {
  std::cout << TextManager::Get("INV_HEADER") << "\n";
  const std::vector<Item>& inv = player_.Inventory();

  if (inv.empty()) {
    std::cout << TextManager::Get("INV_EMPTY") << "\n";
  } else {
    for (size_t i = 0; i < inv.size(); ++i) {
      std::cout << "  [" << (i + 1) << "] " << inv[i].Name() << " | "
                << inv[i].Description() << "\n";
    }
  }
}

void Game::Look() {
  Room* room = GetCurrentRoom();
  if (!room) return;

  std::cout << "\n=== " << room->Name() << " ===\n";
  std::cout << room->Description() << "\n";

  if (room->EnemyId() != Parser::kEmptyValue) {
    Enemy* enemy = room->GetActiveEnemy();
    if (enemy) {
      std::cout << TextManager::Get("ROOM_ENEMY_WARNING") << enemy->Name()
                << "\n";
      std::cout << "  " << enemy->Description() << " (HP: " << enemy->Hp()
                << "/" << enemy->MaxHp() << ")\n";
    }
  }

  if (room->ItemId() != Parser::kEmptyValue) {
    Item* item = FindItemById(room->ItemId());
    if (item) {
      std::cout << TextManager::Get("ROOM_ITEM_WARNING") << item->Name()
                << ".\n";
      std::cout << "  " << item->Description() << "\n";
    }
  }

  std::cout << TextManager::Get("ROOM_EXITS_HEADER");
  bool has_exits = false;
  if (room->NorthId() != Parser::kEmptyValue) {
    std::cout << TextManager::Get("DIR_NORTH");
    has_exits = true;
  }
  if (room->SouthId() != Parser::kEmptyValue) {
    std::cout << TextManager::Get("DIR_SOUTH");
    has_exits = true;
  }
  if (room->EastId() != Parser::kEmptyValue) {
    std::cout << TextManager::Get("DIR_EAST");
    has_exits = true;
  }
  if (room->WestId() != Parser::kEmptyValue) {
    std::cout << TextManager::Get("DIR_WEST");
    has_exits = true;
  }

  if (!has_exits) std::cout << TextManager::Get("DIR_NULL");
  std::cout << "\n";
}

void Game::Go(const std::string& direction) {
  Room* room = GetCurrentRoom();
  if (!room) return;

  if (room->EnemyId() != Parser::kEmptyValue) {
    Enemy* enemy = room->GetActiveEnemy();
    if (enemy && enemy->IsAlive()) {
      std::cout << TextManager::Get("MOVE_BLOCKED_PREFIX") << enemy->Name()
                << TextManager::Get("MOVE_BLOCKED_SUFFIX") << "\n";
      return;
    }
  }

  std::string next_room_id = "";
  if (direction == "North")
    next_room_id = room->NorthId();
  else if (direction == "South")
    next_room_id = room->SouthId();
  else if (direction == "East")
    next_room_id = room->EastId();
  else if (direction == "West")
    next_room_id = room->WestId();

  if (next_room_id != Parser::kEmptyValue) {
    current_room_id_ = next_room_id;
    std::cout << TextManager::Get("MOVE_SUCCESS") << "\n";
  } else {
    std::cout << TextManager::Get("MOVE_INVALID_DIR") << "\n";
  }
}

void Game::Attack() {
  Room* room = GetCurrentRoom();
  if (!room || !room->HasActiveEnemy()) {
    std::cout << TextManager::Get("NO_ENEMY_MSG") << "\n";
    return;
  }

  Enemy* enemy = room->GetActiveEnemy();
  CombatSystem::ResolveAttack(player_, enemy, room);

  if (player_.Hp() <= 0) {
    is_running_ = false;
  }
}

void Game::Defend() {
  Room* room = GetCurrentRoom();
  if (!room || !room->HasActiveEnemy()) {
    std::cout << TextManager::Get("NO_ENEMY_MSG") << "\n";
    return;
  }
  Enemy* enemy = room->GetActiveEnemy();
  CombatSystem::ResolveDefend(player_, enemy);

  if (player_.Hp() <= 0) is_running_ = false;
}

void Game::Charge() {
  Room* room = GetCurrentRoom();
  if (!room || !room->HasActiveEnemy()) {
    std::cout << TextManager::Get("NO_ENEMY_MSG") << "\n";
    return;
  }
  CombatSystem::ResolveCharge(player_);

  Enemy* enemy = room->GetActiveEnemy();
  CombatSystem::ProcessEnemyTurn(player_, enemy);

  if (player_.Hp() <= 0) is_running_ = false;
}

void Game::Interact() {
  Room* room = GetCurrentRoom();
  if (!room || !room->HasActiveEnemy()) {
    std::cout << TextManager::Get("NO_ENV_MSG") << "\n";
    return;
  }
  Enemy* enemy = room->GetActiveEnemy();
  CombatSystem::ResolveInteract(player_, enemy, room);

  if (player_.Hp() <= 0) is_running_ = false;
}

void Game::TakeItem() {
  Room* room = GetCurrentRoom();
  if (!room) return;

  if (room->ItemId() == Parser::kEmptyValue) {
    std::cout << TextManager::Get("NO_ROOM_ITEM") << "\n";
    return;
  }

  Item* item = FindItemById(room->ItemId());
  if (item) {
    player_.AddItem(*item);
    std::cout << "Вы подобрали: " << item->Name() << ".\n";
    room->SetItemId(Parser::kEmptyValue);
  }
}

void Game::UseItem(int item_index) {
  std::vector<Item>& inv = player_.Inventory();
  int idx = item_index - 1;

  if (idx < 0 || idx >= static_cast<int>(inv.size())) {
    std::cout << TextManager::Get("ITEM_NOT_FOUND") << "\n";
    return;
  }

  Item item = inv[idx];

  if (item.Type() == "HEAL") {
    int new_hp = player_.Hp() + item.Value();
    if (new_hp > player_.MaxHp()) new_hp = player_.MaxHp();
    player_.SetHp(new_hp);
    std::cout << TextManager::Get("USED_MSG") << item.Name()
              << TextManager::Get("HP_RESTORED_TO") << player_.Hp() << ".\n";
    inv.erase(inv.begin() + idx);

  } else if (item.Type() == "WEAPON") {
    player_.SetDamage(player_.Damage() + item.Value());
    std::cout << TextManager::Get("WEAPON_EQUIPPED") << item.Name()
              << TextManager::Get("DAMAGE_NOW") << player_.Damage() << ".\n";
    inv.erase(inv.begin() + idx);

  } else if (item.Type() == "KEY") {
    Room* room = GetCurrentRoom();
    if (room && room->Id() == "R20") {
      std::cout << TextManager::Get("USE_KEYCARD") << "\n"
                << TextManager::Get("VICTORY_MSG") << "\n";
      is_running_ = false;
      inv.erase(inv.begin() + idx);

    } else {
      std::cout << TextManager::Get("KEYCARD_WRONG_ROOM") << "\n";
    }
  }
}

std::string Game::ToLower(std::string str) const {
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str;
}
