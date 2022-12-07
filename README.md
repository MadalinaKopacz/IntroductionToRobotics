
# Introduction to Robotics (2022 - 2023)


Introduction to Robotics laboratory homeworks, taken in the 3rd year at the **Faculty of Mathematics and Computer Science**, University of Bucharest. 

Each homework includes requirements, implementation details, code and image files.

<details>
  <summary> <h2> 💡 Homework #1 </h2> </summary>

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
</details>
<details>
  <summary> <h2> 🚦 Homework #2 </h2> </summary>

### 📜 Task Requirements

#### Components
- 5 LEDs 
- 1 button 
- 1 buzzer
- Resistors
- Wires


#### Task Description
This homework consisted in building the traffic lights for a crosswalk. I used 2 LEDs (green and red) for the pedestrian traffic lights and 3 LEDs (green, yellow and red) for the car traffic lights. This system has 4 states:
- State 1: default, reinstated after State 4 ends. We have green light for cars, red light for people, no sounds. The duration is indefinite, changed by pressing the button.
- State 2: Starts after 8 seconds after a button press. The light is yellow for cars, red for people and no sounds. This state lasts 3 seconds.
- State 3: Starts after State 2 ends. The light is red for cars, green for people and there is a beeping sound from the buzzer at a constant interval. This state lasts 8 seconds.
- State 4: Starts after State 3 ends. The light is red for cars, **blinking green** for people and there is a beeping sounds from the buzzer at a constant interval, faster then the beeping in the previous state. This state lasts 4 seconds. 

#### Coding Task
Coding style is of utmost importance. Magic numbers are not accepted and style consistency is key. An important coding challenge present in this task is using **millis()** instead of **delay()**.


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

</details>
<details>
  <summary> <h2> 🕹️ Homework #3 </h2> </summary>

### 📜 Task Requirements

#### Components
- 1 7-segment display 
- 1 joystick
- Resistors
- Wires

#### Task Description
This homework consisted in using a joystick to control a 7-segment display. This system has 2 states:
- State 1: default, but also reinstated after a button press in State 2. Current  position  blinking. Can  use  the  joystick  to  move  from one  position  to  its neighbors.   Short  pressing  the  button  toggles  State 2. Long pressing the button in State 1 resets the entire display by turning all the segments OFF and moving the current position to the decimal point.
- State 2: initiated  after  a  button  press  in  State  1. The current segment stops blinking, adopting the state of the segment before selection (ON or OFF). Toggling the X axis should change  the  segment  state  from  ON  to  OFF  or  from  OFF  to  ON. Clicking the joystick should save the segment state and exit back to State 1.

Mentions:
- Long pressing the button to reset should be available only in State 1.
- Some examples of possible movements: a - b (moving down); f - b(moving to the right); d - g (moving up); c - dp (moving to the right).
- Joystick movements should be done with toggle, as in the lab (joy-Moved, etc)

#### Coding Task
Coding style is of utmost importance. Magic numbers are not accepted and style consistency is key. An important coding challenge present in this task is using **millis()** instead of **delay()**.


### 🖼️ Pictures of the setup
- [Front view](https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%233/SetUp_Pictures/FrontView.jpg)
 <img src="https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%233/SetUp_Pictures/FrontView.jpg" width="400" height="400" />

- [Back View](https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%233/SetUp_Pictures/BackView.jpg)
 <img src="https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%233/SetUp_Pictures/BackView.jpg" width="400" height="400" />

- [Top-Down View](https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%233/SetUp_Pictures/TopDownView.jpg)
 <img src="https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%233/SetUp_Pictures/TopDownView.jpg" width="400" height="400" />

### 🎞️ Video presenting the functionality
The video can be found [here](https://youtu.be/J91DPxjZTuM).

### 🖥️ Code
The code can be found in this repository, [here](https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%233/homework%233/homework%233.ino).

</details>

<details>
  <summary> <h2> 🔢 Homework #4 </h2> </summary>

### 📜 Task Requirements

#### Components
- 1 4 digit 7-segment display 
- 1 joystick
- 1 74hc595 shift register
- Resistors
- Wires

#### Task Description
This homework consisted in using a joystick to move through the 4 digit 7- segment displays digits. We can press the button to lock in the current digit and use the other axis to increment/decrement the number.  By keeping the button pressed, we can reset all the digit values and the current position becomes the first digit. 
This system has the following states:
- State 1: default, but also reinstated after a button press in State 2. A joystick axis can be used to cycle through the 4 digits; using the other axis does nothing. A blinking decimal point shows the current digit position. By pressing the button, we lock in the selected digit and enter the second state.
- State 2: initiated  after  a  button  press  in  State  1. In this state, the decimal point stays always on, and we can no longer use the axis to cycle throughout the  4  digits.   Using  the  other  axis,  we  can  increment/decrement  the  number  on  the  current  digit  IN  HEX.  By pressing the button again, it returns to the previous state.  Also, the system should  not continuosly increment, if we keep the joystick in one position.
- Reset: toggled by long pressing the button, only in the first state. When resetting, all the digits go back to 0 and the current position is set to the first (rightmost) digit, in the first state.

#### Coding Task
Coding style is of utmost importance. Magic numbers are not accepted and style consistency is key.

### 🖼️ Pictures of the setup
- [Front view](https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%234/SetUp_Pictures/FrontView.jpg)
 <img src="https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%234/SetUp_Pictures/FrontView.jpg" width="600" height="400" />

- [Back View](https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%234/SetUp_Pictures/BackView.png)
 <img src="https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%234/SetUp_Pictures/BackView.png" width="600" height="400" />

- [Top-Down View](https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%234/SetUp_Pictures/TopDownView.png)
 <img src="https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%234/SetUp_Pictures/TopDownView.png" width="600" height="400" />

### 🎞️ Video presenting the functionality
The video can be found [here](https://youtu.be/3IIdMhDvcL8).

### 🖥️ Code
The code can be found in this repository, [here](https://github.com/MadalinaKopacz/IntroductionToRobotics/blob/main/Homework%234/homework%234/homework%234.ino).

</details>
