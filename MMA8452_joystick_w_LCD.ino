#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <I2C.h>
#include <MMA8453_n0m1.h>
#include <Comp6DOF_n0m1.h>
 
#define I2C_ADDR    0x27  // Define I2C Address where the PCF8574A is
#define BACKLIGHT_PIN     3
#define En_pin  2
#define Rw_pin  1
#define Rs_pin  0
#define D4_pin  4
#define D5_pin  5
#define D6_pin  6
#define D7_pin  7

// data structure as defined by the joystick firmeware
struct {
    int8_t x;
    int8_t y;
    uint8_t buttons;
    uint8_t rfu;
} joyReport;

int x, y;

LiquidCrystal_I2C       lcd(I2C_ADDR,En_pin,Rw_pin,Rs_pin,D4_pin,D5_pin,D6_pin,D7_pin);
MMA8453_n0m1 accelerometer;

void setup()
{
  lcd.begin (16,2,LCD_5x8DOTS);
  lcd.setBacklightPin(BACKLIGHT_PIN,POSITIVE);
  Serial.begin(115200);
  accelerometer.setI2CAddr(0x1D);
  accelerometer.dataMode(true, 2);
  lcd.setBacklight(HIGH);
}
 
void loop()
{
  accelerometer.update();
  x = constrain(((int)(map(accelerometer.x(), -250, 250, 0, 100))), 0, 100);
  y = constrain(((int)(map(accelerometer.y(), -250, 250, 0, 100))), 0, 100);
  
  lcd.setCursor(0,0);
 
  lcd.print("SL tilt joystick");
  
  lcd.setCursor(0,1);
  
  lcd.print("x: ");
  lcd.print(x);
  
  lcd.setCursor(8,1);
  
  lcd.print("y: ");
  lcd.print(y);  

  joyReport.buttons = 0;
  joyReport.rfu = 0;
  joyReport.x = x;
  joyReport.y = y;
  Serial.write((uint8_t *)&joyReport, 4);

  delay(250);
  lcd.clear();
}
