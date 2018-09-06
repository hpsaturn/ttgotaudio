#include <MPU9250_asukiaaa.h>
#include "Ring.h"

#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 19
#define SCL_PIN 18
#endif

MPU9250 mpu;
Ring ring = Ring();

void setup() {
  while(!Serial);
  Serial.begin(115200);
  Serial.println("started");

  #ifdef _ESP32_HAL_I2C_H_
  // for esp32
  Wire.begin(SDA_PIN, SCL_PIN); //sda, scl
  #else
  Wire.begin();
  #endif

  mpu.setWire(&Wire);
  mpu.beginAccel();
  mpu.beginMag();
  mpu.beginGyro();

  // you can set your own offset for mag values
  // mpu.magXOffset = -50;
  // mpu.magYOffset = -55;
  // mpu.magZOffset = -10;

}

void ringLoop(){
  ring.colorWipe(ring.Color(255, 0, 0), 50); // Red
  ring.colorWipe(ring.Color(0, 255, 0), 50); // Green
  ring.colorWipe(ring.Color(0, 0, 255), 50); // Blue
  ring.colorWipe(ring.strip.Color(0, 0, 0, 255), 50); // White
  ring.whiteOverRainbow(20,75,5);
  ring.pulseWhite(5);
  ring.fullWhite();
  delay(2000);
  ring.rainbowFade2White(3,3,1);
}

void mpuLoop(){
  mpu.accelUpdate();
  char buffer [60];
  float mSqr = mpu.accelSqrt();
  sprintf(buffer,"aX:%+.3f aY:%+.3f aZ:%+.3f aSqr:%.3f",mpu.accelX(),mpu.accelY(),mpu.accelX(),mSqr);
  Serial.print(buffer);
  mpu.magUpdate();
  sprintf(buffer," mX:%+08.3f mY:%+08.3f mZ:%+08.3f mDir:%+08.3f",mpu.magX(),mpu.magY(),mpu.magZ(),mpu.magHorizDirection());
  Serial.print(buffer);
  mpu.gyroUpdate();
  sprintf(buffer," gX:%+08.3f gY:%+08.3f gZ:%+08.3f ms:%lu",mpu.gyroX(),mpu.gyroY(),mpu.gyroZ(),millis());
  Serial.println(buffer);
}

void loop() {
  mpuLoop();
  ringLoop();
  delay(100);
}
