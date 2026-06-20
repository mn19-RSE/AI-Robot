/*
Created by Mason Newman 5/24/2026
Stripped down SimpleFOC code to test new hardware
Intended for: 
- AS5048A magnetic encoder using I2C
- Driver with EN, A, B, C inputs
*/

#include <SimpleFOC.h>
MagneticSensorI2C sensor = MagneticSensorI2C(AS5600_I2C);
BLDCMotor motor = BLDCMotor(7);                          // configure motor pole pairs
BLDCDriver3PWM driver = BLDCDriver3PWM(D3, D2, D1, D0);  // configure motor A, B, C, EN pins
Commander command = Commander(Serial);                   // instatiate serial terminal commander

float target_angle = 0;

void doTarget(char* cmd) {
  command.scalar(&target_angle, cmd);
}

void setup() {
  Serial.begin(115200);
  SimpleFOCDebug::enable(&Serial);  // enable verbose debugging output
  Wire.setClock(400000);            // configure I2C speed
  sensor.init();                    // initialize magnetic sensor
  Serial.println("sensor ready");
  delay(250);

  motor.linkSensor(&sensor);
  driver.voltage_power_supply = 12;  // set power supply output
  driver.init();                     // initialize driver
  Serial.println("driver ready");
  delay(250);

  motor.linkDriver(&driver);
  motor.foc_modulation = FOCModulationType::SinePWM;  // choose FOC modulation (optional)
  motor.controller = MotionControlType::angle;               // set motion control loop to be used
  //motor.controller = MotionControlType::velocity_openloop;
  //motor.controller = MotionControlType::velocity;


  // PID parameters
  motor.PID_velocity.P = 0.5;
  motor.PID_velocity.I = 20.0;
  motor.PID_velocity.D = 0.0;
  // motor.PID_velocity.output_ramp = 1000;
  motor.voltage_limit = 6;       // max motor voltage before init
  motor.LPF_velocity.Tf = 0.8;  // velocity low pass filtering time constant, lower = less filtered
  motor.P_angle.P = 10.0;         
  motor.velocity_limit = 5;      // max velocity of position control


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
  // motor.move(1);  // use for velocity mode test
  motor.monitor();  // serial plotter to monitor motor variables
  command.run();
}
