#include <Servo.h>

int lastState = LOW;
int STEP = 5;
int DIFF = 150;

Servo myservo1;
int servoPin1 = 4;

Servo myservo2;
int servoPin2 = 3;

int ur = A0; // select the input pin for LDR up-right
int ur_value = 0; // variable to store the value coming from the sensor

int dr = A2; // select the input pin for LDR down-right
int dr_value = 0; // variable to store the value coming from the sensor

int ul = A1; // select the input pin for LDR up-left
int ul_value = 0; // variable to store the value coming from the sensor

int dl = A3; // select the input pin for LDR down-left
int dl_value = 0; // variable to store the value coming from the sensor

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_BUILTIN, OUTPUT);
  myservo1.attach(servoPin1);
  myservo2.attach(servoPin2);
  myservo1.write(0);
  myservo2.write(0);
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
//
//  for (int pos = 0; pos <= 170; pos += 5) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(50);                       // waits 15ms for the servo to reach the position
//  }
//  
//  for (int pos = 170; pos >= 0; pos -= 5) { // goes from 180 degrees to 0 degrees
//    myservo1.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(50);                       // waits 15ms for the servo to reach the position
//  }
//  delay(1000);
//  for (int pos = 0; pos <= 170; pos += 5) { // goes from 0 degrees to 180 degrees
//    // in steps of 1 degree
//    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(50);                       // waits 15ms for the servo to reach the position
//  }
//  
//  for (int pos = 170; pos >= 0; pos -= 5) { // goes from 180 degrees to 0 degrees
//    myservo2.write(pos);              // tell servo to go to position in variable 'pos'
//    delay(50);                       // waits 15ms for the servo to reach the position
//  }
  
  ur_value = analogRead(ur); // read the value from up-right
  dr_value = analogRead(dr); // read the value from down-right
  ul_value = analogRead(ul); // read the value from up-left
  dl_value = analogRead(dl); // read the value from down-left
  int avg_top = ur_value + ul_value;
  int avg_down = dr_value + dl_value;
  int avg_right = ur_value + dr_value;
  int avg_left = ul_value + dl_value;
  int posx = myservo1.read();
  int posy = myservo2.read();

  if (avg_top > avg_down && avg_top - DIFF > avg_down && posy - STEP >= 0) {
    myservo2.write(posy-STEP);
  } else if (avg_top < avg_down && avg_top < avg_down - DIFF && posy + STEP <= 170) {
    myservo2.write(posy+STEP);
  }
  delay(50);
    if (avg_left > avg_right && avg_left - DIFF > avg_right && posx - STEP >= 0) {
    myservo1.write(posx-STEP);
  } else if (avg_left < avg_right && avg_left < avg_right - DIFF && posx + STEP <= 170) {
    myservo1.write(posx+STEP);
  }
  Serial.print("Value up-right: ");
  Serial.println(ur_value); //prints the values coming from the sensor on the screen

  Serial.print("Value down-righ: ");
  Serial.println(dr_value); //prints the values coming from the sensor on the screen

  Serial.print("Value up-left: ");
  Serial.println(ul_value); //prints the values coming from the sensor on the screen

  Serial.print("Value down-left: ");
  Serial.println(dl_value); //prints the values coming from the sensor on the screen

  Serial.println("\n");

  Serial.print("Avgtop: ");
  Serial.println(avg_top); //prints the values coming from the sensor on the screen

  Serial.print("Avg down: ");
  Serial.println(avg_down); //prints the values coming from the sensor on the screen

  Serial.print("Avgleft: ");
  Serial.println(avg_left); //prints the values coming from the sensor on the screen

  Serial.print("Avg right: ");
  Serial.println(avg_right); //prints the values coming from the sensor on the screen

    Serial.print("posx: ");
  Serial.println(posx); //prints the values coming from the sensor on the screen

    Serial.print("posy: ");
  Serial.println(posy); //prints the values coming from the sensor on the screen

  ledBlink();
  delay(200);
}

void ledBlink () {
  digitalWrite(LED_BUILTIN, lastState);
  if (lastState == LOW) {
    lastState = HIGH;
  } else {
    lastState = LOW;
  }
}
