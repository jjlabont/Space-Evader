#include "Ship.h"

Meteor::Meteor(uint8_t xPosition, uint8_t yPosition):Entity(xPosition, yPosition){};

void Ship::shipMove(int yMove){
   {
      if (yPosition > 0 && yMove == 1) {
        yPosition = yPosition - 1;
      }
      if (yPosition < 25 && yMove == -1) {
        yPosition = yPosition + 1;
      }
    }
}
