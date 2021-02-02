#include <Servo.h>

#define ENABLE 5
#define DIRA 3
#define DIRB 4
#define SERVO_PIN 9

Servo myservo;


void setup() {
  pinMode(ENABLE, OUTPUT);
  pinMode(DIRA, OUTPUT);
  pinMode(DIRB, OUTPUT);

  myservo.attach(SERVO_PIN);
  myservo.write(90);

  Serial.begin(9600);
}

void loop() {
  goFast();
  moveAround();
}


void goFast() {
  Serial.println("Go!");
  digitalWrite(ENABLE, HIGH);
  digitalWrite(DIRA, HIGH);
  digitalWrite(DIRB, LOW);
  delay(1000);
}

void moveAround() {
  myservo.write(90);
  delay(1000);
  myservo.write(40);
  delay(1000);
  myservo.write(90);
  delay(1000);
  myservo.write(120);
  delay(1000);
}
