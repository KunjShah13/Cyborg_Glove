#include <Keyboard.h>
#include <Mouse.h>
#include <MPU9250.h>
#include <Wire.h>
MPU9250 IMU (Wire , 0x68);
float dt;
float mfroll = 7;
int mfpitch = 13;
unsigned long millisOld;
int en = 9;
int state = 0;
int wheel = 0;
int enter = 7;
int back = 8;
int ctrl = 10;
int right = 6;
int left = 5;
int opitch;
int oroll;
void setup() {
  pinMode(en, INPUT_PULLUP);
  pinMode(enter, INPUT_PULLUP);
  pinMode(back, INPUT_PULLUP);
  pinMode(ctrl, INPUT_PULLUP);
  pinMode(left, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);
  IMU.begin();
  millisOld = millis();
  Serial.begin(9600);
  Keyboard.begin();
}

void loop() {
  dt = (millis() - millisOld) / 1000.;
  millisOld = millis();
  IMU.readSensor();
  float ax = IMU.getAccelX_mss();
  float ay = IMU.getAccelY_mss();
  float az = IMU.getAccelZ_mss();

  float apitch = 180 * atan2(ax, sqrt(ay * ay + az * az)) / PI;
  float aroll = 180 * atan2(ay, sqrt(ax * ax + az * az)) / PI;

  float gpitch = gpitch + IMU.getGyroX_rads() * dt;
  float groll = groll + IMU.getGyroY_rads() * dt;
  float gyaw = gyaw + IMU.getGyroZ_rads() * dt;

  float pitch = 0.98 * gpitch + 0.02 * apitch;
  float roll = 0.98 * groll + 0.02 * aroll;
  //Serial.println("pitch"  + String( pitch));
  //Serial.println("roll" + String( roll));
  //Serial.println("yaw" + String( gyaw));
  pitch = mfpitch * pitch;
  roll = mfroll * roll;
  //Serial.println(state);
  if (digitalRead(en) != 1) {
    state = state + 1;
    delay(200);
    opitch = pitch;
    oroll = roll;
  }
  if (state % 2 == 0) {
    Mouse.move(pitch - opitch, roll - oroll, wheel);

    if (digitalRead(ctrl) != HIGH) {
      typeKey(KEY_LEFT_CTRL);
    }

    else if (digitalRead(enter) != HIGH) {
      typeKey(KEY_RETURN);
    }

    else if (digitalRead(back) != HIGH) {
      typeKey(KEY_BACKSPACE);
    }

    else if (digitalRead(left) != HIGH) {
      Mouse.press(MOUSE_LEFT);
    }

    else if (digitalRead(right) == HIGH) {
      Mouse.release(MOUSE_LEFT);
    }

    else if (digitalRead(right) != HIGH) {
      Mouse.press(MOUSE_RIGHT);
      Mouse.release(MOUSE_RIGHT);
      delay(10);
      Mouse.click(MOUSE_LEFT);
      Mouse.release(MOUSE_LEFT);
      delay(100);
    }
  }
}

void typeKey(int key) {
  Keyboard.press(key);
  delay(140);
  Keyboard.release(key);
}
