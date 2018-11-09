#include "Meteor.h"

Meteor::Meteor(uint8_t xPosition, uint8_t yPosition, uint8_t speed)
:Entity(xPosition, yPosition)
{
    spd = speed;
};
