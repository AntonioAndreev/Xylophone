#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

#include "Servo.h"

int servo0Pin = 2;
int servo1Pin = 3;
int servo2Pin = 4;
int servo3Pin = 5;

int buttonPin = 6;

int play1[] = {0+8,0+8,1+8,0+8,3+8,2+8,0+8,0+8,1+8,0+8,4+8,3+8,0+8,0+8,7+8,5+8,3+8,2+8,1+8,0+8,0+8,5+8,3+8,4+8,3+8,0+8,0+8,1+8,0+8,3+8,2+8,0+8,0+8,1+8,0+8,4+8,3+8,0+8,0+8,7+8,5+8,3+8,2+8,1+8,0+8,0+8,5+8,3+8,4+8,3+8,0+8,0+8,1+8,0+8,3+8,2+8,0+8,0+8,1+8,0+8,4+8,3+8,0+8,0+8,7+8,5+8,3+8,2+8,1+8,0+8,0+8,5+8,3+8,4+8,3+8};
int play2[] = {8,9,3,3,3,3,3,3,3,8,9,3,3,3,3,3,3,3,8,9,3,3,3,3,3,3,3,11,11,10};
int play3[] = {16,20,3,2,1,23,20,3,2,1,23,20,3,2,3,17};

int positions[] = {132,122,112,102,52,42,30,22};
int playSpeeds[2][3] = {
  {150, 300, 500},
  {50, 100, 150}
};

int sizeOfPositions, playTone, playSpeed;
int currentSong = 0;

Servo servo0;
Servo servo1;
Servo servo2;
Servo servo3;

void setup() {
  lcd.begin();
  lcd.backlight();

  servo0.attach(servo0Pin);
  servo1.attach(servo1Pin);
  servo2.attach(servo2Pin);
  servo3.attach(servo3Pin);

  noPlay();
 
  pinMode(buttonPin, INPUT);
}

void loop() {
  if (digitalRead(buttonPin)) {
    currentSong++;
    switch(currentSong) {
      case 1:
        lcd.clear();
        lcd.print("Playing song: 1");
        play(play1, sizeof(play1) / sizeof(int));
        break;
      case 2:
        lcd.clear();
        lcd.print("Playing song: 2");
        play(play2, sizeof(play2) / sizeof(int));
        break;
      case 3:
        lcd.clear();
        lcd.print("Playing song: 3");
        play(play3, sizeof(play3) / sizeof(int));
        break;
      default:
        currentSong = 0;
    }
  }
}

void play(int play[], int sizeOfPlay) {
  sizeOfPositions = sizeof(positions) / sizeof(int);
  for(int i = 0; i < sizeOfPlay; i++){
    playTone = play[i];
    playSpeed = 0;
    while (playTone > 7) {
      playTone %= 8;
      playSpeed += 1;
    }
    if(playTone < sizeOfPositions / sizeof(int)){
      servo0.write(positions[playTone]);
      delay(playSpeeds[0][playSpeed]);
      servo1.write(20);
      delay(playSpeeds[1][playSpeed]);
      servo1.write(30);
    } else {
      servo2.write(positions[playTone]);
      delay(playSpeeds[0][playSpeed]);
      servo3.write(25);
      delay(playSpeeds[1][playSpeed]);
      servo3.write(10);
    }
  }
  noPlay();
}

void noPlay() {
  lcd.clear();
  lcd.print("Not playing song");
  servo0.write(115);
  servo1.write(30);
  servo2.write(35);
  servo3.write(10);
  delay(1000);
}
