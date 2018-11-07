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
int up = 5;
int down = 4;

void setup()   { 
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  Serial.begin(9600);
  
  // by default, we'll generate the high voltage from the 3.3v line internally! (neat!)
  display.begin(SSD1306_SWITCHCAPVCC);
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
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

class enitity
{
  public:
  uint8_t xPosition;
  uint8_t yPosition;
};
