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
int pressed = 0;
//game state
int board[21][4];
long prevTime = 0;
long interval = 250;
int numUpdates = 0;


void setup()   {
  //set pinmodes
  pinMode(up, INPUT_PULLUP);
  pinMode(down, INPUT_PULLUP);
  pinMode(fire, INPUT_PULLUP);

  //put ship at 0,0
  board[0][0] = 1;
  board[20][2] = 2;
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC);
  //seed random
  randomSeed(analogRead(0));

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.clearDisplay();
  display.setCursor(0, 0);
  display.println("Hello Bworld");
  display.display();
  delay(1000);
  display.clearDisplay();
}

void loop() {
  //get current time
  long currentTime = millis();

  //reads inputs
  if (digitalRead(up) == LOW && yPos > 0 && pressed == 0) {
    board[0][yPos] = 0;
    yPos -= 1;
    board[0][yPos] = 1;
    pressed = 1;
  }
  if (digitalRead(down) == LOW && yPos < 3 && pressed == 0) {
    board[0][yPos] = 0;
    yPos += 1;
    board[0][yPos] = 1;
    pressed = 1;
  }

  if (digitalRead(down) == HIGH && digitalRead(up) == HIGH) {
    pressed = 0;
  }

  //if threshold is passed update board
  if (currentTime - prevTime >= interval) {
    prevTime = currentTime;
    updateBoard();
    numUpdates += 1;
    if (numUpdates >= 12) {
      long r = random(4);
      //board[21][r] = 2;
      numUpdates = 0;
    }
  }

  printBoard();
}

int updateBoard() {
  for (int y = 0; y < 4; y++) {
    for (int  x = 0; x < 21; x++) {
      int pos = board[x][y];
      if (pos == 2) {
        board[x][y] = 0;
        if (x - 1 >= 0) {
          board[x - 1][y] = 2;
        }
      }
    }
  }
  return 0;
}

int printBoard() {
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
  return 0;
}

int spawnMeteor() {
  
}
