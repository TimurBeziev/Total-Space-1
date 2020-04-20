#ifndef OBJECTSSTORAGE_H
#define OBJECTSSTORAGE_H

#include <QString>
#include <map>
#include <memory>

#include "util/utility.h"

class EconomicBuilding;
class WarBuilding;
class Unit;

class ObjectsStorage {
public:
  ObjectsStorage() = delete;

  static void AddBuilding(const EconomicBuilding* building);
  static void AddBuilding(const WarBuilding* building);
  static void AddUnit(const Unit* unit);

private:
  static const std::map<QString, EconomicBuildingType>
      economic_caption_to_type_;
  static const std::map<QString, WarBuildingType> war_caption_to_type_;
  static const std::map<QString, UnitType> unit_caption_to_type_;

  static std::map<EconomicBuildingType, const EconomicBuilding *>
      type_to_economic_building_;
  static std::map<WarBuildingType, const WarBuilding *> type_to_war_building_;
  static std::map<UnitType, const Unit *> type_to_unit_;
};

#endif // OBJECTSSTORAGE_H
