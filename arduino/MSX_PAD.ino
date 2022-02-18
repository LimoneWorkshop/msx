#include <Joystick.h>
#include <Keyboard.h>

Joystick_ Joystick(JOYSTICK_DEFAULT_REPORT_ID,JOYSTICK_TYPE_GAMEPAD,
  2, 0,                  // Button Count, Hat Switch Count
  true, true, false,     // X and Y, but no Z Axis
  false, false, false,   // No Rx, Ry, or Rz
  false, false,          // No rudder or throttle
  false, false, false);  // No accelerator, brake, or steering

#define turbo_fire_1 2
#define fire_1 3
#define fire_2 4
#define turbo_fire_2 5
#define dpad_up 6
#define dpad_down 7
#define dpad_left 8
#define dpad_right 9

#define KEY_SPACE 0x2C

bool dpad_up_val = true;
bool dpad_down_val = true;
bool dpad_left_val = true;
bool dpad_right_val = true;
bool fire_1_val = true;
bool fire_2_val = true;
bool turbo_fire_1_val = true;
bool turbo_fire_2_val = true;

int turbo_Spd_1 = 1;
int turbo_Spd_2 = 1;

bool fire_1_status = true;
bool fire_2_status = true;

int turbo_cnt_1 = 0;
int turbo_cnt_2 = 0;

int keyboard_cnt = 0;
bool keyboard_mode = false;

void setup() {
  // Initialize Button Pins
  pinMode(dpad_up, INPUT_PULLUP);
  pinMode(dpad_down, INPUT_PULLUP);
  pinMode(dpad_left, INPUT_PULLUP);
  pinMode(dpad_right, INPUT_PULLUP);
  pinMode(fire_1, INPUT_PULLUP);
  pinMode(fire_2, INPUT_PULLUP);  
  pinMode(turbo_fire_1, INPUT_PULLUP);
  pinMode(turbo_fire_2, INPUT_PULLUP);

  // Initialize Joystick Library
  Joystick.begin();
  Joystick.setXAxisRange(-1, 1);
  Joystick.setYAxisRange(-1, 1);

  Keyboard.begin();
}

void loop() {
  dpad_up_val = digitalRead(dpad_up);
  dpad_down_val = digitalRead(dpad_down);
  dpad_left_val = digitalRead(dpad_left);
  dpad_right_val = digitalRead(dpad_right);
  fire_1_val = digitalRead(fire_1);
  fire_2_val = digitalRead(fire_2);
  turbo_fire_1_val = digitalRead(turbo_fire_1);
  turbo_fire_2_val = digitalRead(turbo_fire_2);

  if(keyboard_mode){
    if (!fire_1_val) {
      Keyboard.press(KEY_RETURN);
      delay(110);
    }
    if (!fire_2_val) {
      Keyboard.press(KEY_SPACE);
      delay(110);
    }
    if (!dpad_up_val) {
      Keyboard.press(KEY_UP_ARROW);
      delay(110);
    }
    if (!dpad_down_val) {
      Keyboard.press(KEY_DOWN_ARROW);
      delay(110);
    }
    if (!dpad_left_val) {
      Keyboard.press(KEY_LEFT_ARROW);
      delay(110);
    }
    if (!dpad_right_val) {
      Keyboard.press(KEY_RIGHT_ARROW);
      delay(110);
    }
    if (!turbo_fire_1_val) {
      Keyboard.press('n');
      delay(110);
    }
    if (!turbo_fire_2_val) {
      keyboard_mode = false;
      keyboard_cnt = 0;
      delay(500);
    }
    Keyboard.releaseAll();
    
  }else{
    //UP, DOWN
    if(!dpad_up_val){
      Joystick.setYAxis(-1);
    }else if(!dpad_down_val){
      Joystick.setYAxis(1);
    }else{
      Joystick.setYAxis(0);
    }
  
    //LEFT
    if(!dpad_left_val){
      Joystick.setXAxis(-1);
    }else if(!dpad_right_val){
      Joystick.setXAxis(1);
    }else{
      Joystick.setXAxis(0);
    }
  
    //FIRE 1
    Joystick.setButton(0, !fire_1_val);
    
    //FIRE 2
    Joystick.setButton(1, !fire_2_val);
    
    //TURBO 1
    if(!turbo_fire_1_val){
      if(turbo_cnt_1 < 1){
        Joystick.setButton(0, true);
      }else if(turbo_cnt_1 > turbo_Spd_1){
        turbo_cnt_1 = 0;
      }else{
        Joystick.setButton(0, false);
        turbo_cnt_1++;
      }
      
      if(!fire_1_val){
        fire_1_status = false;
      }else if(!fire_1_status){
        turbo_Spd_1 = turbo_Spd_1 + 5;
        fire_1_status = true;
      }
      if(turbo_Spd_1 > 20){
        turbo_Spd_1 = 1;
      }
    }else{
      turbo_cnt_1 = 0;
    }
  
    //TURBO 2
    if(!turbo_fire_2_val){
      if(turbo_cnt_2 < 1){
        Joystick.setButton(1, true);
      }else if(turbo_cnt_2 > turbo_Spd_2){
        turbo_cnt_2 = 0;
      }else{
        Joystick.setButton(1, false);
        turbo_cnt_2++;
      }
      
      if(!fire_2_val){
        fire_2_status = false;
      }else if(!fire_2_status){
        turbo_Spd_2 = turbo_Spd_2 + 5;
        fire_2_status = true;
      }
      if(turbo_Spd_2 > 20){
        turbo_Spd_2 = 1;
      }
    }else{
      turbo_cnt_2 = 0;
    }

    if(!dpad_down_val && !fire_1_val && !fire_2_val){
      keyboard_cnt++;
    }else if (keyboard_cnt > 200){
      keyboard_mode = true;
      delay(200);
    }else{
      keyboard_cnt = 0;
    }
  }
  
  delay(10);
}
