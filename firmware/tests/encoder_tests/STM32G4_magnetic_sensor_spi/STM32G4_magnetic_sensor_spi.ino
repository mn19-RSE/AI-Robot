#include "stm32g431_mcu.h"
#include <SimpleFOC.h>
MagneticSensorSPI sensor = MagneticSensorSPI(ENC_CS, 14, 0x3FFF);  //PA4 or PA15

void setup() {
  // monitoring port
  Serial.begin(115200);
  SPI.setSCLK(ENC_SCK);
  SPI.setMISO(ENC_MISO);
  SPI.setMOSI(ENC_MOSI);
  // initialise magnetic sensor hardware
  sensor.init();

  Serial.println("Sensor ready");
  _delay(1000);
}

void loop() {
  sensor.update();
  Serial.print(sensor.getAngle());
  Serial.print("\t");
  Serial.println(sensor.getVelocity());
}
