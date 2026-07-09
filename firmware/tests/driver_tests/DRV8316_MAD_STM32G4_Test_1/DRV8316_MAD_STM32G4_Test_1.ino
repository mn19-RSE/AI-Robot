//#include "stm32g431_mcu.h"
#include <SimpleFOC.h>
MagneticSensorSPI sensor = MagneticSensorSPI(D7, 14, 0x3FFF);  //test
// MagneticSensorSPI sensor = MagneticSensorSPI(ENC_CS, 14, 0x3FFF);
BLDCMotor motor = BLDCMotor(11);                          // configure motor pole pairs
BLDCDriver3PWM driver = BLDCDriver3PWM(D2, D1, D0, D3);  //test
// BLDCDriver3PWM driver = BLDCDriver3PWM(MOTOR_INA, MOTOR_INB, MOTOR_INC, MOTOR_EN);  // configure motor A, B, C, EN pins
Commander command = Commander(Serial);  // instatiate serial terminal commander
float target_angle = 0;


void doTarget(char* cmd) {
  command.scalar(&target_angle, cmd);
}

void setup() {
  Serial.begin(115200);
  // SPI.setSCLK(ENC_SCK);
  // SPI.setMISO(ENC_MISO);
  // SPI.setMOSI(ENC_MOSI);
  sensor.init();
  Serial.println("sensor ready");
  delay(250);

  motor.linkSensor(&sensor);
  driver.voltage_power_supply = 12;  // set power supply output
  driver.pwm_frequency = 25000;
  driver.init();  // initialize driver
  SimpleFOCDebug::enable(&Serial);
  Serial.println("driver ready");
  delay(250);

  motor.linkDriver(&driver);
  motor.foc_modulation = FOCModulationType::SpaceVectorPWM;  // choose FOC modulation (optional)
  motor.controller = MotionControlType::angle;               // set motion control loop to be used

  // PID parameters
  motor.PID_velocity.P = 0.2;  // 0.5
  motor.PID_velocity.I = 0.2;  // 25
  motor.PID_velocity.D = 0.0;
  // motor.PID_velocity.output_ramp = 1000;
  motor.voltage_limit = 4;      // max motor voltage before? init
  motor.LPF_velocity.Tf = .01;  // velocity low pass filtering time constant, lower = less filtered
  // motor.P_angle.P = 10.0;
  motor.velocity_limit = 20;  // 20   // max velocity of position control

  motor.useMonitoring(Serial);  // (optional)
  motor.init();                 // initailize motor
  Serial.println("motor ready");
  delay(1250);

  motor.initFOC();                             // align sensor and start FOC
  command.add('T', doTarget, "target angle");  // add target command T
  Serial.println("FOC ready, Set target angle in terminal prefaced by a T");
  delay(250);
}

void loop() {
  motor.loopFOC();
  motor.move(target_angle);
  command.run();
}
