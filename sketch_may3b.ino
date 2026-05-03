#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

// ONLY REAL WORKING LAYOUT (2 rows effectively used)
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'*','7','4','1'},
  {'0','8','5','2'},
  {'X','X','X','X'}, // ignored row
  {'X','X','X','X'}  // ignored row
};

byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 9};

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// SYSTEM VARIABLES
int studyTime = 10;
int breakTime = 5;
int rounds = 1;

bool paused = false;

void setup() {
  lcd.init();
  lcd.backlight();

  showUI();
}

void loop() {

  char key = keypad.getKey();

  if (!key) return;

  // ignore broken readings
  if (key == 'X') return;

  handleKey(key);
}

// ---------------- INPUT MAP ----------------
void handleKey(char key) {

  // STUDY +1
  if (key == '7') {
    studyTime++;
    showUI();
  }

  // STUDY -1
  if (key == '4') {
    studyTime--;
    if (studyTime < 1) studyTime = 1;
    showUI();
  }

  // BREAK +1
  if (key == '8') {
    breakTime++;
    showUI();
  }

  // BREAK -1
  if (key == '5') {
    breakTime--;
    if (breakTime < 1) breakTime = 1;
    showUI();
  }

  // ROUNDS (0 cycles 1→5)
  if (key == '0') {
    rounds++;
    if (rounds > 5) rounds = 1;
    showUI();
  }

  // PAUSE
  if (key == '2') {
    paused = !paused;
    showUI();
  }

  // RESET
  if (key == '*') {
    studyTime = 10;
    breakTime = 5;
    rounds = 1;
    paused = false;
    showUI();
  }
}

// ---------------- UI ----------------
void showUI() {

  lcd.clear();

  lcd.setCursor(0,0);
  lcd.print("S:");
  lcd.print(studyTime);
  lcd.print(" B:");
  lcd.print(breakTime);

  lcd.setCursor(0,1);
  lcd.print("R:");
  lcd.print(rounds);
  lcd.print(" P:");
  lcd.print(paused ? "Y" : "N");
}