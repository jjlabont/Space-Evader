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
int meteorsDodged = 0;


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
      long r = random(3);
      //single spawn
      if (r == 0) {
        r = random(3);
        spawnMeteor(r);
      }
      //double spawn
      if (r == 1) {
        r = random(3);
        long scnd = random(3);
        while (scnd == r) {
          scnd = random(3);
        }
        spawnMeteor(r);
        spawnMeteor(scnd);
      }
      //triple spawn
      if (r == 2) {
        r = random(3);
        spawnMeteorBut(r);
      }
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
          int nx = board[x - 1][y];
          board[x - 1][y] = 2;
          if (nx == 1) { //if next space is ship you lose
            while (1) {
              display.clearDisplay();
              display.setCursor(0, 0);
              display.println("      Game Over");
              display.print("      Score: ");
              display.print(meteorsDodged);
              display.display();
            }
          }
        } else {
          //spead up game after dodging meteors
          meteorsDodged += 1;
          if (interval > 45) {
          interval -= 5;
          }
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

int spawnMeteor(int row) {
  board[20][row] = 2;
  return 0;
}

int spawnMeteorBut(int row){
  board[20][0] = 2;
  board[20][1] = 2;
  board[20][2] = 2;
  board[20][3] = 2;
  board[20][row] = 0;
}
