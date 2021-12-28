#include <cstdlib>
#include <ctime>
#include <cmath>
#include <iostream>
#include <QtWidgets>

#include "rectangle.h"

/**
  Creates a new Rectangle object with coordinates x and y
  @param: x int x coordinate, int y coordinate, int rectangle_width, bool infected_bool (should we be checking if it's infected or not)

*/
Rectangle::Rectangle(const int x, const int y) {

  this->width_ = 25; //7 because it's 525 x 525, so 75 squares width 7 fits perfectly
  QColor color(255, 255, 255);
  this->color_ = color;
  alive_ = true; //this block is alive

  x_ = x;
  y_ = y;

  x_iteration_ = (x/25);
  y_iteration_ = 23-(y/25); //this is the jazz we need to make these made the board seem like a coordinate plane, with origin bottom left

  building_ = nullptr;
  troop_ = nullptr;

  available_ = false; //only used to mean a troop can travel there

  moveable_visual_ = false;
  attackable_visual_ = false;

}

/**
  Slot that responds to clicking on the node, handles the changing of the node's state upon clock
  @param QGraphicsSceneMouseEvent *event, 'the click'
  returns nothing
*/
//in recctanlge.cpp
void Rectangle::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if(this->available_){ //meaing we said we could move here, the player just clicked it
        emit MoveClick(this);
    }
    else if(this->building_ != nullptr){
        qDebug() << "Hello clicked!";
        if(this->attackable_){ //WE only get here if the building is to be attacked
            emit AttackBuildingClick(this);
        }
        else if(this->building_->type_ == "castle1"){
            qDebug() << "castle1";
            emit CastleClick(1);
        }
        else if(this->building_->type_ == "castle2"){
            qDebug() << "castle2";
            emit CastleClick(2);
        }
    }
    else if(this->troop_ != nullptr){
        qDebug() << "Troop clicked!";
        emit TroopClick(this);
    }
    qDebug() << "point clicked!";

    update();

}

/**
  Function to change the state of the rectangle – handles a LOT of changes
  @param std::string state
  returns none
*/
void Rectangle::ChangeState(std::string state){
    if(state == "castle1" || state == "castle2"){
        this->available_ = false;
        Building * temp = new Building(state);
        this->building_ = temp;
        this->color_ = temp->get_color();
        this->attackable_ = false;
    }if(state == "river"){
        this->available_ = false;
        Building * temp = new Building(state);
        this->building_ = temp;
        this->color_ = temp->get_color();
    }
    else if(state == "wall"){
        this->available_ = false;
        this->attackable_ = false;
        Building * temp = new Building(state);
        this->building_ = temp;
        this->color_ = temp->get_color();
    }
    else if(state == "chest"){
        this->available_ = false;
        this->attackable_ = false;
        Building * temp = new Building(state);
        this->building_ = temp;
        this->color_ = temp->get_color();
    }
    else if(state == "wizard"){
        this->available_ = false;
        Wizard * temp = new Wizard(1);
        this->troop_ = temp;
        this->color_ = temp->get_color();
    }
    else if(state == "knight"){
        this->available_ = false;
        Knight * temp = new Knight(1);
        this->troop_ = temp;
        this->color_ = temp->get_color();
    }
    else if(state == "empty"){
        this->building_ = nullptr;
        this->troop_ = nullptr;
        this->available_ = false;
        this->attackable_ = false;
        QColor color(255, 255, 255);
        this->color_ = color;
    }
    else if(state == "refresh castle"){
        this->attackable_ = false;
        QColor color(16, 17, 18);
        this->color_ = color;
    }
    else if(state == "dead"){
        emit Announce(std::to_string(this->troop_->get_player()) + "'s " + this->troop_->get_name() + " died in battle");
        this->building_ = nullptr;
        this->troop_ = nullptr;
        this->available_ = false;
        this->attackable_ = false;
        QColor color(255, 255, 255);
        this->color_ = color;
    }
    else if(state == "open"){
        this->available_ = true;
        QColor color(175, 220, 250);
        this->color_ = color;
    }

    //we already know for the moveables and attackables, it will 100% be a troop

    else if(state == "moveable_visual_"){
        this->moveable_visual_ = true;
        this->color_ = this->troop_->get_color();
    }
    else if(state == "not moveable_visual_"){
        this->moveable_visual_ = false;
        this->color_ = this->troop_->get_color();
    }
    else if(state == "attackable_visual_"){
        this->attackable_visual_ = true;
        this->color_ = this->troop_->get_color();
    }
    else if(state == "not attackable_visual_"){
        this->attackable_visual_ = false;
        this->color_ = this->troop_->get_color();
    }

    //it was around now i became a tad annoyed with how I decided to organize the change state...

    else if(state == "attackable"){
        qDebug() << "Within attackable portion";
        if(this->troop_ != nullptr){ //we have already checked, this troop will belong to a different player
            this->attackable_ = true;
            this->color_ =  this->troop_->get_color(); //... just needs to call paint function again...
        }
        else if(this->building_ != nullptr && this->building_->player_ != 0){
            this->attackable_ = true;
            this->color_ =  this->building_->get_color(); //... just needs to call paint function again...
        }
        else{
            this->color_ = QColor(230, 90, 129);
        }
    }
    update();
}

/**
  Overloaded function to change the state of the rectangle – handles actually very little changes
  @param std::string state, int player
  returns none
*/
void Rectangle::ChangeState(std::string state, int player){ //overloaded such that we call when we definitely want a troop – allows for creation in duelBoard setup
    if(state == "wizard"){
        this->available_ = false;
        Wizard * temp = new Wizard(player);
        this->troop_ = temp;
        this->color_ = temp->get_color();
    }
    else if(state == "knight"){
        this->available_ = false;
        Knight * temp = new Knight(player);
        this->troop_ = temp;
        this->color_ = temp->get_color();
    }
    else if(state == "infantry"){
        this->available_ = false;
        Infantry * temp = new Infantry(player);
        this->troop_ = temp;
        this->color_ = temp->get_color();
    }
    else if(state == "archer"){
        this->available_ = false;
        Archer * temp = new Archer(player);
        this->troop_ = temp;
        this->color_ = temp->get_color();
    }
    else if(state == "assassin"){
        this->available_ = false;
        Assassin * temp = new Assassin(player);
        this->troop_ = temp;
        this->color_ = temp->get_color();
    }
    update();
}

/**
  Overloaded function to change the state of the rectangle – handles a lot of changes when we just want to change a spot to having a troop
  @param Troop* troop
  returns none
*/
void Rectangle::ChangeState(Troop * troop){
    this->available_ = false;
    this->attackable_ = false; //important refresher!!
    this->troop_ = troop;
    this->color_ = troop->get_color();
    update();
}
/**
  Overloaded function to change the state of the rectangle – handles changes and announces that this player spawned – used for spawning
  @param Troop* troop, int announce
  returns none
*/
void Rectangle::ChangeState(Troop * troop, int announce){
    this->available_ = false;
    this->attackable_ = false; //important refresher!!
    this->troop_ = troop;
    this->color_ = troop->get_color();
    if(announce){
        if(troop->get_name() == "Archer" || troop->get_name() == "Infantry" || troop->get_name() == "Assassin"){
            this->Announce("Player " + std::to_string(troop->get_player()) + " spawned an " + troop->get_name() + " at their castle");
        }
        else{
            this->Announce("Player " + std::to_string(troop->get_player()) + " spawned a " + troop->get_name() + " at their castle");
        }
    }
    update();
}

/**
  Overloaded function to change the state of the rectangle – handles changing to a chest building
  @param std::string state, int player
  returns none
*/
void Rectangle::ChangeState(Building *chest){
    this->building_ = chest;
    this->attackable_ = false; //important refresher!!
    this->troop_ = nullptr;
    this->color_ = building_->get_color();
    update();
}

//void Rectangle::CheckPaint(){
//    if(troop_ != nullptr){
//        this->color_ = troop_->color_;
//    }
//}

/**
  Function that returns true if it's got neither building nor troop
  @param none
  returns bool
*/
bool Rectangle::CheckEmpty(){
    if(this->troop_ == nullptr && this->building_ == nullptr){
        return true;
    }
    else{
        return false;
    }
}


//void Rectangle::Kill(){
//    this->troop_ = nullptr;
//    this->ChangeState()
//}



/**
  Helps create the rectangle, bounds it's location and gives a rectangle to work with
  @param none
  returns QRectF
*/
// where is this object located
// always a rectangle, Qt uses this to know "where" the user
// would be interacting with this object
QRectF Rectangle::boundingRect() const
{
    return QRectF(x_, y_, width_, width_);
}

/**
  Painting function that helps with creation of rectangle/ color
  @param none
  returns QPainterPath
*/
// define the actual shape of the object
QPainterPath Rectangle::shape() const
{
    QPainterPath path;
    path.addRect(x_, y_, width_, width_);
    return path;
}


/**
  Painting function that actually paints the object
  @param QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget – everything needed to paint
  returns nothing
*/
// called by Qt to actually display the point
void Rectangle::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    Q_UNUSED(widget);


    QBrush b = painter->brush();
    // update the line for setBrush to be this
    painter->setBrush(QBrush(color_));

    painter->drawRect(QRect(this->x_, this->y_, this->width_, this->width_));
    painter->setBrush(b);

    if(this->troop_ != nullptr){
        if(this->troop_->get_player() == 1){
            painter->drawEllipse((this->x_+3),(this->y_+3), width_-6, width_-6);

        }
        else{
            painter->drawLine(this->x_,this->y_, this->x_+width_, this->y_+width_);
            painter->drawLine(this->x_,this->y_+width_, this->x_+width_, this->y_);
        }

        if(this->attackable_){
            painter->setBrush(QBrush(QColor(230, 90, 129))); //colors a red circle...
            painter->drawEllipse((this->x_+5),(this->y_+5), width_-10, width_-10);
        }
        if(this->moveable_visual_){
            painter->setBrush(QBrush(QColor(255,250,250))); //colors a white circle...
            painter->drawEllipse((this->x_+5),(this->y_+5), width_-10, width_-10);
        }
        else if(this->attackable_visual_){
            painter->setBrush(QBrush(QColor(50, 168, 82))); //colors a green circle...
            painter->drawEllipse((this->x_+5),(this->y_+5), width_-10, width_-10);
        }
    }
    else if(this->building_ != nullptr){
        if(this->attackable_){
            painter->setBrush(QBrush(QColor(230, 90, 129))); //colors a red circle...
            painter->drawEllipse((this->x_+5),(this->y_+5), width_-10, width_-10);
        }
    }
}
