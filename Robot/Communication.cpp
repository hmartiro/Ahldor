/****************************************************
* Communication Module
* Prefix: COMM
****************************************************/

/*---------------- Includes ---------------------------------*/

#include "Communication.h"
//#include <WString.h>

/*---------------- Private Variables -------------------------*/

String usb_rx_buffer = "test 100\n";///////////////////////////////////////////////////////////////////for test, change!!!!!!!!!!!!!!!!!!!!!!!//////////////////

String last_command = String();
int last_arg = -1;

int new_command = FALSE;

Timer* timer;

/*---------------- Private Functions -------------------------*/

int COMM_has_new_command() {
  return new_command;
}

static int COMM_check_command_string(String* pStr) {
  
  String command = *pStr;
  
  if (command == last_command)
    return TRUE;
  return FALSE;
}

static void COMM_check_all_commands() {
  //DRIVE_commands();
}

static void COMM_command_received(String command) {
  //Serial.println("COMM command received: " + command);
  last_command = command;
  last_command.toUpperCase();
  last_arg = NO_ARGUMENT;
  new_command = TRUE;
  //COMM_check_all_commands();
}

static void COMM_command_received(String command, int arg) {
  //Serial.println("COMM command received: " + command + ", arg: " + String(arg));
  last_command = command;
  last_command.toUpperCase();
  last_arg = arg;
  new_command = TRUE;
  //COMM_check_all_commands();
}

static void COMM_parse_command(String command) {
  Serial.println("Command received: " + command);
  
  int delimiter_index = command.indexOf(DELIMITER);
  if(delimiter_index != -1) {
    String command_name = command.substring(0, delimiter_index);
    String arg_str = command.substring(delimiter_index+1);
      int arg = arg_str.toInt();
      if ((arg == 0) && (arg_str != "0")) {
        Serial.println("Integer argument converted to zero, ignoring!!");
        COMM_send_usb_command("ERROR bad command argument, not int");
      } else
        COMM_command_received(command_name, arg);
  } else {
    COMM_command_received(command);
  }
}

void(* resetFunc) (void) = 0;
static void COMM_reset() {
  Serial.println("COMM module reset!");
  resetFunc();
}

void COMM_check_command(String pCommand, void (*callback)(void)) {
  
  if(last_arg != NO_ARGUMENT) {
    //Serial.println("Ignoring command, argument present!");
    return;
  }
  
  if(COMM_check_command_string(&pCommand))
    callback();
}

void COMM_check_command(String pCommand, void (*callback)(int)) {
  
  if(last_arg == NO_ARGUMENT) {
    return;
  }
  
  if(COMM_check_command_string(&pCommand))
    callback(last_arg);
}

void COMM_send_usb_command(String command) {
  Serial.print(command);
  Serial.print(END_COMMAND);
}

void COMM_send_usb_command(String command, int arg) {
  Serial.print(command);
  Serial.print(DELIMITER);
  Serial.print(arg);
  Serial.print(END_COMMAND);
}

void COMM_Update() {
  
  new_command = FALSE;
  
  if(Serial.available()) {
    char c = (char)Serial.read();
    Serial.println(c);//prints
    Serial.println(usb_rx_buffer);//prints the initial value before it gets corrupted
    Serial.println(String(c));//fails, does not print anything.
    usb_rx_buffer = usb_rx_buffer + c;//corrupts usb_rx_buffer
    Serial.print("USB buffer increased:");
    Serial.print(usb_rx_buffer);//doesn't print anything
    Serial.println(":here");
    int end_command_index = usb_rx_buffer.indexOf(END_COMMAND);
    
    if(end_command_index != -1) {
      Serial.print("Not getting in here because the buffer is shot.");
      String command = usb_rx_buffer.substring(0, end_command_index);
      usb_rx_buffer = usb_rx_buffer.substring(end_command_index+1);
      COMM_parse_command(command);      
    }
    Serial.println("after the if. i'm guessing the command has not been parsed.");
  }
}

void COMM_Init(Timer* t) {
  
  Serial.begin(USB_BAUD);
  
  timer = t;
   
  Serial.println("COMM module initialized!");
}

void COMM_commands() {
  
  // Commands
  COMM_check_command(String("RESET"), COMM_reset);
}
