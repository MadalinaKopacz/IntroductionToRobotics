const int D1 = 0;

const int displayCount = 4;
const int encodingsNumber = 16;
const byte regSize = 8;  // 1 byte aka 8 bits

const int pinSW = 2;
const int pinX = A0;
const int pinY = A1;

const int segD1 = 7;
const int segD2 = 6;
const int segD3 = 5;
const int segD4 = 4;

const int positive = 1;
const int negative = -1;

const byte dpOnForState2 = 1;
const int minValue = 0;
const int maxValueDisplayCount = displayCount - 1;
const int maxValueEncodingsNumber = encodingsNumber - 1;

const unsigned long blinkDuration = 300;
const unsigned long resetTime = 3000;
unsigned long lastBlinkTime = 0;

unsigned long lastJoyDebounceTime = 0;
const unsigned long debounceJoyDelay = 100;
bool lastJoyMoved = false;

bool transitioned = false;
bool shouldTransition = false;

const unsigned long debounceDelay = 100;
bool buttonPressed = false;
bool shortPress = false;

unsigned long pressedDebounceTime = 0;
unsigned long releasedDebounceTime = 0;

unsigned long start = 0;
byte readingPress = LOW;

const int state1 = 1;
const int state2 = 2;
int currentState = state1;

int valueState = 0;
int joyMovement = 0;
bool joyMoved = false;

int minThreshold = 400;
int maxThreshold = 600;

int byteEncodings[encodingsNumber] = {
  //A B C D E F G DP
  B11111100,  // 0
  B01100000,  // 1
  B11011010,  // 2
  B11110010,  // 3
  B01100110,  // 4
  B10110110,  // 5
  B10111110,  // 6
  B11100000,  // 7
  B11111110,  // 8
  B11110110,  // 9
  B11101110,  // A
  B00111110,  // b
  B10011100,  // C
  B01111010,  // d
  B10011110,  // E
  B10001110   // F
};

int displayDigits[displayCount] = {
  segD1, segD2, segD3, segD4
};

int displayNumbers[displayCount] = {
  0, 0, 0, 0
};

const int clockPin = 10;
const int latchPin = 11;
const int dataPin = 12;

int currentDPState = true;
byte dpEncodingValue = 1;
int encodingValue = 0;

int currentDisplayIndex = D1;
int currentDisplayNumber = 0;


void setup() {
  pinMode(pinSW, INPUT_PULLUP);

  pinMode(latchPin, OUTPUT);
  pinMode(clockPin, OUTPUT);
  pinMode(dataPin, OUTPUT);

  for (int i = 0; i < displayCount; i++) {
    pinMode(displayDigits[i], OUTPUT);
    digitalWrite(displayDigits[i], HIGH);
  }

  Serial.begin(9600);
}

void loop() {
  setUpCurrentState();
  buttonPress();
  changeStates();
}

void setUpCurrentState() {
  if (currentState == state1) {
    blink();
    joyMove(pinX, maxValueDisplayCount, currentDisplayIndex);
  } else {
    joyMove(pinY, maxValueEncodingsNumber, displayNumbers[currentDisplayIndex]);
  }
  activateDisplay();
}

void blink() {
  if (millis() - lastBlinkTime > blinkDuration) {
    lastBlinkTime = millis();
    currentDPState = !currentDPState;
    dpEncodingValue = !dpEncodingValue;
  }
}

void changeStates() {
  if (buttonPressed) {
    if (shortPress) {
      if (currentState == state1) {
        currentState = state2;
        buttonPressed = false;
      } else {
        currentState = state1;
        buttonPressed = false;
      }
    } else if (currentState == state1) {
      if (millis() - start > resetTime) {
        buttonPressed = false;
        reinitialize();
      } else {
        shortPress = false;
      }
    }
  }
}

void buttonPress() {
  readingPress = digitalRead(pinSW);
  if (!readingPress) {
    if (millis() - pressedDebounceTime > debounceDelay) {
      buttonPressed = true;
      shortPress = false;
      start = millis();
    }
    pressedDebounceTime = millis();
  } else {
    if (millis() - releasedDebounceTime > debounceDelay) {
      shortPress = true;
    }
    releasedDebounceTime = millis();
  }
}

void writeReg(byte encoding) {
  digitalWrite(latchPin, LOW);
  byte msb = B0;

  for (int i = 0; i < regSize; i++) {
    msb = bitRead(encoding, regSize - i - 1);
    digitalWrite(clockPin, LOW);
    digitalWrite(dataPin, msb);
    digitalWrite(clockPin, HIGH);
  }
  digitalWrite(latchPin, HIGH);
}

void activateDisplay() {
  for (int i = 0; i < displayCount; ++i) {
    writeEncoding(i);
    turnOnAndOffDisplay(displayDigits[i]);
  }
}

void writeEncoding(const int displayIndex) {
  encodingValue = byteEncodings[displayNumbers[displayIndex]];
  if (displayIndex == currentDisplayIndex) {
    if (currentDPState) {
      encodingValue = encodingValue ^ dpEncodingValue;
    } else if (currentState == state2) {
      encodingValue = encodingValue ^ dpOnForState2;
    }
  }
  writeReg(encodingValue);
}

void turnOnAndOffDisplay(const int display) {
  digitalWrite(display, LOW);
  delay(1);
  digitalWrite(display, HIGH);
}


void joyMove(const int pin, const int maxValue, int& modifiedValue) {
  valueState = analogRead(pin);

  joyMoved = false;
  joyMovement = 0;

  if (valueState > maxThreshold) {
    joyMovement = positive;
    joyMoved = true;
  }
  if (valueState < minThreshold) {
    joyMovement = negative;
    joyMoved = true;
  }
  if (joyMoved != lastJoyMoved) {
    lastJoyDebounceTime = millis();
  }
  if ((millis() - lastJoyDebounceTime) > debounceJoyDelay) {
    shouldTransition = joyMoved;
  }
  lastJoyMoved = joyMoved;

  if (shouldTransition && !transitioned) {
    modifiedValue += joyMovement;
    modifiedValue = max(modifiedValue, minValue);
    modifiedValue = min(modifiedValue, maxValue);
  }
  transitioned = shouldTransition;
}

void reinitialize() {
  for (int i = 0; i < displayCount; ++i) {
    displayNumbers[i] = minValue;
  }
  currentDisplayIndex = D1;
}