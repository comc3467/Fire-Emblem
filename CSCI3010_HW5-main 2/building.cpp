#include "building.h"

/**
  Constructor for Building, depends on the string, type
  @param std::string
  returns none
*/
Building::Building(std::string type){
    type_ = type;
    if(type == "castle1"){
        QColor color(16, 17, 18);
        color_ = color;
        player_ = 1;
        currentHealth_ = 50;
    }
    else if(type == "castle2"){
        QColor color(16, 17, 18);
        color_ = color;
        player_ = 2;
        currentHealth_ = 50;
    }
    else if(type == "river"){
        QColor color(0,255,255);
        color_ = color;
        player_ = 0;
    }
    else if(type == "wall"){
        QColor color(16, 17, 18);
        color_ = color;
        player_ = 0;
    }
    else if(type == "chest"){
        QColor color(156, 113, 64);
        color_ = color;
        player_ = 3; //given a specific player number to indicate that we should be able to attack this
    }
}
