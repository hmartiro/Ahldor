/**************************************************************
  File:      Robot.ino 
  Contents:  This program runs the robot for the ME210 2014 
              Bitcoin Bonanza competition.
  
  Team:      Caitlin Clancy
             Stefan Kowalski
             Mishel Johns
             Hayk Martirosyan

**************************************************************/

/*---------------- Includes ---------------------------------*/

// outside libraries
#include <Servo.h>
#include "Timer.h"

// modules
#include "Defines.h"
#include "Communication.h"
#include "Multiplex.h"
#include "BeaconSens.h"
#include "Diagnostics.h"
#include "LineFind.h"
#include "MineShoot.h"
#include "DriveTrain.h"

/*---------------- Module Defines ---------------------------*/

// states
#define STATE_WAIT_FOR_JOYSTICK 0
#define STATE_WAIT_TO_START 1
#define STATE_ROTATE_TO_SERVER 2
#define STATE_FIND_THE_LINE 3
#define STATE_ROTATE_TO_ALIGN 4
#define STATE_FOLLOW_LINE 5
#define STATE_MINE_SHOOT 6
#define STATE_FIND_NEXT_EX 7
#define STATE_TURNOFF 8

/*------------------ Module Level Variables -----------------*/

// timer library object
Timer t;

// which state is the robot in
byte state;

// if TRUE, beacon is to left and exchanges to right
// if FALSE, beacon is to right and exchanges to left
int map_left;

/*---------------- Arduino Main Functions -------------------*/

 void MAIN_commands() {
   COMM_check_command(String("FIND_LINE"), start_finding_line);
 }
 
void check_for_commands() {
  COMM_Update();
  if(COMM_has_new_command()) {
    COMM_commands();
    DRIVE_commands();
    MINE_commands();
    BEACON_commands();
    DIAG_commands();
    LINE_commands();
    MUX_commands();
    MAIN_commands();
  }
}

void mine() {
  Serial.println("mined!");
}
int mine_timer;
void stopMine() {
  t.stop(mine_timer);
}

void setup() {
  
  // Initializing each module
  COMM_Init(&t);
  MUX_Init(&t);
  BEACON_Init(&t);
  DIAG_Init(&t);
  DRIVE_Init(&t);
  LINE_Init(&t);
  MINE_Init(&t);
  
  t.every(COMM_UPDATE_RATE, check_for_commands);
  
  //mine_timer = t.every(500, mine);
  //t.after(2600, stopMine);
  Serial.println("Modules initialized!");
  
  state = STATE_WAIT_TO_START;
}

// temp, for line following
void start_finding_line() {
  map_left = FALSE;
  Serial.println("Putting into STATE_FIND_THE_LINE!");
  DRIVE_forward(120);
  state = STATE_FIND_THE_LINE;
}

void loop() {
  //MUX_print_line();
  // Update the timer
  t.update();
  
  switch(state)
  {
    case STATE_WAIT_TO_START:
    
    //if startbutton pressed
          //selectside()
          
      break;
    case STATE_ROTATE_TO_SERVER:
      break;
    case STATE_FIND_THE_LINE:
      if(LINE_front())
      {             
        DRIVE_backward(255);
        delay(100);
        DRIVE_stop();
        state = STATE_ROTATE_TO_ALIGN;   
      }
      break;
    case STATE_ROTATE_TO_ALIGN:
    
      if(map_left == TRUE) {
        DRIVE_turn_right(100);
      } else if (map_left == FALSE) {
        DRIVE_turn_left(100);
      }
      delay(300);
      DRIVE_stop();
      //if aligned
      //MINE_rotate_to_shoot();//align for first target so we're ready to shot when we get to the server
      break;
    case STATE_FOLLOW_LINE:
      break;
    case STATE_MINE_SHOOT:
      break;
    case STATE_FIND_NEXT_EX:
      MINE_rotate_to_shoot();
      //delayMicroseconds();//time to finish turning
      break;
    case STATE_TURNOFF:
      //turn off all motors
      break;
  }
       
}



