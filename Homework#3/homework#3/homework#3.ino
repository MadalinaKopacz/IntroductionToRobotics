const int segSize = 8;
const int A = 0;
const int B = 1;
const int C = 2;
const int D = 3;
const int E = 4;
const int F = 5;
const int G = 6;
const int DP = 7;

const int up = 0;
const int right = 1;
const int down = 2;
const int left = 3;

const int pinSW = 2;
const int pinX = A0;
const int pinY = A1;

const int pinA = 4;
const int pinB = 5;
const int pinC = 6;
const int pinD = 7;
const int pinE = 8;
const int pinF = 9;
const int pinG = 10;
const int pinDP = 11;

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

int xValueState1 = 0;
int yValueState1 = 0;
int nextLedPosition;
bool joyMoved = false;

int xValueState2 = 0;

int minThreshold = 400;
int maxThreshold = 600;
int currentLed = DP;


int segmentsPins[segSize] = {
  pinA, pinB, pinC, pinD, pinE, pinF, pinG, pinDP
};

byte segmentsStates[segSize] = {
  LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW
};

byte currentLedState = LOW;

int transitionsMatrix[segSize][4] = {
  //Up, Right, Down, Left
  { A, B, G, F },     // A  0
  { A, B, G, F },     // B  1
  { G, DP, D, E },    // C  2
  { G, C, D, E },     // D  3
  { G, C, D, E },     // E  4
  { A, B, G, F },     // F  5
  { A, G, D, G },     // G  6
  { DP, DP, DP, C },  // DP 7
};

void setup() {
  for (int i = 0; i < segSize; ++i) {
    pinMode(segmentsPins[i], OUTPUT);
  }
  pinMode(pinSW, INPUT_PULLUP);

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
    transition();
  } else {
    freezeSegment();
  }
}

void blink() {
  for (int i = 0; i < segSize; ++i) {
    if (i == currentLed) {
      continue;
    }
    digitalWrite(segmentsPins[i], segmentsStates[i]);
  }
  if (millis() - lastBlinkTime > blinkDuration) {
    digitalWrite(segmentsPins[currentLed], currentLedState);
    lastBlinkTime = millis();
    currentLedState = !currentLedState;
  }
}

void transition() {
  xValueState1 = analogRead(pinX);
  yValueState1 = analogRead(pinY);

  joyMoved = false;

  if (xValueState1 > maxThreshold) {
    nextLedPosition = left;
    joyMoved = true;
  }
  if (xValueState1 < minThreshold) {
    nextLedPosition = right;
    joyMoved = true;
  }
  if (yValueState1 > maxThreshold) {
    nextLedPosition = up;
    joyMoved = true;
  }
  if (yValueState1 < minThreshold) {
    nextLedPosition = down;
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
    currentLed = transitionsMatrix[currentLed][nextLedPosition];
  }
  transitioned = shouldTransition;
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
      }
      else {
        shortPress = false;
      }
    }
  }
}

void freezeSegment() {
  xValueState2 = analogRead(pinX);
  if (xValueState2 > maxThreshold)
    segmentsStates[currentLed] = LOW;
  if (xValueState2 < minThreshold)
    segmentsStates[currentLed] = HIGH;
  digitalWrite(segmentsPins[currentLed], segmentsStates[currentLed]);
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

void reinitialize() {
  for (int i = 0; i < segSize; ++i)
    segmentsStates[i] = LOW;
  currentLed = DP;
}