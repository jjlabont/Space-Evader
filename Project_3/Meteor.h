#include <stdint.h>
#include "Entity.h"

class Meteor
{
    public:
    uint8_t spd;
    
    Meteor(uint8_t xPosition, uint8_t yPosition, uint8_t speed);
    void moveLeft();
}
