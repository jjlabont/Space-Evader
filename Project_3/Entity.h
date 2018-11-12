#ifndef ENTITY_H
#define ENTITY_H

#include <stdint.h>

class Entity
{
  public:
    uint8_t xPosition;
    uint8_t yPosition;
    Entity(uint8_t xPos, uint8_t yPos);
    protected:
    int sprt;
    
};
#endif
