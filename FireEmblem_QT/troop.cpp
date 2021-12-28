#include "troop.h"

Troop::Troop()
{

}

/**
  Constructor for Infantry, depends on the player, int
  @param int player
  returns none
*/
Infantry::Infantry(int player){
    name_ = "Infantry";
    currentHealth_ = 10;
    maxHealth_ = 10;
    speed_ = 3;
    attack_ = 3;
    defense_ = 3;
    tiles_ = 6;
    QColor color(146, 176, 137);
    color_ = color;

    range_ = 1;

    player_ = player;

    moved_ = false;
    attacked_ = false;
}

/**
  Constructor for Knight, depends on the player, int
  @param int player
  returns none
*/
Knight::Knight(int player){
    name_ = "Knight";
    currentHealth_ = 10;
    maxHealth_ = 10;
    speed_ = 0;
    attack_ = 6;
    defense_ = 8;
    tiles_ = 4;
    QColor color(140, 146, 156);
    color_ = color;

    range_ = 1;

    player_ = player;

    moved_ = false;
    attacked_ = false;
}

/**
  Constructor for Archer, depends on the player, int
  @param int player
  returns none
*/
Archer::Archer(int player){
    name_ = "Archer";
    currentHealth_ = 10;
    maxHealth_ = 10;
    speed_ = 3;
    attack_ = 2;
    defense_ = 2;
    tiles_ = 4;
    QColor color(184, 139, 201);
    color_ = color;

    range_ = 4;

    player_ = player;

    moved_ = false;
    attacked_ = false;
}

/**
  Constructor for Wizard, depends on the player, int
  @param int player
  returns none
*/
Wizard::Wizard(int player){
    name_ = "Wizard";
    currentHealth_ = 10;
    maxHealth_ = 10;
    speed_ = 1;
    attack_ = 7;
    defense_ = 2;
    tiles_ = 3;
    QColor color(66, 135, 245);
    color_ = color;

    range_ = 2;

    player_ = player;

    moved_ = false;
    attacked_ = false;
}

/**
  Constructor for Assassin, depends on the player, int
  @param int player
  returns none
*/
Assassin::Assassin(int player){
    name_ = "Assassin";
    currentHealth_ = 1;
    maxHealth_ = 1;
    speed_ = 10;
    attack_ = 10;
    defense_ = 2;
    tiles_ = 10;
    QColor color(133, 185, 201);
    color_ = color;

    range_ = 1;

    player_ = player;

    moved_ = false;
    attacked_ = false;
}


