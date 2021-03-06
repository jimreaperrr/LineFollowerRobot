#include <AFMotor.h>
AF_DCMotor motor1(2); //motor1 (front left) is m2
AF_DCMotor motor2(4); // motor2 (front right) is m4

AF_DCMotor motor3(1); //motor3 (rear left) is m1
AF_DCMotor motor4(3); //motor4 (rear right) is m3

//ir sensors connected to pwm / This should change accordingly
int left = digitalRead(A0);
int right = digitalRead(A1);
//int value = 0;

//integer variables

int Left = 0;
int Right = 0;

//calling functions inside loop
void LEFT(void);
void RIGHT(void);
void STOP(void);


void setup() {

  AF_DCMotor motor1(2, OUTPUT); //motor1 (front left) is m2
  AF_DCMotor motor2(4, OUTPUT); // motor2 (front right) is m4

  AF_DCMotor motor3(1, OUTPUT); //motor3 (rear left) is m1
  AF_DCMotor motor4(4, OUTPUT); //motor4 (rear right) is m3

  //set up ir sensors
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);


  //turn on ir sensors
  digitalWrite(A0, HIGH);
  digitalWrite(A1, HIGH);
  Serial.begin(9600);

}

void loop() {

  motor1.setSpeed(250); //0 to 255 as 0 is off and 255 is full throttle
  motor2.setSpeed(250); //maybe set 0
  motor3.setSpeed(250);
  motor4.setSpeed(250); //maybe set 0 */
  /*
    int left = analogRead(A0);
    int right = analogRead(A1);
    Serial.println(left);
    Serial.println(right); */
  /*motor1.setSpeed(250); //0 to 255 as 0 is off and 255 is full throttle
    motor2.setSpeed(0); //maybe set 0
    motor3.setSpeed(250);
    motor4.setSpeed(0); //maybe set 0*/
  // Direction
  motor1.run(FORWARD);
  motor2.run(FORWARD);
  motor3.run(FORWARD);
  motor4.run(FORWARD);


  /*try different combinations of forward and backward to spin in a circle
    try the same directions to go the same direction
    motor2.run(BACKWARD); make wheels go backwards
    motor2.run(RELEASE); stops the motor
    motor1.setSpeed(100); set speed here is fine as well
  */

  /*wonder if we have to set speed by analog
    analogWrite(motor1,250);
    analogWrite(motor2,0);
    analogWrite(mot3,250);
    analogWrite(motor4,0);
  */

  //this loop is reading inputs from both ir sensors
  while (1) {
    //reading inputs
    Left = /*analogRead(left);*/ digitalRead(A0);
    Right = /*analogRead(right);*/ digitalRead(A1);

    //if left ir sensor didnt detect anything, run left again
    if ((Left == 0 && Right == 1 ) == 1) // if ((Left == 0 && Right == 1) == 1)
      LEFT();

    //if right ir sensor didn't detect anyting, run right again
    else if ((Right == 0 && Left == 1) == 1) //((Right == 0 && Left == 1) == 1)
      RIGHT();
  }

}

//left ir sensor function
void LEFT(void) {
  motor1.setSpeed(30);
  motor2.setSpeed(0);
  motor3.setSpeed(30); //analogWrite(motor3, 0);
  motor4.setSpeed(0);//analogWrite(motor4, 30);

  //from loop
  while (Left == 0) {
    //try reading inputs again
    Left = digitalRead(A0); //analogRead(left);
    Right = digitalRead(A1); //analogRead(right);
    //this time if Right ir sensor didn't get anything
    if (Right == 0) {
      //new variables
      int lprev = Left;
      int rprev = Right;
      //bascially in this while loop if left is still 0 and right is also 0 then stop
      STOP();
      //while both ir sensors are receving inputs correctly
      while (((lprev == Left) && (rprev == Right)) == 1) {
        //keep reading inputs
        Left = digitalRead(A0); //analogRead(left);
        Right = digitalRead(A1); //analogRead(right);
      }

    }
    //honestly I'm stuck here
    motor1.setSpeed(250); //analogWrite(motor1, 250);
    motor2.setSpeed(0); //analogWrite(motor2, 0);
    motor3.setSpeed(250);
    motor4.setSpeed(0);

  }
  //same
  motor1.setSpeed(250);
  motor2.setSpeed(0);
  motor3.setSpeed(250); //analogWrite(motor3, 250);
  motor4.setSpeed(0); //analogWrite(motor4, 0);
}

// right ir sensor function
void RIGHT(void) {
  {
    motor1.setSpeed(0); // analogWrite(motor1, 0);
    motor2.setSpeed(30); //analogWrite(motor2, 30);
    motor3.setSpeed(0);
    motor4.setSpeed(30);

    while (Right == 0)
    {
      Left = digitalRead(A0); //analogRead(left);
      Right = digitalRead(A1); //analogRead(right);
      if (Left == 0)
      {
        int lprev = Left;
        int rprev = Right;
        STOP();
        while (((lprev == Left) && (rprev == Right)) == 1)
        {
          Left = digitalRead(A0); //analogRead(left);
          Right = digitalRead(A1); //analogRead(right);
        }
      }
      motor1.setSpeed(0);
      motor2.setSpeed(250);
      motor3.setSpeed(0); //analogWrite(motor3, 255);
      motor4.setSpeed(250); //analogWrite(motor4, 0);
    }
    motor1.setSpeed(0); //analogWrite(motor1, 255);
    motor2.setSpeed(250); // analogWrite(motor2, 0);
    motor3.setSpeed(0); //analogWrite(motor3, 255);
    motor4.setSpeed(250);
  }
}

//calling this function stops all motor
void STOP(void) {
  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);

  loop();

}



