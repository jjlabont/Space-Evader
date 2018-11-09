#include <stdint.h>
#include "Entity.h"

class Meteor : public Entity
{
    public:
    Meteor(uint8_t xPosition, uint8_t yPosition, uint8_t speed);
    void moveLeft();

    private:
    uint8_t spd;
}
