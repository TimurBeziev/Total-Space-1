#ifndef DRAWER_H
#define DRAWER_H

#include <QObject>
#include <memory>

class GameScene;
class Planet;

class Drawer : public QObject {
  Q_OBJECT
 public:
  Drawer(GameScene *game_scene);

  void DrawPlanet(const std::shared_ptr<Planet>& planet);

 private:
  GameScene *game_scene_;
};

#endif  // DRAWER_H
