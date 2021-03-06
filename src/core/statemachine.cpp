#include "core/statemachine.h"

#include <memory>

#include "core/keyhandler.h"
#include "core/menu.h"
#include "core/menugraph.h"
#include "mainwindow.h"
#include "objects/planet.h"
#include "objects/player.h"
#include "scene/gamescene.h"
#include "scene/gameview.h"

// -----------------------------------------------------------

Controller::MenuType Controller::current_state_ = Controller::MenuType::kMain;
int Controller::kMenuCount = 10;

MainMenu* Controller::main_menu_ = nullptr;
ShopMenu* Controller::shop_menu_ = nullptr;
UnitMenu* Controller::unit_menu_ = nullptr;
AttackMenu* Controller::attack_menu_ = nullptr;
MoveMenu* Controller::move_menu_ = nullptr;
PauseMenu* Controller::pause_menu_ = nullptr;
PlanetInfoMenu* Controller::planet_info_menu_ = nullptr;
PlanetMenu* Controller::planet_menu_ = nullptr;
GameMenu* Controller::game_menu_ = nullptr;
SettingsMenu* Controller::settings_menu_ = nullptr;
std::shared_ptr<KeyHandler> Controller::key_handler_ = nullptr;

GameView* Controller::view = nullptr;

Planet* Controller::active_planet_ = nullptr;

GameScene* Controller::scene = nullptr;
MainWindow* Controller::window = nullptr;

std::unique_ptr<MenuGraph> Controller::menu_graph_ = nullptr;

// -----------------------------------------------------------

void Controller::SwitchMenu(MenuType menu) {
  switch (current_state_) {
    case MenuType::kGame:
      game_menu_->SwitchTo(menu);
      break;
    case MenuType::kMain:
      main_menu_->SwitchTo(menu);
      break;
    case MenuType::kPause:
      pause_menu_->SwitchTo(menu);
      break;
    case MenuType::kPlanet:
      planet_menu_->SwitchTo(menu);
      break;
    case MenuType::kAttack:
      attack_menu_->SwitchTo(menu);
      break;
    case MenuType::kMove:
      move_menu_->SwitchTo(menu);
      break;
    case MenuType::kShop:
      shop_menu_->SwitchTo(menu);
      break;
    case MenuType::kPlanetInfo:
      planet_info_menu_->SwitchTo(menu);
      break;
    case MenuType::kSettings:
      settings_menu_->SwitchTo(menu);
      break;
    default:
      break;
  }
}

void Controller::LoadMenuGraph() {
  QVector<QVector<MenuType>> connections(kMenuCount);

  connections[static_cast<int>(MenuType::kMain)] = {MenuType::kGame,
                                                    MenuType::kSettings};
  connections[static_cast<int>(MenuType::kGame)] = {
      MenuType::kPlanet, MenuType::kPause, MenuType::kMain};

  connections[static_cast<int>(MenuType::kPlanet)] = {
      MenuType::kGame, MenuType::kAttack, MenuType::kMove,
      MenuType::kPlanetInfo, MenuType::kShop};
  connections[static_cast<int>(MenuType::kPlanetInfo)] = {MenuType::kPlanet};
  connections[static_cast<int>(MenuType::kAttack)] = {MenuType::kPlanet};
  connections[static_cast<int>(MenuType::kMove)] = {MenuType::kPlanet};
  connections[static_cast<int>(MenuType::kPause)] = {
      MenuType::kMain, MenuType::kGame, MenuType::kSettings};

  connections[static_cast<int>(MenuType::kSettings)] = {MenuType::kPause,
                                                        MenuType::kMain};

  connections[static_cast<int>(MenuType::kShop)] = {MenuType::kPlanet};
  menu_graph_ = std::make_unique<MenuGraph>(kMenuCount, connections);
}

const MenuGraph* Controller::Graph() { return menu_graph_.get(); }

void Controller::SetMenuType(MenuType next_state) {
  current_state_ = next_state;
}

Controller::MenuType Controller::GetMenuType() { return current_state_; }

// !!! WARNING !!!
// GAME MENU должно удаляться последним !!!
void Controller::Destroy() {
  Controller::SetPlanetMenu(nullptr);
  Controller::SetShopMenu(nullptr);
  Controller::SetUnitMenu(nullptr);
  Controller::SetAttackMenu(nullptr);
  Controller::SetMoveMenu(nullptr);
  Controller::SetPlanetInfoMenu(nullptr);
  Controller::SetPauseMenu(nullptr);
  Controller::SetMainMenu(nullptr);
  Controller::SetSettingsMenu(nullptr);
  Controller::SetGameMenu(
      nullptr);  // ! эта строка должна идти последней всегда
}

Planet* Controller::GetActivePlanet() { return active_planet_; }

void Controller::SetActivePlanet(Planet* planet) { active_planet_ = planet; }

MainMenu* Controller::GetMainMenu() { return main_menu_; }

UnitMenu* Controller::GetUnitMenu() { return unit_menu_; }

AttackMenu* Controller::GetAttackMenu() { return attack_menu_; }

MoveMenu* Controller::GetMoveMenu() { return move_menu_; }

PlanetInfoMenu* Controller::GetPlanetInfoMenu() { return planet_info_menu_; }

PauseMenu* Controller::GetPauseMenu() { return pause_menu_; }

PlanetMenu* Controller::GetPlanetMenu() { return planet_menu_; }

GameMenu* Controller::GetGameMenu() { return game_menu_; }

SettingsMenu* Controller::GetSettingsMenu() { return settings_menu_; }

ShopMenu* Controller::GetShopMenu() { return shop_menu_; }

Controller::MenuType Controller::GetCurrentState() { return current_state_; }

void Controller::SetMainMenu(MainMenu* menu) {
  delete (main_menu_);
  main_menu_ = menu;
}

void Controller::SetUnitMenu(UnitMenu* menu) {
  delete (unit_menu_);
  unit_menu_ = menu;
}

void Controller::SetAttackMenu(AttackMenu* menu) {
  delete (attack_menu_);
  attack_menu_ = menu;
}

void Controller::SetMoveMenu(MoveMenu* menu) {
  delete (move_menu_);
  move_menu_ = menu;
}

void Controller::SetPlanetInfoMenu(PlanetInfoMenu* menu) {
  delete (planet_info_menu_);
  planet_info_menu_ = menu;
}

void Controller::SetPauseMenu(PauseMenu* menu) {
  delete (pause_menu_);
  pause_menu_ = menu;
}

void Controller::SetPlanetMenu(PlanetMenu* menu) {
  delete (planet_menu_);
  planet_menu_ = menu;
}

void Controller::SetGameMenu(GameMenu* menu) {
  delete (game_menu_);
  game_menu_ = menu;
}

void Controller::SetSettingsMenu(SettingsMenu* menu) {
  delete (settings_menu_);
  settings_menu_ = menu;
}

KeyHandler* Controller::GetKeyHandler() { return key_handler_.get(); }

void Controller::CreateKeyHandler() {
  key_handler_ = std::make_shared<KeyHandler>();
}

void Controller::SetShopMenu(ShopMenu* menu) {
  delete (shop_menu_);
  shop_menu_ = menu;
}
