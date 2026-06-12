#include "item.h"

Item::Item()
    : id_(""),
      name_(""),
      type_(""),
      value_(0),
      description_(""),
      spawn_chance_(100) {}

Item::Item(const std::string& id, const std::string& name,
           const std::string& type, int value, const std::string& description,
           int spawn_chance)
    : id_(id),
      name_(name),
      type_(type),
      value_(value),
      description_(description),
      spawn_chance_(spawn_chance) {}
