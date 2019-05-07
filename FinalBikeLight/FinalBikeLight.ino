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
  SP = 1600;
  int LED_index = 0;
  PT_BEGIN(pt);
  uint8_t *stackptr;
  stackptr =  (uint8_t *)(SP);
  int ButtonState = LOW;
  int LastButtonState = LOW;
  int button = LOW;
  while(1) {
    PT_WAIT_UNTIL(pt, protothread2_flag != 0);
    button = digitalRead(buttonPin);
    if(button == HIGH){
      if(buttonTemp == 0){
        LED_index++;
        *stackptr = 300;
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
  SP = 1600;
  Serial.println("this is happening");
  uint8_t *stackptr;
  stackptr =  (uint8_t *)(SP);
  int LED_index = 0;
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

//__attribute__((noinline)) int recurse(int counter){
//  if(counter < 100){
//    stackptr =  (uint8_t *)(SP);
//    Serial.print(counter);Serial.print(":"); Serial.println((int) stackptr);
//    SP = SP - 8;
//    recurse(counter + 1);
//  }
//}

void loop() {
  // put your main code here, to run repeatedly:
//  check_stack();
//  Serial.print("Stack: ");
//  Serial.println((int) * stackptr);
//  recurse(0);
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
