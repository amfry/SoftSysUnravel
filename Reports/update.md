# Unravel: Protothreading in C on Arduino
## Abby Fry and Nathan Estill

### Project Goals
Our project goal is to create a program that can run multiple threads on an Arduino Uno.  Our original MVP was to understand how protothreading works and have a small program that utilizes multithreading to make two things update simultaneously on an Arduino without relying on pre-existing libraries. Our stretch goal is to make more than two things update on the Arduino.

Since starting the project, we have modified our MVP slightly to be understanding how protothreading works and have a small program that utilizes multithreading to make two things update simultaneously on an Arduino.  Implementing this without external libraries proved to be quite difficult and we felt that using an external one still allowed us to achieve our learning goals.  We have also updated our stretch goal to get create a new stack and have the threads use it.
### Learning Goals
By working on this project, we want to gain a deeper understanding of how hardware limitations interact with software.  We want to learn more about how C can be used for embedded development and the challenges associated with that.  We would also like to understand how the hardware of the Arduino limits threading.
### Resources
* [An already existing library to help implement threads on an Arduino](https://github.com/ivanseidel/ArduinoThread)
* [A tutorial w/ arduino code on implementing protothreading](https://create.arduino.cc/projecthub/reanimationxp/how-to-multithread-an-arduino-protothreading-tutorial-dd2c37)
* [Details about protothreading](http://dunkels.com/adam/pt/)

### The Journey So Far
We began by learning more about threading and challenges implementing them in C.  From that research, we found a library called pt.h and decided to use it to make protothreads on the Arduino. We got it to complile and run on the Arduino as protothreads. We used the pt.h library to make a program that could function as a bike light. The inputs thread handles the button pressing functionality to change the variable that remembers the state of the light. The outputs thread uses this variable to control which light is turned on. The two threads run such that they alternate running.

### Next Steps
At this point, we achieved our original MVP of getting two protothreads to run on an Arduino but we used a pre-existing library to implement it. Making our own library or using something like pthread.h are out of the scope of the project, so we pivoted to a slightly different goal. First we will figure out if the pt.h library threads are running on the same stack, which will be done when we use the same strategies as we did in exercise 9. Then we will learn more about stacks and how to create them and have functions interact with them. If they are running on different stacks, our next task would be to make the threads run on the same stack. the definition of done for this task is when the strategy we used to test if they run on the same stack works for our new implementation.

[Github Repository](https://github.com/amfry/SoftSysUnravel)

[Trello Board](https://trello.com/b/yUVN1Rta/unravel)
