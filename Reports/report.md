# Unravel: Protothreading in C on Arduino
## Abby Fry and Nathan Estill

### Project Goals
Our project goal is to create a program that can run multiple threads on an Arduino Uno.  Our minimum goal was to understand how protothreading works and have a small program that utilizes multi-threading to make two things update simultaneously on an Arduino.  We decided to implement our protothreads in the context of creating a simple "bike light."  Our "bike light" was made up of 3 LEDs that could be toggled through with a button.

After completing our minimum goal, we focused on learning more about the stack and how the library we used utilized the stack to make multi-threading possibly on the Arduino.
### Resources
* [An already existing library to help implement threads on an Arduino](https://github.com/ivanseidel/ArduinoThread)
* [A tutorial w/ arduino code on implementing protothreading](https://create.arduino.cc/projecthub/reanimationxp/how-to-multithread-an-arduino-protothreading-tutorial-dd2c37)
* [Details about protothreading](http://dunkels.com/adam/pt/)

### Setting Up the PT Thread Library Tutorial
Setting up the PT Thread for Arduino was difficult the first time through. First you need to download the pt thread folder from [the website](http://dunkels.com/adam/pt/download.html) and put it into your Arduino libraries folder. The thread won't compile the first time around. You need to delete

### Hardware Setup

### The Journey So Far
We began by learning more about threading and challenges implementing them in C.  From that research, we found a library called pt.h and decided to use it to make protothreads on the Arduino. We got it to complile and run on the Arduino as protothreads. We used the pt.h library to make a program that could function as a bike light. The inputs thread handles the button pressing functionality to change the variable that remembers the state of the light. The outputs thread uses this variable to control which light is turned on. The two threads run such that they alternate running.

### Challenge
-what does it mean for the threads to be stackless
-Inline w/ the stack



[Github Repository](https://github.com/amfry/SoftSysUnravel)

[Trello Board](https://trello.com/b/yUVN1Rta/unravel)
