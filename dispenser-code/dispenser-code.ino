/*
   PILL DISPENSER FIRMWARE
Pin mappings:

**SERVOS**
Servo 1: D5
Servo 2: D6

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

//General Pin Mappings

//Servos
#define SERVO1 5
#define SERVO2 6

//RTC
#define RTC_CLK 1
#define RTC_DAT 2
#define RTC_RST 3

//RFID
#define RFID_RST 9
#define RFID_MISO 10
#define RFID_MOSI 11
#define RFID_SCK 12
#define RFID_SDA 13

//Misc
#define BUZZER 8
#define PHOTO 0

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

int n = 1;

LiquidCrystal_I2C  lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);

void setup()
{
 lcd.begin (16,2); //  <<----- My LCD was 16x2

 
// Switch on the backlight
lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
lcd.setBacklight(HIGH);
lcd.home (); // go home

 lcd.print("Guhaaaaaaaaaaa");  
 delay(1000);
}

void loop()
{
	for (int y = 0; y<2; y++)
	{
		for (int x = 0; x < 16; x++)
		{
			lcd.clear();
			lcd.setCursor(x,y);
			lcd.print("O");
			delay(2000/16);
		}
	}

}




