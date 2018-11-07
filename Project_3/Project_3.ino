#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// If using software SPI (the default case):
#define OLED_MOSI   9
#define OLED_CLK   10
#define OLED_DC    11
#define OLED_CS    12
#define OLED_RESET 13
Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);

uint8_t yPos = 12;
int up = 4;
int down = 5;
int fire = 3;

void setup()   {
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(fire, INPUT_PULLUP);
  Serial.begin(9600);

  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 0);
  display.println("Hello world!");
  display.display();
  delay(1000);
  display.clearDisplay();
}

void loop() {
  shipMove();
}

void shipMove() {
  if (yPos > 0 && digitalRead(up) == LOW) {
    yPos = yPos - 1;
  }
  if (yPos < 25 && digitalRead(down) == LOW) {
    yPos = yPos + 1;
  }
  display.setCursor(0, yPos);
  display.write(16);
  display.display();
  display.clearDisplay();
}

class entity
{
  public:
    uint8_t xPosition = 0;
    uint8_t yPosition = 0;
    int sprt = 16;

    entity(uint8_t xPos, uint8_t yPos, int sprite) {
      xPosition = xPos;
      yPosition = yPos;
      sprt = sprite;
    }
};

class renderer
{
  public:
    entity* sprites[20];
    int numSprites = 0;

    renderer() {
    }

    void addEntity(entity* ent) {
      sprites[numSprites] = ent;
      numSprites += 1;
    }

    void update() {
      for (int i = 0; i < numSprites; i++) {
        uint8_t xPos = sprites[i]->xPosition;
        uint8_t yPox = sprites[i]->yPosition;

      }
    }

};
