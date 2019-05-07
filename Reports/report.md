# Unravel: Protothreading in C on the  Arduino Uno
## Abby Fry and Nathan Estill

### Project Goals
Our project goal is to create a program that can run multiple threads on an Arduino Uno.  Our minimum goal was to understand how protothreading works and have a small program that utilizes multi-threading to make two things update simultaneously on an Arduino.  We decided to implement our protothreads in the context of creating a simple bike light.  Our bike light was made up of 3 LEDs that could be toggled through with a button.

After completing our minimum goal, we focused on learning more about the stack and how the library we used utilized the stack to make multi-threading possibly on the Arduino. Our ultimate goal was to be able move the stack pointer for each of the threads and have the thread run at a new point in address space.

### Resources
* [An already existing library to help implement threads on an Arduino](https://github.com/ivanseidel/ArduinoThread)
* [A tutorial w/ arduino code on implementing protothreading](https://create.arduino.cc/projecthub/reanimationxp/how-to-multithread-an-arduino-protothreading-tutorial-dd2c37)
* [Details about protothreading](http://dunkels.com/adam/pt/)

### Setting Up the PT Thread Library Tutorial
Setting up the PT Thread for Arduino was difficult the first time through. First you need to download the pt thread folder from [the website](http://dunkels.com/adam/pt/download.html) and put it into your Arduino libraries folder. The thread library won't compile the first time around. The examples included in the library need additional libraries. As they are not neccesary, delete the three files 'example-buffer.c', 'example-codelock.c' and 'example-small.c'. After that, the library should compile just fine in Arduino.

### Hardware Setup
To create the hardware for the bike light set up, we used :
* Arduino Uno
* 3 LEDs
* A 4 pin button
* 3 200K resistors

[SEE c00l SCHEMATIC HERE ]
### Protothreading
We started off by creating a basic threading program to confirm we could get multiple threads running with pthreads library.  Then we laid out a skeleton for our bike light program.  We divided up functionality into an input and output threads. The inputs thread handled the button pressing functionality to change the variable that remembers the state of the light. The outputs thread uses this variable to control which light is turned on.  

To get the threads to alternate in running we used function from the pthreads library. PT_BEGIN declared the start of the protothread, input. PT_WAIT_UNTIL() blocks the thread from running and waits until condition that are set at the end of the output thread are true.  PT_END() is used to declare the end of the thread. Below is the shell for the threading part of the code for the input thread.
```c
int inputs(struct pt *pt){
  PT_BEGIN(pt);
  while(1) {
    PT_WAIT_UNTIL(pt, protothread2_flag != 0);
    // Body of the inputs function
    protothread2_flag = 0;
    protothread1_flag = 1;
  }

  PT_END(pt);
}
```
Below is a showing the bike light alternating LEDs after the button is pressed.

[![](http://img.youtube.com/vi/CSBi38pHqTo/0.jpg)](http://www.youtube.com/watch?v=CSBi38pHqTo "Bike Light Demo")

### Challenge
Our stretch goal was to look into the stackless nature of the protothreads. The website for the library claimed that the threads it made were stackless. To look into this, we first tried to run functions in the thread, which worked. Then we got the location of the stack pointer within the thread. To ensure the stack pointer was working as expected, we ran a recursive function that ran 100 times and printed the stack pointer. The function had to have the attribute no inline added to stop the function from being inserted into the code. The location of the stack pointer was the same in both threads. We were still able to use stack variables in the function. At this point, we are still confused on why the website labels these threads a stackless, as they seem to still have a stack.

We tried to make the threads share a stack. We set the stack pointer of both of them to a point in the memory. Then we had each thread reference and change the value of the stack pointer. However, every time each function ran, it reset the value at the stack pointer, leading us to believe that the threads are actually stackful.


### Reflection
As a team, we were able to build off of the introduction to threads in-class and apply it to a new problem.  Getting experience with a new library was valuable because we relied on the documentation to learn about how the library was using the stack.  Our stretch goal about moving the stack pointer made the second half of the project research heavy.  Trying to understand how protothreading used the stack meant running a lot of small experiments to see where variables were getting allocated.  These small, incremental changes really allowed us to hone our understanding of the stack.  However, it was challenging to keep moving in a consistent direction because it was easy to get lost in different theories for what might have been happening.

[Github Repository](https://github.com/amfry/SoftSysUnravel)

[Trello Board](https://trello.com/b/yUVN1Rta/unravel)
