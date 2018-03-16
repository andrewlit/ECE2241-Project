/*
   PILL DISPENSER FIRMWARE
   Pin mappings:

 **SERVOS**
 Servo 1: D5	//Dispensing servo
 Servo 2: D6	//"Double-Check" servo

 **LCD**
 SCL, SDA

 **RFID**
RFID_RST: D9
RFID_MISO : D10
RFID_MOSI : D11
RFID_SCK  : D12
RFID_SDA : D13

 **RTC**
RTC_CLK: D1
RTC_DAT: D2
RTC_RST: D3

 **MISC**
BUZZER: D8
PHOTOR: A0
 */


#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

//General Pin Mappings

//Servos
#define SERVO1 5
#define SERVO2 6

//RTC
#define RTC_CLK 1
#define RTC_DAT 2
#define RTC_RST 3

//RFID (these maybe changed? or not?)
#define RFID_RST 9
#define RFID_MISO 10
#define RFID_MOSI 11
#define RFID_SCK 12
#define RFID_SDA 13

//Misc
#define BUZZER 8
#define PHOTO 0
#define PTRANS_P A1	//Not sure if this is right
#define PTRANS_S A2	//Not sure about this one either

//Display I2C mappings
#define I2C_ADDR    0x3F // <<----- Add your address here.  Find it from I2C Scanner
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

//Program Constants
#define DISPENSE_COLLECT 0
#define DISPENSE_RELEASE 100
#define PT_CLEAR	//FIND THIS VALUE
#define PT_BLOCKED	//FIND THIS VALUE

#define CHECK_CLOSE 90
#define CHECK_OPEN 180 
#define CHECK_DISCARD 0


//Object declarations
LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
Servo dispenseServo;
Servo checkServo;

void setup()
{
	//Pin mode assignments
	//Inputs
	pinMode(PHOTO, INPUT);
	pinMode(PTRANS_S, INPUT);

	//Outputs
	pinMode(PTRANS_P, OUTPUT);
	pinMode(BUZZER, OUTPUT);

	//Servos
	dispenseServo.attach(SERVO1);
	checkServo.attach(SERVO2);


	//Initialize the LCD
	lcd.begin (16,2); // LCD panel is 16x2 

	// Switch on the backlight
	lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
	lcd.setBacklight(HIGH);
	lcd.home (); // go home
}

void loop()
{
}

//Dispense function; dispense n pills
void dispense(int n)
{
	int count = 0;
	//Run this code n times
	for (int x =0; x < n; x++)
	{
		//Ensure the servo is at the home position
		dispenseServo.write(DISPENSE_COLLECT);

		//Open and drop the pill
		dispenseServo.write(DISPENSE_RELEASE);

		//Start polling the photointerrupter
		bool poll = 1;
		bool lastReading = 0, reading = 0, passed = 1;
		int startTime = millis();
		int runTime = 0;
		int dropTime = 0;
		byte attempts = 0;
		
		while (attempts < 3)
		{
			//Read the sensor value
			reading = analogRead(PTRANS_S) < PT_BLOCKED;

			if (reading) //The pill has passed the sensor
			{
				dropTime = millis(); //Note the time that the pill dropped
				passed = 1; //The pill has passed. Check for another	
			}

			//Check if it's taken too long
			if ( runTime > 500)
			{
				//Re-rotate the servo
				dispenseServo.write(DISPENSE_COLLECT);
				delay(150);
				dispenseServo.write(DISPENSE_RELEASE);

				//Reset the runtime
				startTime = millis;
				runTime =0 ;

				//Increment the attempts counter
				attempts ++;
			}


			//Update the amount of time of dispensing
			runTime = millis() - startTime();
		}

	}

}



