#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "Ship.h"
#include "Meteor.h"
#include "Entity.h"

//setting up for OLED display
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

//pin numbers
int up = 4;
int down = 5;
int fire = 3;
//render info
Entity* sprites[20];
int numSprites = 0;
Ship s = Ship(0, 12);

void setup()   {
  //set pinmodes
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(fire, INPUT_PULLUP);

  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC);
  display.setTextSize(1);
  display.setTextColor(WHITE);

  startUp();

  addEntity(s);
}

void loop() {
  s.shipMove();
  render();
}

void render() {
      for (int i = 0; i < numSprites; i++) {
        uint8_t xPos = sprites[i]->xPosition;
        uint8_t yPos = sprites[i]->yPosition;
        int sprite = sprites[i]->sprt;
        display.setCursor(xPos, yPos);
        display.write(sprite);
      }
      display.display();
      display.clearDisplay();
}

void addEntity(Entity* ent) {
      sprites[numSprites] = ent;
      numSprites += 1;
    }

void startUp() {
  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Hello world!");
  display.display();
  delay(1000);
  display.clearDisplay();
}
