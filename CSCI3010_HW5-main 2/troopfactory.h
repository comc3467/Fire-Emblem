#ifndef TROOPFACTORY_H
#define TROOPFACTORY_H

#include "troop.h"

class TroopFactory
{
public:
    TroopFactory();
    Troop* createTroop(std::string, int player);
};

#endif // TROOPFACTORY_H
