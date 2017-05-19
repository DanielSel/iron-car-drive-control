#include <EnableInterrupt.h>


#include <Servo.h>

/*
 Name:    NewMotorControl.ino
 Created: 15-May-17 11:25:44 AM
 Author:  Daniel
*/

#include "Arduino.h"

Servo motor;
Servo servo;


#define PWM_OUTPUT_SERVO 9
#define PWM_OUTPUT_MOTOR 10

#define PWM_INPUT_SERVO 11
#define PWM_INPUT_MOTOR 12

// the setup function runs once when you press reset or power the board
void setup() {
 Serial.begin(19200);
 pinMode(PWM_INPUT_MOTOR, INPUT_PULLUP);
 pinMode(PWM_INPUT_SERVO, INPUT_PULLUP);
 motor.attach(PWM_OUTPUT_MOTOR);
 servo.attach(PWM_OUTPUT_SERVO);
 motor.writeMicroseconds(1500);
 servo.writeMicroseconds(1500);
 enableInterrupt(PWM_INPUT_MOTOR, debugProcessEdgeChangeRISING_MOTOR, RISING);
 enableInterrupt(PWM_INPUT_SERVO, debugProcessEdgeChangeRISING_SERVO, RISING);
}

// the loop function runs over and over again until power down or reset
void loop() {
  int time = millis();
  debugLoop(time);
  controlLoop(time);
}

// ------------------
// DEBUG STUFF
// ------------------

volatile int previousTime_MOTOR = 0;
volatile int pwmTime_MOTOR = 0;

volatile int previousTime_SERVO = 0;
volatile int pwmTime_SERVO = 0;

volatile int rising_MOTOR = 0;
volatile int falling_MOTOR = 0;

volatile int rising_SERVO = 0;
volatile int falling_SERVO = 0;

void debugLoop(int time)
{
  static int lastExecutionTime = 0;
  if (time - lastExecutionTime > 500)
  {
    Serial.println("MOTOR says: " + static_cast<String>(pwmTime_MOTOR));
    Serial.println("MOTOR Rising: " + static_cast<String>(rising_MOTOR));
    Serial.println("MOTOR Falling: " + static_cast<String>(falling_MOTOR));
    Serial.println("SERVO says: " + static_cast<String>(pwmTime_SERVO));
    Serial.println("SERVO Rising: " + static_cast<String>(rising_SERVO));
    Serial.println("SERVO Falling: " + static_cast<String>(falling_SERVO));
    lastExecutionTime = time;
  }
}

void controlLoop(int time)
{
  static int lastExecutionTime = 0;
  if (time - lastExecutionTime > 20)
  {
    
    motor.writeMicroseconds(pwmTime_MOTOR);
    servo.writeMicroseconds(pwmTime_SERVO);
    lastExecutionTime = time;
  }
}

void debugProcessEdgeChangeRISING_MOTOR()
{
  previousTime_MOTOR = micros();
  rising_MOTOR++;
  enableInterrupt(PWM_INPUT_MOTOR, debugProcessEdgeChangeFALLING_MOTOR, FALLING);
}
void debugProcessEdgeChangeFALLING_MOTOR()
{
  pwmTime_MOTOR = micros() - previousTime_MOTOR;
  falling_MOTOR++;
  enableInterrupt(PWM_INPUT_MOTOR, debugProcessEdgeChangeRISING_MOTOR, RISING);
}


void debugProcessEdgeChangeRISING_SERVO()
{
  previousTime_SERVO = micros();
  rising_SERVO++;
  enableInterrupt(PWM_INPUT_SERVO, debugProcessEdgeChangeFALLING_SERVO, FALLING);
}
void debugProcessEdgeChangeFALLING_SERVO()
{
  pwmTime_SERVO = micros() - previousTime_SERVO;
  falling_SERVO++;
  enableInterrupt(PWM_INPUT_SERVO, debugProcessEdgeChangeRISING_SERVO, RISING);
}

