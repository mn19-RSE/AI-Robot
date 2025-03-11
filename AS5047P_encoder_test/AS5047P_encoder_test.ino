#include <SPI.h>
#include <AS5047P.h>

AS5047P as5047p(14); // Chip select pin #

void setup() {
  Serial.begin(115200);
  SPI.begin();
  as5047p.initSPI();
}

void loop() {
  uint16_t angle = as5047p.readAngleRaw();
  Serial.print("Angle: ");
  Serial.println(angle);
  delay(100);
}