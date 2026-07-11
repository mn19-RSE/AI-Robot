#include "Arduino.h"
#include <Wire.h>
#include <SimpleFOC.h>
#include <SimpleFOCDrivers.h>
#include "drivers/drv8316/drv8316.h"

SPIClass SPI_1(SPI_MOSI, SPI_MISO, SPI_SCK);
BLDCMotor motor = BLDCMotor(11);

DRV8316Driver6PWM driver = DRV8316Driver6PWM(PHA_H, PHA_L, PHB_H, PHB_L, PHC_H, PHC_L, DRV_CS, true);

// velocity set point variable
float target_velocity = 20.0;

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, HIGH);
  delay(100);
  Serial.begin(250000);
  Serial.println("Initializing...");

  driver.voltage_power_supply = 12.0;
  driver.voltage_limit = 12.0;
  driver.init(&SPI_1);
  driver.setSlew(Slew_25Vus);
  driver.setPWM100Frequency(FREQ_40KHz);
  driver.setBuckVoltage(VB_5V);
  driver.setOCPRetryTime(Retry5ms);
  //driver.enable();
  Serial.println("Init complete...");

  delay(100);
  printDRV8316Status();

  digitalWrite(LED_BUILTIN, LOW);
  Serial.println("Done");
}

void loop() {

  for (int i = 0; i < 6; i++) {
    int pins[3] = { PHA_H, PHB_H, PHC_H };
    for (int j = 0; j < 3; j++) {
      if (i == j) {
        for (int k = 0; k <= 40; k++) {
          analogWrite(pins[j], k);
          delay(10);
        }
      } else {
        analogWrite(pins[j], 0);
      }
    }
  }
}