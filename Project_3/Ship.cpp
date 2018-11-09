#include "Ship.h"

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
