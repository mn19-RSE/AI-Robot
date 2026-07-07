
#include <SimpleFOC.h>
#include <Arduino.h>
#include <driver/twai.h>

#define CAN_TX GPIO_NUM_43   // XIAO D6
#define CAN_RX GPIO_NUM_44   // XIAO D7

MagneticSensorSPI sensor = MagneticSensorSPI(D6, 14, 0x3FFF); // For AS5048A SPI board!!
BLDCMotor motor = BLDCMotor(7);                          // configure motor pole pairs
BLDCDriver3PWM driver = BLDCDriver3PWM(D3, D2, D1, D0);  // configure motor A, B, C, EN pins

float target_angle = 0;


void setup() {
  // put your setup code here, to run once:

}

void loop() {
  // put your main code here, to run repeatedly:

}
