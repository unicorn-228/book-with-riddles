#include <Servo.h>
#include "Wire.h"

// I2Cdev and MPU6050 must be installed as libraries, or else the .cpp/.h files
// for both classes must be in the include path of your project
#include "I2Cdev.h"
#include "MPU6050.h"

#define led1 13
#define led2 12
#define led3 11
#define circle A0
#define servoPin 8
#define chessSwitch1 A1
#define chessSwitch2 A2

bool questDone1 = false;
bool questDone2 = false;
bool questDone3 = false;

Servo servo;

MPU6050 accelgyro;

int16_t ax, ay, az;
int16_t gx, gy, gz;


void lockServo() {
    servo.write(0);
}

void unlockServo() {
    servo.write(180);
}

void made1 (){
    digitalWrite(led1 ,HIGH);
    questDone1 = true;
}

void made2 (){
    digitalWrite(led2 , HIGH);
    questDone2 = true;
}

void made3 (){
    digitalWrite(led3 , HIGH);
    questDone3 = true;
}

bool checkQuest1 () {
    int value = analogRead(circle);
    if( (value < 960) && (value > 850) ) { //this vaules are just for my potentiometer.
                                           //you need to choose suitable for your once
        return true;
    }
    return false;
}

bool checkQuest2() {
  accelgyro.getMotion6(&ax, &ay, &az, &gx, &gy, &gz);   
    if( (ay > -17000) && (ay < -11000) )
        return true;
    return false;
}

bool checkQuest3 () {
    if(analogRead(chessSwitch1) > 100 && analogRead(chessSwitch2) > 100) {
        return true;
    }
    return false;
}

void setup() {
    pinMode(circle , INPUT);
    pinMode(chessSwitch1 , INPUT);
    pinMode(chessSwitch2 , INPUT);
    pinMode(led1 , OUTPUT);
    pinMode(led2 , OUTPUT);
    pinMode(led3 , OUTPUT);
  
    servo.attach(servoPin);
    Wire.begin();
    Serial.begin(38400);
    accelgyro.initialize();

    
    lockServo();
}

void loop() {
    while(true) {
      delay(300);
        if(!questDone1) {
            if(checkQuest1())
              made1(); 
        } else {
            if(!questDone2) {
             if(checkQuest2()){
                      made2(); 
             }
            } else {
                if(!questDone3) {
                   if(checkQuest3()){
                      made3(); 
                   break;
                   }
                }
            }
        }
    }
    unlockServo();
    
   
    delay(1000);
}
