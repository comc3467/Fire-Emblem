#ifndef RECTANGLE_H
#define RECTANGLE_H

#include <QColor>
#include <QGraphicsItem>
#include <QLabel>

#include "building.h"
#include "troop.h"

// any object that inherits from QObject can emit signals
// things that inherit from QGraphicsItem can be added to QGraphicScenes
class Rectangle : public QObject, public QGraphicsItem{

    // this makes it so that we can emit signals
    Q_OBJECT

public:
    Rectangle(const int x, const int y);  // constructor

    int get_x() const { return x_iteration_; }  // inline member function
    int get_y() const { return y_iteration_; }  // inline member function

//    void AdvanceTurn();

    void ChangeState(std::string state);
    void ChangeState(std::string state, int player);
    void ChangeState(Troop * troop);
    void ChangeState(Troop * troop, int announce);
    void ChangeState(Building * chest); //overloaded just to add the CHEST building
    void CheckPaint(); //this function checks to see if there's a troop, changes accordingly

    bool CheckEmpty();

    QRectF boundingRect() const override;
    QPainterPath shape() const override;


//    QLabel *label = new QLabel(this);
//    label->setFrameStyle(QFrame::Panel | QFrame::Sunken);
//    label->setText("first line\nsecond line");
//    label->setAlignment(Qt::AlignBottom | Qt::AlignRight);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *item, QWidget *widget) override;

    int get_width() { return width_; }

    void set_visited(bool set){visited_ = set;};
    bool get_visited(){ return visited_; };


    bool alive_;

    Building * building_;
    Troop * troop_;

    bool available_; //this is to tell if the player can move their troop there
    bool attackable_; //this is to tell if the player can attack there

    bool moveable_visual_; //this is to tell if we should see a white circle to indicate the block can still move
    bool attackable_visual_; //this is to tell if we should see a red circle to indicate the blok can still attack
signals:



protected:
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
//    void mouseMoveEvent(QMouseEvent *event) override;




private:
  bool visited_ = false;

  int x_; //this keeps pixel information
  int y_;

  int x_iteration_; //this keeps information about where it x and y coordinates basically
  int y_iteration_;




  QColor color_;





  // all our rectangles will be 20 wide and tall (they are squares)
  int width_;

signals:
  void CastleClick(int player);
  void TroopClick(Rectangle * rectangle);
  void MoveClick(Rectangle * rectangle);
  void AttackBuildingClick(Rectangle * rectangle);
  void SpawnClick(Rectangle * rectangle);

  void Announce(std::string message);
  void AnnounceStats();

};  // class rectangle

#endif // RECTANGLE_H

