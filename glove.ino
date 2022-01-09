#include "MPU9250.h" //voltmeter cpacitance humidity&temperature ohm meter ammeter sensor
#include "DHT.h"
#include <LiquidCrystal.h>
const int rs = 10, en = 9, d4 = 5, d5 = 4, d6 = 3, d7 = 6;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
MPU9250 IMU(Wire, 0x68);
#define voltmeter A3 //voltmeter sense pin at A3
#define resistorValue  10000.0F  //Remember, we've used a 10K resistor to charge the capacitor
#define sw 7 //switch 1 at pin 7
#define sw1 12 //switch 2 at pin 8
#define analogPin 0 //capacitor capacitance sense pin at A0
#define chargePin 13 //cap charge pin at 13
#define dischargePin 8 //cap discharge pin at 11
#define DHTPIN 2 //sensor at pin2
#define curr A1 //ammeter sense pin
#define resistor A2 // ohm meter sense
#define echoPin 1 // attach pin 1 Arduino to pin Echo of HC-SR04
#define trigPin 0 //attach pin 0 Arduino to pin Trig of HC-SR04

DHT dht(DHTPIN, DHT11);
int i = 0;
int ar[3];
int flag = 0, count = 2;
int state = 0;
int act = 0;
int act1 = 0;
int value;
float angleX;
float angleY;
float vin, vout = 0;
float R1, R2;
float average;
float Vou = 0;
float r2;
float start_time;
float stop_time;
float distance; // variable for the distance measurement
long duration; // variable for the duration of sound wave travel
unsigned long startTime;
unsigned long elapsedTime;
float microFarads;
float nanoFarads;
void setup() {
  // put your setup code here, to run once:
  pinMode(sw, INPUT_PULLUP);
  pinMode(sw1, INPUT_PULLUP);
  pinMode(chargePin, OUTPUT);
  pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(echoPin, INPUT); // Sets the echoPin as an INPUT
  digitalWrite(chargePin, LOW);
  Serial.begin(9600);
  IMU.begin();
  IMU.setAccelRange(MPU9250::ACCEL_RANGE_8G);
  IMU.setGyroRange(MPU9250::GYRO_RANGE_500DPS);
  IMU.setDlpfBandwidth(MPU9250::DLPF_BANDWIDTH_5HZ);
  IMU.setSrd(19);
  dht.begin();
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  IMU.readSensor();
  float pitch = IMU.getAccelY_mss();
  float roll = IMU.getAccelX_mss();

  if (digitalRead(sw) == 0) {
    act = 1;
    lcd.clear();
  }
  else if (digitalRead(sw1) == 0) {
    act1 = 1;
    lcd.clear();
  }
  else {
    act = 0;
    act1 = 0;
  }
  if (act == 1) {
    if (roll > 3) {
      state = 1;
    }
    else if (roll < -3) {
      state = 2;
    }
    else if (pitch > 2) {
      state = 3;
    }
  }
  else if (act1 == 1) {
    if (roll > 3) {
      state = 5;
    }
    else if (roll < -3) {
      state = 6;
    }
    else if (pitch > 2) {
      state = 7;
    }
    else if (pitch < -2) {
      state = 8;
    }
  }
  if (state == 5) { // mode.....................................5
    R2 = 10000.0;
    R1 = 100000.0;
    value = analogRead(voltmeter);
    vout = (value * 5) / 1024.0;
    vin = vout / (R2 / (R1 + R2));
    Serial.println("Vin");
    Serial.println(vin);
    lcd.setCursor(0, 0);
    lcd.print("VOltage: ");
    lcd.setCursor(2, 2);
    lcd.print(vin);
    lcd.setCursor(15, 2);
    lcd.print(state);
  }

  if (state == 6) { //mode.......................................6
    //lcd.clear();
    digitalWrite(chargePin, HIGH);
    startTime = micros();
    while (analogRead(analogPin) < 648) {
    }

    elapsedTime = micros() - startTime;
    microFarads = ((float)elapsedTime / resistorValue) ;



    if (microFarads > 1) {
      Serial.println("SCALE:  0.1uF-4F");
      Serial.println(microFarads);
      lcd.setCursor(0, 0);
      lcd.print("SCALE:0.1uF-4F");
      lcd.setCursor(2, 2);
      lcd.print(microFarads);
      delay(500);
    }

    else {
      nanoFarads = microFarads * 1000.0;
      Serial.println("SCALE:  0.1uF-4F");
      Serial.println(nanoFarads);
      lcd.setCursor(0, 0);
      lcd.print("SCALE:0.1uF-4F");
      lcd.setCursor(2, 2);
      lcd.print(nanoFarads);
      delay(500);
    }


    digitalWrite(chargePin, LOW);
    pinMode(dischargePin, OUTPUT);
    digitalWrite(dischargePin, LOW);     //discharging the capacitor
    while (analogRead(analogPin) > 0) {
    }//This while waits till the capaccitor is discharged
    pinMode(dischargePin, INPUT);      //this sets the pin to high impedance
    Serial.println("DISCHARGING.....");
    //lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Discharging");
    lcd.setCursor(15, 2);
    lcd.print(state);
  }

  if (state == 7) { //mode.......................................7
    //lcd.clear();
    average = 0;
    for (int i = 0; i < 1000; i++) {
      average = average + (0.0264 * analogRead(curr) - 13.51) / 1000;
      delay(1);
    }
    Serial.println("Current is: ");
    Serial.println(average);
    lcd.setCursor(0, 0);
    lcd.print("Current is: ");
    lcd.setCursor(2, 2);
    lcd.print(average);
    lcd.setCursor(15, 2);
    lcd.print(state);
  }

  if (state == 8) { //mode.......................................8
    //lcd.clear();
    R2 = 0;
    average = analogRead(resistor);
    Vou = (average * 5.1) / 1024.0;
    R2 =  11.0 / Vou - 2.2;
    Serial.println("Resistance is: ");
    Serial.println(R2);
    lcd.setCursor(0, 0);
    lcd.print("Resistance is: ");
    lcd.setCursor(2, 2);
    lcd.print(R2);
    lcd.setCursor(15, 2);
    lcd.print(state);
    delay(500);
  }

  if (state == 1) { //mode.......................................1
    //lcd.clear();
    delay(2000);
    float h = dht.readHumidity();
    // Read temperature in C
    float t = dht.readTemperature();

    if (isnan(h) || isnan(t)) {
      Serial.println(F("Failed to read from DHT sensor!"));
      return;
    }

    // Compute heat index in Celsius (isFahreheit = false)
    float hic = dht.computeHeatIndex(t, h, false);

    Serial.print("Hum: ");
    Serial.print(h);
    Serial.print("%  Temp in C: ");
    Serial.print(t);
    Serial.print("  HIndex in C ");
    Serial.println(hic);
    lcd.setCursor(0, 0);
    lcd.print("HUM    Tem");
    lcd.setCursor(0, 2);
    lcd.print(h);
    lcd.setCursor(8, 2);
    lcd.print(t);
    lcd.setCursor(15, 2);
    lcd.print(state);
  }
  if (state == 2) { //mode.......................................2
    start_time = 0;
    int x = digitalRead(13);
    if (x == 0) {
      if (!(count % 2 == 0)) {
        stop_time = millis();
        ar[0] = stop_time;
        count++;
        //lcd.print("stop time : ");
        //lcd.print(stop_time);
        float z = (ar[0] - ar[1]) / 100;
        //lcd.print(z);
        float frequency = (1.0 / z);
        float omega = 60 * z;
        lcd.setCursor(0, 0);
        lcd.print("RPM: ");
        lcd.setCursor(2, 2);
        lcd.print(omega);
        Serial.println("RPM: ");
        Serial.println(omega);

      }
      else {
        start_time = millis();
        ar[1] = start_time;
        delay(350);
        count++;
        //lcd.print("start time : ");
        //lcd.print(start_time);
      }
    }
    delay(100);
  }

  if (state == 3) { //mode.......................................3
    //ultrasonic sensor
    digitalWrite(trigPin, LOW);
    delayMicroseconds(2);
    // Sets the trigPin HIGH/ACTIVE for 10 microseconds
    digitalWrite(trigPin, HIGH);
    delayMicroseconds(10);
    digitalWrite(trigPin, LOW);
    // Reads the echoPin, returns the sound wave travel time in microseconds
    duration = pulseIn(echoPin, HIGH);
    // Calculating the distance
    distance = duration * 0.034 / 2; // Speed of sound wave divided by 2 (go and back)
    // Displays the distance on the Serial Monitor
    lcd.setCursor(0, 0);
    lcd.print("Distance is: "); // Prints Sensor Val: to LCD
    lcd.setCursor(2, 2);
    lcd.print(distance);
    Serial.println("Distance measured: ");
    Serial.println(distance);
    delay(250);
    i = i + 1;
  }

  //Serial.println("act");
  //Serial.println(act);
  Serial.println(state);
  //Serial.println("act1");
  //Serial.println(act1);
  delay(250);
}
