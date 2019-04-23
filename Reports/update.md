# Unravel: Protothreading in C on Arduino
## Abby Fry and Nathan Estill

### Project Goals
Our project goal is to create a program that can run multiple threads on an Arduino Uno.  Our MVP is to understand how protothreading works and have a small program that utilizes multithreading to make two things update simultaneously on an Arduino without relying on pre-existing libraries. Our stretch goal is to make more than two things update on the Arduino.  
### Learning Goals
By working on this project, we want to gain a deeper understanding of how hardware limitations interact with software.  We want to learn more about how C can be used for embedded development and the challenges associated with that.  We would also like to understand how the hardware of the Arduino limits threading.
### Resources
* [An already existing library to help implement threads on an Arduino](https://github.com/ivanseidel/ArduinoThread)
* [A tutorial w/ arduino code on implementing protothreading](https://create.arduino.cc/projecthub/reanimationxp/how-to-multithread-an-arduino-protothreading-tutorial-dd2c37)
* [Details about protothreading](http://dunkels.com/adam/pt/)

### First Steps
Our first step will be to read through our tutorials and fully understand them, which both of us will do.  We will create notes from the tutorials that can be referenced during the project. Then, after reading through the tutorials, we will make tasks and a more thorough game plan and assign the tasks on Trello. This is completed when we have most of the tasks needed to finish the project on the board. Our third step will be creating a code skeleton with the functions that will be needed and their specific functionality, which we will both do. We will consider that done when we have an outline that, based off our research, will allow us to implement our MVP.  This skeleton will most likely need to be updated throughout the project.  We also need to establish basic communication between C and Arduino.

### The Journey So Far
We begun by using a library called pt.h to make protothreads in Arduino. We got it to complile and run on the Arduino as protothreads. We used the pt.h library to make a program that could function as a bike light. The inputs thread handles the button pressing functionality to change the variable that remembers the state of the light. The outputs thread uses this variable to control which light is turned on. The two threads run such that they alternate running.

### Next Steps
At this point, since we achieved our original goal of a bike light, but we used a pre-existing library to implement it. Making our own library or using something like pthread.h are out of the scope of the project, so we pivoted to a slightly different goal. First we will figure out if the pt.h library threads are running on the same stack. If they are running on different stacks, our next task would be to make the threads run on the same stack.
