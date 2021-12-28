#include "troop.h"
#include "troopfactory.h"

/**
  Constructor for TroopFactory
  @param none
  returns none
*/
TroopFactory::TroopFactory()
{

}
/**
  createTroop is the main function for the factory method
  @param std::string name, int player
  returns Troop* that has been created
*/
Troop* TroopFactory::createTroop(std::string name, int player) {
    if(name == "infantry"){
        return new Infantry(player);
    }
    else if(name == "knight"){
        return new Knight(player);
    }
    else if(name == "archer"){
        return new Archer(player);
    }
    else if(name == "wizard"){
        return new Wizard(player);
    }
    else{
        return new Assassin(player);
    }
}
