#include <Wire.h>
 
#define HMC6343_ADDRESS 0x19
#define HMC6343_HEADING_REG 0x50

// data structure as defined by the joystick firmeware
struct {
    int8_t x;
    int8_t y;
    uint8_t buttons;
    uint8_t rfu;
} joyReport;

void setup() {
  Wire.begin();          // initialize the I2C bus
  Serial.begin(115200);  // initialize the serial bus
}
 
void loop() {
  byte highByte, lowByte;
 
  Wire.beginTransmission(HMC6343_ADDRESS);    // start communication with HMC6343
  Wire.write(0x74);                           // set HMC6343 orientation
  Wire.write(HMC6343_HEADING_REG);            // send the address of the register to read
  Wire.endTransmission();
 
  Wire.requestFrom(HMC6343_ADDRESS, 6);       // request six bytes of data from the HMC6343
  while(Wire.available() < 1);                // busy wait while there is no byte to receive
 
  highByte = Wire.read();
  lowByte = Wire.read();
  float heading = ((highByte << 8) + lowByte) / 10.0; // heading in degrees
 
  highByte = Wire.read();
  lowByte = Wire.read();
  float pitch = ((highByte << 8) + lowByte) / 10.0;   // pitch in degrees
 
  highByte = Wire.read();
  lowByte = Wire.read();
  float roll = ((highByte << 8) + lowByte) / 10.0;    // roll in degrees

  joyReport.buttons = 0;
  joyReport.rfu = 0;
  
  joyReport.x = constrain(((int)(map(roll, -90, 90, -100, 100))), -100, 100);
  joyReport.y = constrain(((int)(map(pitch, -90, 90, -100, 100))), -100, 100);
  
  Serial.write((uint8_t *)&joyReport, 4);

  delay(100); // do this at approx 10Hz
}
