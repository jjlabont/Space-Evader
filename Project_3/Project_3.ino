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

  //put ship at 0,0
  board[0][0] = 1;

  //begin to display
  Serial.begin(9600);
  display.begin(SSD1306_SWITCHCAPVCC);
  //seed random
  randomSeed(analogRead(0));

  display.setTextSize(1);
  display.setTextColor(WHITE);

  display.clearDisplay();
  //start info
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

int updateBoard() { //updates the board to the next state
  for (int y = 0; y < 4; y++) {
    for (int  x = 0; x < 21; x++) {
      int pos = board[x][y];
      if (pos == 2) { //if position is meteor move it left one space
        board[x][y] = 0; //set old position to be empty
        if (x - 1 >= 0) { // if the meteor doesnt go off the board
          int nx = board[x - 1][y] // move meteor to left one space
          board[x - 1][y] = 2; 
          if (nx == 1) { //if next space is ship you lose
            while (1) { // endgame loop, prints your score
              display.clearDisplay();
              display.setCursor(0, 0);
              display.println("      Game Over");
              display.print("    Your Score: ");
              display.print(meteorsDodged);
              display.display();
            }
          }
        } else { //if meteor goes off board
          meteorsDodged += 1; //meteors dodged increased
          if (interval > 45) { //increase game speed by lowering refreseh increment up to 40ms per refresh
          interval -= 5;
          }
        }
      }
    }
  }
  return 0;
}

int printBoard() { //method to print board to display
  display.clearDisplay(); //guarantee that display is empty (shouldnt matter but is just a safeguard)
  display.setCursor(0, 0); // set curor back to top left
  for (int y = 0; y < 4; y++) {//loops through all xy coordinates
    for (int  x = 0; x < 21; x++) {
      int i = board[x][y];
      if (i == 0) { //if 2d array holds a 0 print an empty space
        display.print(" ");
      }
      if (i == 1) { // if 2d array holds a 1 print the ship >
        display.print(">");
      }
      if (i == 2) { // if 2d aray holds a 2 print a meteor O
        display.print("O");
      }
    }
  }
  display.display();// tells diplay to diplay new image
  display.clearDisplay();// clears display
  return 0;
}

int spawnMeteor(int row) { //spawns meteor in specified row
  board[20][row] = 2;
  return 0;
}

int spawnMeteorBut(int row){ // spawns meteor in every lane EXCEPT the specified row
  board[20][0] = 2;
  board[20][1] = 2;
  board[20][2] = 2;
  board[20][3] = 2;
  board[20][row] = 0;
}
