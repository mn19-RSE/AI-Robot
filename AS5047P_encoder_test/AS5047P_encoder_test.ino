#include <SPI.h>
#include <AS5047P.h>

AS5047P as5047p(10); // Chip select pin 10

void setup() {
  Serial.begin(9600);
  SPI.begin();
  as5047p.initSPI();
}

void loop() {
  uint16_t angle = as5047p.readAngleRaw();
  Serial.print("Angle: ");
  Serial.println(angle);
  delay(10);
}