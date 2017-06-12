//Schiltz Quentin
//quentin.schiltz@tum.de

#include <NewPing.h> // Ultrasonic
#include <PinChangeInterrupt.h> // enable Interrupts on other pins
#include <TimerOne.h> // PWM generation and interrupt timer

//Pins Steering & Motor
#define pwmPin1 9 // Steering PWM 11/12/13 // Nano 9,10
#define pwmPin2 10 // Motor PWM 11/12/13




//////////////////////////////////////////////////////////////////////////////
//UltraSonic Pins
#define TRIGGER_PIN  7  // Ultrasonic
#define ECHO_PIN     7 //
#define MAX_DISTANCE 300 // in cm, defines when timeout cut off will be

///////////////////////////////////////////////////////////////////////////




//speed control    ; 50 << neutral: 76 >> forward: 102
#define speedMax 100   //0-100 -forward; 
#define MaxPwm 102
#define SpeedMin -100  //0- -100 reverse
#define MinPwm  50

// Display for Demo, remove to save 30% memory
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 4
Adafruit_SSD1306 display(OLED_RESET);
#define NUMFLAKES 10
#define XPOS 0
#define YPOS 1
#define DELTAY 2
#define LOGO16_GLCD_HEIGHT 16
#define LOGO16_GLCD_WIDTH  16

//read Serial
String message_1;
String message_2;
int  DesiredSpeed = 0; //via serial
float angle = 0;
int speedValue = 0;



/////////////////////////////////////////////////////////////
// for UltraSonic
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

int distance = 0;

unsigned long task1Timer = 0;



///////////////////////////////////////////////////////
// for Emergency Brake
int emergencySignal = 1;
int EBS = 0;



void setup() {
	Serial.begin(19200);


	//////////////////////////////////////////////////////////////
	// Start "Multitasking" Timer
	task1Timer = millis();
	//////////////////////////////////////////////////////////////



	//ini pwm signal
	Timer1.initialize(20000); // both PWM Signals have a 20ms period
	Timer1.pwm(pwmPin1, 0);
	Timer1.pwm(pwmPin2, 0);
	Timer1.setPwmDuty(pwmPin2, 77);  //write to motor
	Timer1.setPwmDuty(pwmPin1, 77);


	// Display Init
	display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
	display.clearDisplay();   // Clear the buffer
}
//////////////////////////////////////////////
int uS = 0;
void loop()
{

	if (millis() >= task1Timer) {
		task1Timer += 200;
		uS = sonar.ping_median(2); // 3m / 3values / 70ms)
		Mini_Display(); // update minidisplay
		serialM(); // Serieller Monitor Arduino IDE
	}
	distance = readPing(); // readPing() in Brake (UltrasSonic in CM) 

						   //Serial Communication
	if (receiveMessage())
	{
		DesiredSpeed = message_1.toFloat();
		angle = message_2.toFloat();


		//Set angle
		steering(angle);
		//
		if (!EBS && emergencySignal) {
			//set desired speed (map values)
			motor(DesiredSpeed);
		}

	}

	// Emergency Brake could be triggered when UltraSonic does not recognize the distance 
	//The distance will be set to 300 cm if the UltraSonic does not recognize the distance
	if (distance == 0 || distance == 5 || distance == 4) {
		distance = 300;
	}
	// off at the moment: Bachelor Thesis does not need this brake
	// test it
	////UltraSonic Emergency Brake
	//if (distance<= 70){ // when smaller than 70 cm
	//  EmergencyBrake(); //Brake
	//  delay(1);
	//  steering(-angle); //   reverse steering angle
	//  delay(1);
	//   motor(-25);          // without moving backward, the Brake will remain triggered
	//  delay(20);  
	//  EmergencyBrake(); // after the brake new values can be send
	//  delay(1);
	//  
	//}


}


