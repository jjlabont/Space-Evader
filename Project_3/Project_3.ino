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
int yPos = 0;
//game state
int board[21][4];
int numLoop = 0;


void setup()   {
  //set pinmodes
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(fire, INPUT_PULLUP);

  //put ship at 0,0
  board[0][0] = 1;

  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC);
  //seed random
  randomSeed(analogRead(0));

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Hello World");
  display.display();
  display.clearDisplay();

}

void loop() {

  if (digitalRead(up) == LOW && yPos > 0) {
    board[0][yPos] = 0;
    yPos -= 1;
    board[0][yPos] = 1;
  }
  if (digitalRead(down) == LOW && yPos < 3) {
    board[0][yPos] = 0;
    yPos += 1;
    board[0][yPos] = 1;
  }

  updateBoard();
  printBoard();
  //numLoop += 1;

  if (numLoop <= 10) {
    //int r = 2;
    board[21][2] = 2;
    numLoop = 0;
    display.print("Wtf");
  }
}

void updateBoard() {
  for (int y = 0; y < 4; y++) {
    for (int  x = 0; x < 21; x++) {
      int pos = board[x][y];
      if (pos == 2) {
        board[x][y] = 0;
        if (x - 1 > 0) {
          board[x - 1][y] = 2;
        }
      }
    }
  }
}

void printBoard() {
  display.clearDisplay();
  display.setCursor(0, 0);
  for (int y = 0; y < 4; y++) {
    for (int  x = 0; x < 21; x++) {
      int i = board[x][y];
      if (i == 0) {
        display.print(" ");
      }
      if (i == 1) {
        display.print(">");
      }
      if (i == 2) {
        display.print("O");
      }
    }
  }
  display.display();
  display.clearDisplay();
}
