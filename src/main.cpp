#include <MPU9250_asukiaaa.h>

#ifdef _ESP32_HAL_I2C_H_
#define SDA_PIN 19
#define SCL_PIN 18
#endif

MPU9250 mpu;

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
    // you can set your own offset for mag values
    // mpu.magXOffset = -50;
    // mpu.magYOffset = -55;
    // mpu.magZOffset = -10;
}

void loop() {
    mpu.accelUpdate();
    char buffer [40];
    sprintf(buffer,"aX:%+06.3f aY:%+06.3f aZ:%+06.3f",mpu.accelX(),mpu.accelY(),mpu.accelX());
    Serial.print(buffer);
    mpu.magUpdate();
    sprintf(buffer," mX:%+08.3f mY:%+08.3f mZ:%+08.3f",mpu.magX(),mpu.magY(),mpu.magZ());
    Serial.println(buffer);
    // Serial.println("accelSqrt: " + String(mpu.accelSqrt()));
    // Serial.println("horizontal direction: " + String(mpu.magHorizDirection()));
    // Serial.println("at " + String(millis()) + "ms");
    delay(100);
}
