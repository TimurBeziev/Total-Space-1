#ifndef PLAYERBASE_H
#define PLAYERBASE_H

#include <QObject>
#include <memory>

#include "util/utility.h"

class Planet;
class Unit;

class PlayerBase {
 public:
  enum class Type {
    kPlayer,
    kBot,
  };

  explicit PlayerBase(Planet* planet);
  PlayerBase() = default;
  PlayerBase(Planet* planet, Type type, const QString& color);

  const Resources& GetResources() const;
  int32_t GetTools() const;
  int32_t GetBatteries() const;

  void UpdateResources();

  void AddPlanet(Planet* planet);
  void RemovePlanet(Planet* planet);

  const QVector<Planet*>& GetPlanets() const;
  int64_t GetArmyPower() const;
  void IncreasePower(int32_t power);

  Type GetType();
  const QString& GetColor();

  virtual void Next() = 0;

 private:
  Resources resources_;
  int64_t army_power_ = 0;
  QVector<Planet*> planets_;

  Type type_;
  QString color_;
};

#endif  // PLAYERBASE_H
