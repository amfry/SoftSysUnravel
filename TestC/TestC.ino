#include "pt.h"
/* Two flags that the two protothread functions use. */
static int protothread1_flag, protothread2_flag;
const int buttonPin = 7;
const int LED1 = 9; //
const int LED2 = 10; //
const int LED3 = 11;
static int LED_index = 0;

/**
 * The first protothread function. A protothread function must always
 * return an integer, but must never explicitly return - returning is
 * performed inside the protothread statements.
 *
 * The protothread function is driven by the main loop further down in
 * the code.
 */
static int protothread1(struct pt *pt)
{
  /* A protothread function must begin with PT_BEGIN() which takes a pointer to a struct pt. */
  PT_BEGIN(pt);
  int buttonTemp = 0;
  /* We loop forever here. */
  while(1) {
    /* Wait until the other protothread has set its flag. */
    PT_WAIT_UNTIL(pt, protothread2_flag != 0);
    Serial.println("Protothread 1 running\n");
    if(digitalRead(buttonPin)){
      if(!buttonTemp){
        LED_index++;
        buttonTemp = 1;
        delay(20);
      }
    } else {
      if(buttonTemp){
        buttonTemp = 0;
        delay(20);
      }
    }

    /* We then reset the other protothread's flag, and set our own flag so that the other protothread can run. */
    protothread2_flag = 0;
    protothread1_flag = 1;

    /* And we loop. */
  }

  /* All protothread functions must end with PT_END() which takes a pointer to a struct pt. */
  PT_END(pt);
}

/*
The second protothread function. This is almost the same as the
first one.
*/
static int protothread2(struct pt *pt)
{
  PT_BEGIN(pt);

  while(1) {
    /* Let the other protothread run. */
    protothread2_flag = 1;

    /* Wait until the other protothread has set its flag. */
    PT_WAIT_UNTIL(pt, protothread1_flag != 0);
    Serial.println("Protothread 2 running\n");
    
    /* We then reset the other protothread's flag. */
    protothread1_flag = 0;

    /* And we loop. */
  }
  PT_END(pt);
}

/*
 * Finally, we have the main loop. Here is where the protothreads are
 * initialized and scheduled. First, however, we define the
 * protothread state variables pt1 and pt2, which hold the state of
 * the two protothreads.
 */
static struct pt pt1, pt2;

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  PT_INIT(&pt1);
  PT_INIT(&pt2);
  /*
   * Then we schedule the two protothreads by repeatedly calling their
   * protothread functions and passing a pointer to the protothread
   * state variables as arguments.
   */
  while(1) {
    protothread1(&pt1);
    protothread2(&pt2);
  }
}
