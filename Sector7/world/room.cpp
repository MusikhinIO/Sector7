#include "room.h"

Room::Room()
    : id_(""),
      name_(""),
      description_(""),
      north_id_(""),
      south_id_(""),
      east_id_(""),
      west_id_(""),
      enemy_id_(""),
      item_id_(""),
      env_action_("") {}

Room::Room(const std::string& id, const std::string& name,
           const std::string& description, const std::string& north_id,
           const std::string& south_id, const std::string& east_id,
           const std::string& west_id, const std::string& enemy_id,
           const std::string& item_id, const std::string& env_action)
    : id_(id),
      name_(name),
      description_(description),
      north_id_(north_id),
      south_id_(south_id),
      east_id_(east_id),
      west_id_(west_id),
      enemy_id_(enemy_id),
      item_id_(item_id),
      env_action_(env_action) {}
