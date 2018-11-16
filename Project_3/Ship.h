#ifndef SHIP_H
#define SHIP_H

#include "Entity.h"
class Ship: public Entity
{
  public:
    int sprt = 16;
    Ship(uint8_t xPosition, uint8_t yPosition);
    void shipMove(int yMove);
};

#endif
