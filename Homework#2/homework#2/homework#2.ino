const int buttonPin = 2;
const int buzzerPin = 3;

const int redCarLedPin = 6;
const int yellowCarLedPin = 7;
const int greenCarLedPin = 8;

const int redPeopleLedPin = 11;
const int greenPeopleLedPin = 12;

const int semaphoresState1 = 1;
const int semaphoresState2 = 2;
const int semaphoresState3 = 3;
const int semaphoresState4 = 4;

const int state1DurationAfterPress = 8000;
const int state2Duration = 3000;
const int state3Duration = 8000;
const int state4Duration = 4000;

byte buttonState = HIGH;

byte redCarLedState = LOW;
byte yellowCarLedState = LOW;
byte greenCarLedState = HIGH;

byte redPeopleLedState = HIGH;
byte greenPeopleLedState = LOW;

byte lastReading = LOW;
byte reading = LOW;

int currentSemaphoresState = semaphoresState1;

unsigned long lastDebounceTime = 0;
unsigned int debounceDelay = 50;
unsigned long stageStartTime = 0;
bool buttonPressed = false;

const int buzzerTone = 1000;
const int buzzerTimeStage3 = 1000;
const int buzzerTimeStage4 = 500;
const int buzzerDuration = 200;
unsigned long buzzerStart = 0;

const int blinkDuration = 500;


void setup() {
  pinMode(buttonPin, INPUT_PULLUP);

  pinMode(redCarLedPin, OUTPUT);
  pinMode(yellowCarLedPin, OUTPUT);
  pinMode(greenCarLedPin, OUTPUT);

  pinMode(redPeopleLedPin, OUTPUT);
  pinMode(greenPeopleLedPin, OUTPUT);

  Serial.begin(9600);
}

void loop() {
  debounce();
  if (buttonPressed) {
    switch (currentSemaphoresState) {
      case semaphoresState1:
        state1();
        break;
      case semaphoresState2:
        state2();
        break;
      case semaphoresState3:
        state3();
        break;
      case semaphoresState4:
        state4();
        break;
      default:
        break;
    }
  }
  ledPrinting();
}

void ledPrinting() {
  digitalWrite(redCarLedPin, redCarLedState);
  digitalWrite(yellowCarLedPin, yellowCarLedState);
  digitalWrite(greenCarLedPin, greenCarLedState);

  digitalWrite(redPeopleLedPin, redPeopleLedState);
  digitalWrite(greenPeopleLedPin, greenPeopleLedState);
}

void debounce() {
  reading = digitalRead(buttonPin);

  if (reading != lastReading) {
    lastDebounceTime = millis();
  }
  if ((millis() - lastDebounceTime) > debounceDelay) {
    buttonState = reading;

    if (buttonState == LOW && currentSemaphoresState == semaphoresState1 && !buttonPressed) {
      stageStartTime = millis();
      buttonPressed = true;
    }
  }
  lastReading = reading;
}


void reinitialize() {
  redCarLedState = LOW;
  yellowCarLedState = LOW;
  greenCarLedState = HIGH;

  redPeopleLedState = HIGH;
  greenPeopleLedState = LOW;
}

void state1() {
  redCarLedState = LOW;
  greenCarLedState = HIGH;
  redPeopleLedState = HIGH;
  greenPeopleLedState = LOW;

  if (millis() - stageStartTime >= state1DurationAfterPress) {
    currentSemaphoresState = semaphoresState2;
    stageStartTime = millis();
  }
}

void state2() {
  greenCarLedState = LOW;
  yellowCarLedState = HIGH;

  if (millis() - stageStartTime >= state2Duration) {
    currentSemaphoresState = semaphoresState3;
    stageStartTime = millis();
  }
}

void state3() {
  yellowCarLedState = LOW;
  redCarLedState = HIGH;
  greenPeopleLedState = HIGH;
  redPeopleLedState = LOW;

  if (millis() - buzzerStart >= buzzerTimeStage3) {
    tone(buzzerPin, buzzerTone, buzzerDuration);
    buzzerStart = millis();
  }

  if (millis() - stageStartTime >= state3Duration) {
    currentSemaphoresState = semaphoresState4;
    stageStartTime = millis();
  }
}

void state4() {
  if (millis() - buzzerStart >= blinkDuration) {
    tone(buzzerPin, buzzerTone, buzzerDuration);
    greenPeopleLedState = !greenPeopleLedState;
    buzzerStart = millis();
  }
  
  if (millis() - stageStartTime >= state4Duration) {
    currentSemaphoresState = semaphoresState1;
    buttonPressed = false;
    reinitialize();
  }
}