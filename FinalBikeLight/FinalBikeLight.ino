#include "pt.h"
static int protothread1_flag, protothread2_flag;
const int buttonPin = 6;
const int LED1 = 9;
const int LED2 = 10;
const int LED3 = 11;
static int LED_index = 0;
bool buttonTemp = 0;

void setup(){
  pinMode(LED1,OUTPUT);
  pinMode(LED2,OUTPUT);
  pinMode(LED3,OUTPUT);
  pinMode(buttonPin,INPUT);
  Serial.begin(9600);
}
  
int inputs(struct pt *pt){
  // Handles the button sensor of the Bike Light
  PT_BEGIN(pt);
  int ButtonState = LOW;
  int LastButtonState = LOW;
  int button = LOW;
  while(1) {
    PT_WAIT_UNTIL(pt, protothread2_flag != 0);
    button = digitalRead(buttonPin);
    if(button == HIGH){
      if(buttonTemp == 0){
        LED_index++;
        buttonTemp = 1;
        delay(40);
      }
    } else {
      if(buttonTemp == 1){
        buttonTemp = 0;
        delay(40);
      }
    }
    protothread2_flag = 0;
    protothread1_flag = 1;
  }
 
  PT_END(pt);
}
int outputs(struct pt *pt){
  // Handles the LEDs of the bike light
  PT_BEGIN(pt);
  while(1){
    protothread2_flag = 1;
    PT_WAIT_UNTIL(pt,protothread1_flag !=0);
    if(LED_index % 3 == 0){  //as loop run, index doesn't have to be set back to 0
      digitalWrite(LED1,HIGH);
      digitalWrite(LED2,LOW);
      digitalWrite(LED3,LOW);
    }

    if (LED_index % 3 == 1){
      digitalWrite(LED1,LOW);
      digitalWrite(LED2,HIGH);
      digitalWrite(LED3,LOW);
    }

    if(LED_index % 3 == 2){
      digitalWrite(LED1,LOW);
      digitalWrite(LED2,LOW);
      digitalWrite(LED3,HIGH);
    }

    protothread1_flag = 0;
  }
  PT_END(pt);
}
static struct pt pt1, pt2;

void loop() {
  Serial.print("global");
  Serial.println((int) &buttonTemp);
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
