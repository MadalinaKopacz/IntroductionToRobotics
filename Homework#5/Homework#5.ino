#include <LedControl.h>
#include <LiquidCrystal.h>
#include <EEPROM.h>

const byte RS = 9;
const byte enable = 8;

const byte d4 = 7;
const byte d5 = 6;
const byte d6 = 5;
const byte d7 = 4;

LiquidCrystal lcd(RS, enable, d4, d5, d6, d7);

const int dinPin = 12;
const int clockPin = 11;
const int loadPin = 10;

const int xPin = A0;
const int yPin = A1;
const int swPin = 2;

const int minRow = 0;
const int maxRow = 8;
const int minCol = 0;
const int maxCol = 8;

const unsigned long blinkDuration = 300;
const unsigned long resetTime = 3000;
unsigned long lastBlinkTime = 0;
unsigned long score = 0;
unsigned long highscore = 0;
unsigned long oldHighscore = 0;
unsigned long maximumScore = 5;
unsigned long last = 0;
unsigned long lastFinishGameTime = 0;

LedControl lc = LedControl(dinPin, clockPin, loadPin, 1);

byte matrixBrightness = 2;

byte xPos = 0;
byte yPos = 0;

byte xLastPos = 0;
byte yLastPos = 0;

byte newFoodPosX = -1;
byte newFoodPosY = -1;
byte needFood = true;

const int minThreshold = 200;
const int maxThreshold = 600;

const byte moveInterval = 100;
unsigned long long lastMoved = 0;

unsigned long startGameTime = 0;
unsigned long finishGameTime = 0;
unsigned long time = 0;
unsigned long currentGameTime = 0;

const byte matrixSize = 8;
bool matrixChanged = true;
bool goToAction = false;
uint16_t characterCursor = 0;

byte matrix[matrixSize][matrixSize] = {
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0 }
};

byte matrixByte[matrixSize] = {
  B00000000,
  B01000100,
  B00101000,
  B00010000,
  B00010000,
  B00010000,
  B00000000,
  B00000000
};

unsigned long long greetDuration = 3000;
bool cleared = 0;

const byte upArrow = 0;
const byte downArrow = 1;
const short int cat = 2;


int xValue = 0;
bool joyMoved = false;

unsigned long lastJoyDebounceTime = 0;
const unsigned long debounceJoyDelay = 100;
bool lastJoyMoved = false;
bool transitioned = false;
bool shouldTransition = false;

short int direction = 0;
const short int up = -1;
const short int down = 1;

const unsigned long debounceDelay = 100;
bool buttonPressed = false;
bool shortPress = false;

int buttonState;
int lastButtonState = HIGH;

unsigned long lastDebounceTime = 0;
unsigned long start = 0;
byte readingPress = LOW;
unsigned long pressedDebounceTime = 0;
unsigned long releasedDebounceTime = 0;

const char instructions[] = "Use the joystick to move. Eat the blinking dot. Press the joystick to go back.";
const char about1[] = "GAME NAME: A Dabloon Story";
const char about2[] = "AUTHOR: Madalina-Elena Kopacz";
const char about3[] = "GITHUB: https://github.com/MadalinaKopacz/";

unsigned short int menuOption = 1;
unsigned short int aboutOption = 1;
unsigned short int highScoreOption = 1;

bool shouldDisplayFinish1 = true;

bool gameCanRun = true;

byte customDownArrow[] = {
  B00000,
  B00000,
  B00000,
  B11111,
  B01110,
  B00100,
  B00000,
  B00000
};

byte customUpArrow[] = {
  B00000,
  B00000,
  B00100,
  B01110,
  B11111,
  B00000,
  B00000,
  B00000
};

byte customCat[] = {
  B11011,
  B10001,
  B00000,
  B01010,
  B00000,
  B10101,
  B01110,
  B00000
};

const unsigned int hsAddress[] = { 0, 32, 64, 96, 128 };

struct playerHighScore {
  char name[6] = "N/A";
  unsigned int score = 0;
};

char currentName[6] = "Play";
unsigned long startDisplay1Time = millis();
unsigned short int difficulty = 1;

void setup() {
  Serial.begin(9600);

  lc.shutdown(0, false);
  lc.setIntensity(0, matrixBrightness);
  lc.clearDisplay(0);

  matrix[xPos][yPos] = 1;

  randomSeed(analogRead(0));

  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);

  lcd.createChar(upArrow, customUpArrow);
  lcd.home();
  lcd.createChar(downArrow, customDownArrow);
  lcd.home();
  lcd.createChar(cat, customCat);
  lcd.home();

  pinMode(swPin, INPUT_PULLUP);
  // initializeHighScoreEeprom();
}


void loop() {
  greet();
}

void updateByteMatrix() {
  for (int row = 0; row < matrixSize; row++) {
    lc.setRow(0, row, matrixByte[row]);
  }
}
void updateMatrix() {
  for (int row = 0; row < matrixSize; row++) {
    for (int col = 0; col < matrixSize; col++) {
      lc.setLed(0, row, col, matrix[row][col]);
    }
  }
}

void updatePositions() {
  int xValue = analogRead(xPin);
  int yValue = analogRead(yPin);

  xLastPos = xPos;
  yLastPos = yPos;
  if (xValue < minThreshold) {
    if (xPos < matrixSize - 1) {
      xPos++;
    } else {
      xPos = 0;
    }
  }
  if (xValue > maxThreshold) {
    if (xPos > 0) {
      xPos--;
    } else {
      xPos = matrixSize - 1;
    }
  }

  if (yValue > maxThreshold) {
    if (yPos < matrixSize - 1) {
      yPos++;
    } else {
      yPos = 0;
    }
  }

  if (yValue < minThreshold) {
    if (yPos > 0) {
      yPos--;
    } else {
      yPos = matrixSize - 1;
    }
  }
  if (xPos != xLastPos || yPos != yLastPos) {
    matrixChanged = true;
    matrix[xLastPos][yLastPos] = 0;
    matrix[xPos][yPos] = 1;
  }
}

void blink() {
  if (millis() - lastBlinkTime > blinkDuration) {
    lastBlinkTime = millis();
    matrix[newFoodPosX][newFoodPosY] = !matrix[newFoodPosX][newFoodPosY];
    lc.setLed(0, newFoodPosX, newFoodPosY, matrix[newFoodPosX][newFoodPosY]);
  }
}

void collision() {
  if (newFoodPosX == xPos && newFoodPosY == yPos) {
    score++;
    needFood = true;
    matrixChanged = true;
  }

  matrix[xPos][yPos] = 1;
  lc.setLed(0, newFoodPosX, newFoodPosY, matrix[newFoodPosX][newFoodPosY]);
}

void generateFood() {
  newFoodPosX = random(minRow, maxRow);
  newFoodPosY = random(minCol, maxCol);

  if (newFoodPosX == xPos && newFoodPosY == yPos) {
    generateFood();
  }

  matrix[newFoodPosX][newFoodPosY] = 1;
  matrixChanged = true;

  needFood = false;
}

void displayPartialMessage(char* text) {
  uint8_t ind = 0;
  while (ind < 16) {
    if (!text[ind]) {
      break;
    }
    lcd.print((char)text[ind]);
    ind++;
  }
  while (ind < 16) {
    lcd.print(" ");
    ind++;
  }
}

void displayWholeMessage(char* text) {
  if (millis() > last + 500) {
    last = millis();

    if (text[characterCursor]) {
      displayPartialMessage(text + characterCursor);
      characterCursor++;
    } else {
      characterCursor = 0;
    }
  }
}

void greet() {
  if (millis() <= greetDuration) {
    lcd.setCursor(0, 0);
    lcd.print("HELLO, TRAVELER!");
  } else {
    if (!cleared) {
      lcd.clear();
      cleared = 1;
    }
    if (!goToAction) {
      scrollMenu(1, 5, menuOption);
      menu();
      pressButtonInMenu(true);
    } else {
      actionAfterPress();
      pressButtonInMenu(false);
    }
  }
}

void pressButtonInMenu(const bool givenGoToAction) {
  buttonPress();
  if (buttonPressed) {
    lcd.clear();
    goToAction = givenGoToAction;
    buttonPressed = false;
    if (!givenGoToAction && menuOption == 1) {
      closeGame();
    }
    if (givenGoToAction && menuOption == 1) {
      score = 0;
      gameCanRun = true;
      startGameTime = millis();
      shouldDisplayFinish1 = true;
    }
    if (givenGoToAction && (menuOption == 3 || menuOption == 4 || menuOption == 5)) {
      characterCursor = 0;
    }
    if (!givenGoToAction && menuOption == 3) {
      highScoreOption = 1;
    }
    if (!givenGoToAction && menuOption == 5) {
      aboutOption = 1;
    }
  }
}

void closeGame() {
  for (int row = 0; row < matrixSize; row++) {
    for (int col = 0; col < matrixSize; col++) {
      matrix[row][col] = 0;
    }
  }
  updateMatrix();
  xPos = 0;
  yPos = 0;
  needFood = 1;
}

void scoreCloseGame() {
  if (score > highscore) {
    oldHighscore = highscore;
    highscore = score;
  }
  playerHighScore smallestHighScore;
  EEPROM.get(hsAddress[4], smallestHighScore);
  if (score > smallestHighScore.score) {
    updateHighScores();
  }
}

void menu() {
  // set the cursor:
  switch (menuOption) {
    case 1:
      {
        lcd.setCursor(0, 0);
        lcd.print("A Dabloon Story");
        lcd.setCursor(15, 0);
        lcd.write(cat);
        lcd.setCursor(0, 1);
        lcd.print("> Start Game");

        lcd.setCursor(15, 1);
        lcd.write(downArrow);
        break;
      }
    case 2:
      {
        lcd.setCursor(0, 0);
        lcd.print("> Settings");
        lcd.setCursor(2, 1);
        lcd.print("Highscore");

        lcd.setCursor(15, 0);
        lcd.write(upArrow);
        lcd.setCursor(15, 1);
        lcd.write(downArrow);
        break;
      }
    case 3:
      {
        lcd.setCursor(0, 0);
        lcd.print("> Highscore");
        lcd.setCursor(2, 1);
        lcd.print("How to play");

        lcd.setCursor(15, 0);
        lcd.write(upArrow);
        lcd.setCursor(15, 1);
        lcd.write(downArrow);
        break;
      }
    case 4:
      {
        lcd.setCursor(0, 0);
        lcd.print("> How to play");
        lcd.setCursor(2, 1);
        lcd.print("About");

        lcd.setCursor(15, 0);
        lcd.write(upArrow);
        lcd.setCursor(15, 1);
        lcd.write(downArrow);
        break;
      }
    case 5:
      {
        lcd.setCursor(2, 0);
        lcd.print("How to play");
        lcd.setCursor(0, 1);
        lcd.print("> About");

        lcd.setCursor(15, 0);
        lcd.write(upArrow);
        break;
      }
  }
}

void game() {
  //  updateByteMatrix();
  if (gameCanRun) {

    updateMatrix();
    if (needFood) {
      generateFood();
    }
    if (millis() - lastMoved > moveInterval) {
      updatePositions();
      lastMoved = millis();
    }
    if (matrixChanged == true) {
      updateMatrix();
      matrixChanged = false;
    }
    blink();
    collision();
    if (score >= maximumScore) {
      gameCanRun = false;
      cleared = false;
      closeGame();
      scoreCloseGame();
    }
    currentGameTime = millis();
    displayPlayingGame();
  } else {
    displayFinishScreens();
  }
}

void displayFinishScreen1() {
  if (!cleared) {
    lcd.clear();
    cleared = 1;
  }
  char buffer[7];
  itoa(score, buffer, 10);
  char message[50] = "Congratulations on reaching score ";
  strcat(message, buffer);
  displayWholeMessage(message);

  lcd.setCursor(0, 1);
  lcd.print("Top: ");

  if (millis() >= currentGameTime + 13000) {
    lastFinishGameTime = millis();
    shouldDisplayFinish1 = false;
    cleared = false;
  }
}

void displayFinishScreen2() {
  if (!cleared) {
    lcd.clear();
    cleared = 1;
  }
  char buffer[7] = "";
  itoa(score, buffer, 10);
  char message1[10] = "Score:";
  strcat(message1, buffer);

  if (score > oldHighscore) {
    strcat(message1, " NEW HIGHSCORE!");
    displayWholeMessage(message1);
  } else {
    lcd.setCursor(0, 0);
    lcd.print(message1);
  }

  time = (finishGameTime - startGameTime) / 1000;

  itoa(time, buffer, 10);
  char message2[15] = "Time:";
  strcat(message2, buffer);

  lcd.setCursor(0, 1);
  lcd.print(message2);
}

void displayPlayingGame() {
  if (!cleared) {
    lcd.clear();
    cleared = 1;
  }

  char message0[15] = "Hello, ";
  strcat(message0, currentName);
  lcd.setCursor(0,0);
  lcd.print(message0);

  char buffer[7] = "";
  itoa(score, buffer, 10);
  char message1[10] = "S:";
  strcat(message1, buffer);
  lcd.setCursor(0, 1);
  lcd.print(message1);

  time = (currentGameTime - startGameTime) / 1000;
  itoa(time, buffer, 10);
  char message2[15] = "T:";
  strcat(message2, buffer);
  lcd.setCursor(8, 1);
  lcd.print(message2);
}

void displayFinishScreens() {
  if (shouldDisplayFinish1) {
    displayFinishScreen1();

  } else {
    displayFinishScreen2();
  }
}

void scrollMenu(const unsigned short int minBoundary, const unsigned short int maxBoundary, unsigned short int& option) {
  xValue = analogRead(xPin);
  joyMoved = 0;
  direction = 0;

  if (xValue < minThreshold) {
    if (option < maxBoundary) {
      joyMoved = true;
      direction = down;
    }
  }
  if (xValue > maxThreshold) {
    if (option > minBoundary) {
      joyMoved = true;
      direction = up;
    }
  }

  if (joyMoved != lastJoyMoved) {
    lastJoyDebounceTime = millis();
  }
  if ((millis() - lastJoyDebounceTime) > debounceJoyDelay) {
    shouldTransition = joyMoved;
  }
  lastJoyMoved = joyMoved;

  if (shouldTransition && !transitioned) {
    option += direction;
    lcd.clear();
    characterCursor = 0;
  }
  transitioned = shouldTransition;
}

void buttonPress() {
  readingPress = digitalRead(swPin);
  if (readingPress != lastButtonState) {
    lastDebounceTime = millis();
  }
  if (millis() - lastDebounceTime > debounceDelay) {
    if (readingPress != buttonState) {
      buttonState = readingPress;

      if (buttonState == LOW) {
        buttonPressed = true;
      }
    }
  }
  lastButtonState = readingPress;
}

void actionAfterPress() {
  switch (menuOption) {
    case 1:
      {
        lcd.setCursor(0, 0);
        game();
        break;
      }
    case 2:
      {
        lcd.setCursor(0, 0);
        lcd.print("Settings");
        break;
      }
    case 3:
      {
        lcd.setCursor(0, 0);
        lcd.print("HighScores");
        scrollMenu(1, 5, highScoreOption);
        showHighScores();
        break;
      }
    case 4:
      {
        lcd.setCursor(0, 0);
        lcd.print("How to play?");
        lcd.setCursor(0, 1);
        displayWholeMessage(instructions);
        break;
      }
    case 5:
      {
        lcd.setCursor(0, 0);
        lcd.print("About");
        scrollMenu(1, 3, aboutOption);
        aboutOptions(aboutOption);
        break;
      }
  }
}

void aboutOptions(short int aboutOption) {
  switch (aboutOption) {
    case 1:
      {
        lcd.setCursor(15, 0);
        lcd.write(downArrow);
        lcd.setCursor(0, 1);
        displayWholeMessage(about1);
        break;
      }
    case 2:
      {
        lcd.setCursor(14, 0);
        lcd.write(upArrow);
        lcd.setCursor(15, 0);
        lcd.write(downArrow);
        lcd.setCursor(0, 1);
        displayWholeMessage(about2);
        break;
      }
    case 3:
      {
        lcd.setCursor(15, 0);
        lcd.write(upArrow);
        lcd.setCursor(0, 1);
        displayWholeMessage(about3);
        break;
      }
  }
}

void initializeHighScoreEeprom() {
  playerHighScore highScores[5];
  for (int i = 0; i < 5; i++) {
    EEPROM.put(hsAddress[i], highScores[i]);
  }
}

void updateHighScores() {
  playerHighScore highScores[5];
  for (int i = 0; i < 5; i++) {
    EEPROM.get(hsAddress[i], highScores[i]);
  }
  short int position;
  playerHighScore currentHighScore;
  strcpy(currentHighScore.name, currentName);
  currentHighScore.score = score;

  for (int i = 0; i < 5; i++) {
    if (score > highScores[i].score) {
      position = i;
      break;
    }
  }
  Serial.println("position");
  Serial.println(position);
  for (int i = 4; i > position; i--) {
    EEPROM.put(hsAddress[i], highScores[i - 1]);
  }
  EEPROM.put(hsAddress[position], currentHighScore);
}

void showHighScores() {
  playerHighScore highScores[5];
  for (int i = 0; i < 5; i++) {
    EEPROM.get(hsAddress[i], highScores[i]);
  }
  switch (highScoreOption) {
    case 1:
      {
        lcd.setCursor(15, 0);
        lcd.write(downArrow);
        lcd.setCursor(0, 1);
        lcd.print("1.");
        lcd.setCursor(3, 1);
        lcd.print(highScores[highScoreOption - 1].score);
        lcd.setCursor(10, 1);
        lcd.print(highScores[highScoreOption - 1].name);
        break;
      }
    case 2:
      {
        lcd.setCursor(14, 0);
        lcd.write(upArrow);
        lcd.setCursor(15, 0);
        lcd.write(downArrow);
        lcd.setCursor(0, 1);
        lcd.print("2.");
        lcd.setCursor(3, 1);
        lcd.print(highScores[highScoreOption - 1].score);
        lcd.setCursor(10, 1);
        lcd.print(highScores[highScoreOption - 1].name);
        break;
      }
    case 3:
      {
        lcd.setCursor(14, 0);
        lcd.write(upArrow);
        lcd.setCursor(15, 0);
        lcd.write(downArrow);
        lcd.setCursor(0, 1);
        lcd.print("3.");
        lcd.setCursor(3, 1);
        lcd.print(highScores[highScoreOption - 1].score);
        lcd.setCursor(10, 1);
        lcd.print(highScores[highScoreOption - 1].name);
        break;
      }
    case 4:
      {
        lcd.setCursor(14, 0);
        lcd.write(upArrow);
        lcd.setCursor(15, 0);
        lcd.write(downArrow);
        lcd.setCursor(0, 1);
        lcd.print("4.");
        lcd.setCursor(3, 1);
        lcd.print(highScores[highScoreOption - 1].score);
        lcd.setCursor(10, 1);
        lcd.print(highScores[highScoreOption - 1].name);
        break;
      }
    case 5:
      {
        lcd.setCursor(15, 0);
        lcd.write(upArrow);
        lcd.setCursor(0, 1);
        lcd.print("5.");
        lcd.setCursor(3, 1);
        lcd.print(highScores[highScoreOption - 1].score);
        lcd.setCursor(10, 1);
        lcd.print(highScores[highScoreOption - 1].name);
        break;
      }
  }
}