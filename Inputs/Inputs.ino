#include "pt.h"
static int protothread1_flag, protothread2_flag;

static int ButtonState;
static int analogReader;
int buttonPin = 7;
int analogPin = A0;

static int inputs(struct pt *pt){
/* A protothread function must begin with PT_BEGIN() which takes a pointer to a struct pt. */
  PT_BEGIN(pt);

  /* We loop forever here. */
  int buttonTemp = 0;
  while(1) {
    /* Wait until the other protothread has set its flag. */
    PT_WAIT_UNTIL(pt, protothread2_flag != 0);
    Serial.println("Protothread 1 running\n");
    if(digitalRead(buttonPin)){
    	if(!buttonTemp){
    		ButtonState++;
    		buttonTemp = 1;
    		delay(20);
    	}
    } else {
    	if(buttonTemp){
    		buttonTemp = 0;
    		delay(20);
    	}
    }

    analogReader = analogRead(analogPin);

    /* We then reset the other protothread's flag, and set our own flag so that the other protothread can run. */
    protothread2_flag = 0;
    protothread1_flag = 1;

    /* And we loop. */
  }

  /* All protothread functions must end with PT_END() which takes a pointer to a struct pt. */
  PT_END(pt);
}

static int outputs(struct pt *pt){
	
}

static struct pt pt1, pt2;
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
    inputs(&pt1);
    outputs(&pt2);
  }
}