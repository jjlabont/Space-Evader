#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

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
//ship characteristics
int yPos = 1;
//game state
int board[4][21];

void setup()   {
  //set pinmodes
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(fire, INPUT_PULLUP);

  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC);
  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Hello Game!");
  display.display();
  delay(1000);
  display.clearDisplay();
}

void loop() {
  if (digitalRead(up) == LOW && yPos > 0) {
    yPos -= 1;
    
  }
  if (digitalRead(down) == LOW && yPos < 3) {
    yPos += 1;
  }

  //printBoard();
}

void printBoard() {
  display.clearDisplay();
  display.setCursor(0, 0);
  char* s;
  for (int y = 0; y < 4; y++) {
    for (int  x = 0; x < 21; x++) {
      char* c = convertInt(board[x][y]);
      s = strcat(s, c);
    }
  }
  
  display.println(s);
  display.display();
  display.clearDisplay();
}

char* convertInt(int i) {
  if (i == 0) {
    return "^";
  }
  if (i == 1) {
    return ">";
  }
  if (i == 2) {
    return "O";
  }
}
