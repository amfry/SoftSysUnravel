#include "pt.h"
static int protothread1_flag, protothread2_flag;

int ButtonState;
int LastButtonState;

const int LED1 = 9; //
const int LED2 = 10; //
const int LED3 = 11;


static int outputs(struct pt *pt){

  PT_BEGIN(pt);
  int LED_index //index for the LED configuration the button is on

  while(1){
    PT_WAIT_UNTIL(pt,protothread1_flag !=0)
    Serial.println("Protothread 2 is running\n")
    if (ButtonState!=LastButtonState){
      //check for change in ButtonState
      if (ButtonState == HIGH){
        LED_index ++; //check if button is pressed and change index acordingly
      }
    }

    LastButtonState = ButtonState;

    if(LED_index % 3 == 1){  //as loop run, index doesn't have to be set back to 0
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,LOW);
      digitalWrite(LED3,LOW);
    }

    if(LED_index % 3 == 2){
      digitalWrite(LED1,LOW);
      digitalWrite(LED2,HIGH);
      digitalWrite(LED3,LOW);
    }

    if(LED_index % 3 == 3){
      digitalWrite(LED1,LOW);
      digitalWrite(LED2,LOW);
      digitalWrite(LED3,HIGH);
    }

    protothread1_flag = 0;
    protothread2_flag = 1;
    }
  PT_END(pt);
}
static struct pt pt1, pt2;

void setup(){
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
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
    inputs(&pt1);
    outputs(&pt2);
  }
}
