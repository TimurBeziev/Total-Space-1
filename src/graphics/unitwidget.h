#ifndef UNITWIDGET_H
#define UNITWIDGET_H

#include <QApplication>
#include <QScreen>

#include "core/menu.h"
#include "graphics/buttonitem.h"
#include "util/utility.h"

class Planet;

class UnitWidget : public ButtonItem {
  Q_OBJECT
 public:
  UnitWidget(UnitsInteractionMenu* parent, Planet* planet, UnitType unit,
             int32_t width, int32_t height);
  Planet* GetPlanet() const;
  UnitType GetUnit() const;

 protected:
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

 private:
  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;

  void SwitchWidget();
  QColor current_color_ = Qt::black;
  QPixmap active_widget_;
  QPixmap unactive_widget_;
  QPixmap current_widget_ = unactive_widget_;

  QPixmap unit_icon_;

  QString attack_;
  QString armor_;
  QString health_;
  QString stamina_;

  int font_;
  UnitsInteractionMenu* parent_;
  Planet* unit_planet_;

  UnitType cell_unit_;
  const QString caption_;
  bool is_chosen_ = false;
  const int32_t kWidth = qApp->screens()[0]->size().width();
  const int32_t kHeight = qApp->screens()[0]->size().height();
};

#endif  // UNITWIDGET_H
