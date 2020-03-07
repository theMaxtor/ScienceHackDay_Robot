/*******************************************************************************************************
* Test DC Motors Funtionality
* Created 7/11/16
* 
*
*
*
*******************************************************************************************************/
#include <Servo.h> 

//Define Servo Pin
int servoPin = 7;
Servo Servo1; 

//Define motors pins
int motor_left[] = {9, 6};
int motor_right[] = {8, 10};

//Define HC-SR04 pins
#define trig 4
#define echo 2

//Define global variable
long duration, distance;

//Function to stop the wheels
void wheels_stop()
  {
    analogWrite(motor_left[0], 0);
    analogWrite(motor_left[1], 0);
    analogWrite(motor_right[0], 0);
    analogWrite(motor_right[1], 0);
    delay(600);
  }

//Function to make the robot goes straight
void go_straight(int speed1, int speed2)
  {
    analogWrite(motor_left[0], speed1);
    analogWrite(motor_left[1], 0);
    analogWrite(motor_right[0], 0);
    analogWrite(motor_right[1], speed2);
    delay(600);
  }

//Function to make the roboto goes back
void go_back(int speed1, int speed2)
  {
    analogWrite(motor_left[0], 0);
    analogWrite(motor_left[1], speed1);
    analogWrite(motor_right[0], speed2);
    analogWrite(motor_right[1], 0);
    delay(600); 
  }

//Function to make the robot turns left
void turn_left(int speed1)
  {
    analogWrite(motor_left[0], 0);
    analogWrite(motor_left[1], 0);
    analogWrite(motor_right[0], 0);
    analogWrite(motor_right[1], speed1);
    delay(600);
  }

//Function to make the roboto turns right
void turn_right(int speed1)
  {
    analogWrite(motor_left[0], 0);
    analogWrite(motor_left[1], speed1);
    analogWrite(motor_right[0], 0);
    analogWrite(motor_right[1], 0);
    delay(600);
  }



void move_servo(Servo object, int desired_angle)
{
  int actual_angle = object.read();
  for (actual_angle; actual_angle != desired_angle; )
  {
    if (actual_angle > desired_angle)
    {
      actual_angle += 1;
      
    }
    else
    {
      actual_angle -= 1;
    }
    object.write(actual_angle);
  }
}

int read_distance()
{
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  duration = pulseIn(echo, HIGH);
  distance = duration / 58;
}




void setup() {
  
  //Initialize Serial
  Serial.begin(9600);

  //Set pin mode for HC-SR04 device
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  
  //Setup Motors
  for (int i = 0; i < 2; i++)
  {
    pinMode(motor_left[i], OUTPUT);
    pinMode(motor_right[i], OUTPUT);
  }

  //Initialize Servo object
  Servo1.attach(servoPin); 

  //Rotate servo from 0 to 180
  int angle =0;

  for(angle = 0; angle < 180; angle += 1)    // command to move from 0 degrees to 180 degrees 
  {                                  
    Servo1.write(angle);                 //command to rotate the servo to the specified angle
    delay(15);                       
  } 

  //Rotate servo from 180 to 0
  for(angle = 180; angle > 0; angle -= 1)    // command to move from 0 degrees to 180 degrees 
  {                                  
    Servo1.write(angle);                 //command to rotate the servo to the specified angle
    delay(15);                       
  } 


  //Put servo to the front
  Servo1.write(70);
  
}



void loop()
{
  Serial.print("Actual Distance: ");
  int distance = read_distance();
  Serial.println(distance);
  //if distance > 15 go straight
  if (distance > 15) 
  {
    Serial.println("Go straight");
    go_straight(255,255);
  }
  else
  {
    Serial.println("Stop Wheels");
    wheels_stop();
    move_servo(Servo1, 0);
    Serial.print("Distance from right object: ");
    distance = read_distance();
    Serial.println(distance);
    if (distance > 15)
    {
      Serial.println("Go right");
      turn_right(255);
      move_servo(Servo1, 70);
    }
    else
    {
      move_servo(Servo1, 170);
      Serial.print("Distance from left object: ");
      distance = read_distance();
      Serial.println(distance);
      if (distance > 15)
      {
        Serial.println("Go left");
        turn_left(255);
        move_servo(Servo1, 70);
      }
      else
      {
        Serial.println("Go back");
        go_back(255,255);
        move_servo(Servo1, 70);
      }
    }
  }
  delay(100);
}
