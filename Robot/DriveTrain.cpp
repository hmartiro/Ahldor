/****************************************************
 * Drivetrain
 * Prefix: Drive
 ****************************************************/


/*---------------- Includes ---------------------------------*/

#include "DriveTrain.h"

/*---------------- Module Functions -------------------------*/

int clamp_v(int vel) {
  int v = vel;
  if(v > 255) v = 255;
  if(v < 0) v = 0;
  return v;
}

void DRIVE_forward_left(int vel) {
  int v = clamp_v(vel + LEFT_OFFSET);
  Serial.println("Left wheel forward at vel " + String(v));
  digitalWrite(LWHEEL_DIR, HIGH);
  analogWrite(LWHEEL_ENABLE, v);
}

void DRIVE_forward_right(int vel) {
  int v = clamp_v(vel + RIGHT_OFFSET);
  Serial.println("Right wheel forward at vel " + String(v));
  digitalWrite(RWHEEL_DIR, LOW);
  analogWrite(RWHEEL_ENABLE, v);
}

void DRIVE_backward_left(int vel) {
  int v = clamp_v(vel + LEFT_OFFSET);
  Serial.println("Left wheel backward at vel " + String(v));
  digitalWrite(LWHEEL_DIR, LOW);
  analogWrite(LWHEEL_ENABLE, v);
}

void DRIVE_backward_right(int vel) {
  int v = clamp_v(vel + RIGHT_OFFSET);
  Serial.println("Right wheel forward at vel " + String(v));
  digitalWrite(RWHEEL_DIR, HIGH);
  analogWrite(RWHEEL_ENABLE, v);
}

void DRIVE_forward(int vel) {
  DRIVE_forward_left(vel);
  DRIVE_forward_right(vel);
}

void DRIVE_backward(int vel) {
  DRIVE_backward_left(vel);
  DRIVE_backward_right(vel);
}

void DRIVE_turn_right(int mag) {
  DRIVE_forward_left(mag);
  DRIVE_backward_right(mag);
}

void DRIVE_turn_left(int mag) {
  DRIVE_backward_left(mag);
  DRIVE_forward_right(mag);
}

void DRIVE_stop() {
  DRIVE_forward(0);
}

void DRIVE_forward_full() {
  DRIVE_forward_left(255);
  DRIVE_forward_right(255);
}

void DRIVE_backward_full() {
  DRIVE_backward_left(255);
  DRIVE_backward_right(255);
}

void DRIVE_Init(Timer* t) {
  
  pinMode(LWHEEL_DIR, OUTPUT);
  pinMode(RWHEEL_DIR, OUTPUT);
  pinMode(LWHEEL_ENABLE, OUTPUT);
  pinMode(RWHEEL_ENABLE, OUTPUT);
  //pinMode(LWHEEL_BRAKE, OUTPUT);
  //pinMode(RWHEEL_BRAKE, OUTPUT);
  
  digitalWrite(LWHEEL_DIR, LOW);
  digitalWrite(RWHEEL_DIR, LOW);
  analogWrite(LWHEEL_ENABLE, 0);
  analogWrite(RWHEEL_ENABLE, 0);
  //digitalWrite(LWHEEL_BRAKE, LOW);
  //digitalWrite(RWHEEL_BRAKE, LOW);
  
  Serial.println("DRIVE module initialized!");
}

void DRIVE_commands() {
  
  // Commands
  COMM_check_command(String("DRIVE_STOP"), DRIVE_stop);
  COMM_check_command(String("DRIVE_FORWARD_FULL"), DRIVE_forward_full);
  COMM_check_command(String("DRIVE_BACKWARD_FULL"), DRIVE_backward_full);
  COMM_check_command(String("DRIVE_FORWARD"), DRIVE_forward);
  COMM_check_command(String("DRIVE_BACKWARD"), DRIVE_backward);
  COMM_check_command(String("TURN_LEFT"), DRIVE_turn_left);
  COMM_check_command(String("TURN_RIGHT"), DRIVE_turn_right);
  COMM_check_command(String("DRIVE_FORWARD_RIGHT"), DRIVE_forward_right);
  COMM_check_command(String("DRIVE_FORWARD_LEFT"), DRIVE_forward_left);
}
