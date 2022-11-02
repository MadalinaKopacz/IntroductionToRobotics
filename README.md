
# Introduction to Robotics (2022 - 2023)


Introduction to Robotics laboratory homeworks, taken in the 3rd year at the **Faculty of Mathematics and Computer Science**, University of Bucharest. 

Each homework includes requirements, implementation details, code and image files.

<details>
  <summary> 💡 Homework #1</summary>

### 📜 Task Requirements

#### Components
- RGB LED (minimum 1)
- Potentiometers (minimum 3)
- Resistors
- Wires


#### Technical Task
Use a separate potentiometer to control each of the colors of the RGB LED.
The LED must be controlled with software, meaning we must read the value of the potentiometers with Arduino, and write a mapped value to each of the pins connected to the LED.

#### Coding Task
Coding style is of utmost importance. Magic numbers are not accepted and style consistency is key.


### 🖼️ Pictures of the setup
- [Front view](https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%231/hw1_Setup_Pictures/FrontView.jpg)
 <img src="https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%231/hw1_Setup_Pictures/FrontView.jpg" width="400" height="400" />

- [Back view](https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%231/hw1_Setup_Pictures/BackView.jpg)
 <img src="https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%231/hw1_Setup_Pictures/BackView.jpg" width="400" height="400" />
 
- [Top-Down View](https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%231/hw1_Setup_Pictures/TopDownView.jpg)
 <img src="https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%231/hw1_Setup_Pictures/TopDownView.jpg" width="400" height="400" />

### 🎞️ Video presenting the functionality
The video can be found [here](https://youtu.be/IT1rydAFlZk).

### 🖥️ Code
The code can be found in this repository, [here](https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%231/hw1_RGB_LED/hw1_RGB_LED.ino).


<details>
  <summary> 🚦 Homework #2</summary>

### 📜 Task Requirements

#### Components
- 5 LEDs 
- 1 button 
- 1 buzzer
- Resistors
- Wires


#### Task Description
This homework consisted in building the traffic lights for a crosswalk. I used 2 LEDs (green and red) for the pedestrian traffic lights and 3 LEDs (green, yellow and red) for the car traffic lights. This system has 4 states:
- State 1: default, reinstated after State 4 ends. We have green light for cars, red light for people, no sounds. The duration is indefinite, change by pressing the button.
- State 2: Starts after 8 seconds after a button press. The light is yellow for cars, red for people and no sounds. This state lasts 3 seconds.
- State 3: Starts after State 2 ends. The light is red for cars, green for people and there is a beeping sounds from the buzzer at a constant interval. This state lasts 8 seconds.
- State 4: Starts after State 3 ends. The light is red for cars, **blinking green** for people and there is a beeping sounds from the buzzer at a constant interval, faster then the beeping in the previous state. This state lasts 3 seconds. This state lasts 4 seconds. 

#### Coding Task
Coding style is of utmost importance. Magic numbers are not accepted and style consistency is key. An importantcoding challenge present in this task is using **millis()** instead of **delay()**.


### 🖼️ Pictures of the setup
- [Front view](https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%232/SetUp_Pictures/FrontView.jpg)
 <img src="https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%232/SetUp_Pictures/FrontView.jpg" width="400" height="400" />

- [Back View](https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%232/SetUp_Pictures/BackView.jpg)
 <img src="https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%232/SetUp_Pictures/BackView.jpg" width="400" height="400" />

- [Top-Down View](https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%232/SetUp_Pictures/TopDownView.jpg)
 <img src="https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%232/SetUp_Pictures/TopDownView.jpg" width="400" height="400" />

### 🎞️ Video presenting the functionality
The video can be found [here](https://youtu.be/yomegRG7JE8).

### 🖥️ Code
The code can be found in this repository, [here](https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%232/homework%232/homework%232.ino).

