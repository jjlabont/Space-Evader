#include "Meteor.h"

Meteor::Meteor(uint8_t xPosition, uint8_t yPosition, uint8_t mSpeed)
:Entity(xPosition, yPosition)
{
    spd = mSpeed;
};
