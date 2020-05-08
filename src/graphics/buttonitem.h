#ifndef BUTTONITEM_H
#define BUTTONITEM_H

#include <QGraphicsItem>
#include <QGraphicsSceneMouseEvent>

#include "util/typeoffset.h"

class ButtonItem : public QObject, public QGraphicsItem {
  Q_OBJECT
  Q_INTERFACES(QGraphicsItem)
 public:
  ButtonItem(int32_t width, int32_t height, bool is_scalable = true);
  void SetPixmap(QPixmap* button_image);

  int type() const override;

  enum {
    Type = UserType + TypeOffset::kButtonItem,
  };

 signals:
  void clicked();

 protected:
  void mouseReleaseEvent(QGraphicsSceneMouseEvent* event) override;

  int32_t width_;
  int32_t height_;

 private:
  QRectF boundingRect() const override;
  void paint(QPainter* painter, const QStyleOptionGraphicsItem* option,
             QWidget* widget) override;

  QPixmap* button_image_;
  bool is_scalable_;
};

#endif  // BUTTONITEM_H
