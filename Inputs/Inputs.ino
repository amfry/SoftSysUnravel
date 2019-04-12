#include "pt.h"
static int protothread1_flag, protothread2_flag;

static int ButtonState;

static int inputs(struct pt *pt){

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