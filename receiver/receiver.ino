#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <AFMotor.h>
#define S1 255
#define S2 200
#define S3 150
#define STOP 400

AF_DCMotor motor1(1);
AF_DCMotor motor2(2);
AF_DCMotor motor3(3);
AF_DCMotor motor4(4);
RF24 radio(48, 53);
int motor_speed;
const byte rxAddr[6] = "00003";
int motor_direction1;
int motor_direction2;
int motor_direction3;
int motor_direction4;
void setup()
{
   // turn on motor
  motor1.setSpeed(200);
  motor2.setSpeed(200);
  motor3.setSpeed(200);
  motor4.setSpeed(200);

  motor1.run(RELEASE);
  motor2.run(RELEASE);
  motor3.run(RELEASE);
  motor4.run(RELEASE);
  while (!Serial);
  Serial.begin(9600);
  Serial.print("start");
  radio.begin() ;
  radio.openReadingPipe(0, rxAddr);
  
  radio.startListening();
}

void loop()
{
  Serial.println("loop");
  double text = 400;
  if (radio.available()) {
      radio.read(&text, sizeof(text));
      Serial.println("here");
      Serial.println(text);
       int x = text;
       if (x == STOP) {
         motor_direction1 = RELEASE;
         motor_direction2 = RELEASE;
         motor_direction3 = RELEASE;
         motor_direction4 = RELEASE;
      } else if (x % 90 == 0) {
          motor_speed = S1; 
          if (x == 270) {
            motor_direction1 = BACKWARD;
            motor_direction2 = BACKWARD;
            motor_direction3 = BACKWARD;
            motor_direction4 = BACKWARD;
          }else {
            motor_direction1 = FORWARD;
            motor_direction2 = FORWARD;
            motor_direction3 = FORWARD;
            motor_direction4 = FORWARD; 
          }
      } else if (x % 180 < 45) {
        motor_speed = S2;
        if (x < 45) {
         motor_direction1 = RELEASE;
         motor_direction2 = RELEASE;
         motor_direction3 = FORWARD;
         motor_direction4 = FORWARD;

        } else {
         motor_direction1 = BACKWARD;
         motor_direction2 = BACKWARD;
         motor_direction3 = RELEASE;
         motor_direction4 = RELEASE;
        } 
      } else if (x % 180 < 90) {
        motor_speed = S3;
        if (x < 90) {
         motor_direction1 = RELEASE;
         motor_direction2 = RELEASE;
         motor_direction3 = FORWARD;
         motor_direction4 = FORWARD;
        } 
        else {
         motor_direction1 = BACKWARD;
         motor_direction2 = BACKWARD;
         motor_direction3 = RELEASE;
         motor_direction4 = RELEASE;
        } 
      } else if (x % 180 < 135) {
        motor_speed = S3;
        if (x < 135) {
         motor_direction1 = FORWARD;
         motor_direction2 = FORWARD;
         motor_direction3 = RELEASE;
         motor_direction4 = RELEASE;
        }
        else {
         motor_direction1 = RELEASE;
         motor_direction2 = RELEASE;
         motor_direction3 = BACKWARD;
         motor_direction4 = BACKWARD;
        } 
      } else if (x % 180 < 180) {
        motor_speed = S2;
        if (x < 180) {
         motor_direction1 = FORWARD;
         motor_direction2 = FORWARD;
         motor_direction3 = RELEASE;
         motor_direction4 = RELEASE;
        }  
        else {
         motor_direction1 = RELEASE;
         motor_direction2 = RELEASE;
         motor_direction3 = BACKWARD;
         motor_direction4 = BACKWARD;
        }
      }
      
    }
    motor1.setSpeed(motor_speed);
    motor2.setSpeed(motor_speed);
    motor3.setSpeed(motor_speed);
    motor4.setSpeed(motor_speed);
    motor1.run(motor_direction1);
    motor2.run(motor_direction2);
    motor3.run(motor_direction3);
    motor4.run(motor_direction4);
    delay(500);
}
