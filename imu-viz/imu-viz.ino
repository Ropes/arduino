#include <Arduino.h>
#include <U8g2lib.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BNO055.h>
#include <utility/imumaths.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0); 
Adafruit_BNO055 bno = Adafruit_BNO055(55);

 void setup(void) {
  u8g2.begin();

  Serial.begin(9600);
  Serial.println("Orientation Sensor Test"); Serial.println("");
  
  /* Initialise the sensor */
  if(!bno.begin())
  {
    /* There was a problem detecting the BNO055 ... check your connections */
    Serial.print("Ooops, no BNO055 detected ... Check your wiring or I2C ADDR!");
    while(1);
  }
  
  delay(1000);
    
  bno.setExtCrystalUse(true);
}

void loop(void) {
  /*
  u8g2.clearBuffer();         // clear the internal memory
  u8g2.setFont(u8g2_font_logisoso28_tr);  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
  u8g2.drawStr(4,29,"katie");  // write something to the internal memory
  u8g2.sendBuffer();         // transfer internal memory to the display
  delay(800);
  

  /* Get a new sensor event */ 
  sensors_event_t event, quatData, magData, gravData; 
  bno.getEvent(&event);
  bno.getEvent(&magData, Adafruit_BNO055::VECTOR_MAGNETOMETER);
  bno.getEvent(&gravData, Adafruit_BNO055::VECTOR_GRAVITY);


  
  
  /* Display the floating point data */
  Serial.print("X: ");
  Serial.print(event.orientation.x, 4);
  Serial.print("\tY: ");
  Serial.print(event.orientation.y, 4);
  Serial.print("\tZ: ");
  Serial.print(event.orientation.z, 4);
  Serial.println("");
  

  char buff[40];
  char x[7];
  dtostrf(event.orientation.x, 6, 1, x);
  char y[7];
  dtostrf(event.orientation.y, 6, 1, y);

/*
  float[3] v;
  v = gravData.acceleration.v;
  char vx[7];
  char vy[7];
  char vz[7];
  dtostrf(v[0], 6, 1, vx);
  dtostrf(v[1], 6, 1, vy);
  dtostrf(v[2], 6, 1, vz);
*/


  u8g2.clearBuffer();         // clear the internal memory
  // choose a suitable font at https://github.com/olikraus/u8g2/wiki/fntlistall
  u8g2.setFont(u8g2_font_mercutio_basic_nbp_tf);
  sprintf(buff, "X: %s   Y: %s", x, y);
  u8g2.drawStr(0,15, buff);  // write something to the internal memory


  char z[7];
  dtostrf(event.orientation.z, 6, 1, z);
  //char p[7];
  //dtostrf(event.temperature, 6, 1, p);
  sprintf(buff, "Z: %s  tempC: %d", z, bno.getTemp());
  u8g2.drawStr(0,32, buff);  // write something to the internal memory

  u8g2.sendBuffer();         // transfer internal memory to the display
  delay(100);
 
}

