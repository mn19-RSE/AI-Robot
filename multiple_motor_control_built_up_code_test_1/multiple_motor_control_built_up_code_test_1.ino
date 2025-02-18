#include <SimpleFOC.h>

#define V_SUPPLY 12
#define motor1_target 4
#define motor2_target 4

BLDCMotor motor1 = BLDCMotor(17);                     //motor phase resistance
BLDCDriver3PWM driver1 = BLDCDriver3PWM(0, 1, 2, 3);  //driver IN1, IN2, IN3, EN pin connections to MCU
MagneticSensorSPI sensor1 = MagneticSensorSPI(10, 14, 0x3FFF);


BLDCMotor motor2 = BLDCMotor(7);                      //motor phase resistance
BLDCDriver3PWM driver2 = BLDCDriver3PWM(4, 5, 6, 7);  //driver IN1, IN2, IN3, EN pin connections to MCU
MagneticSensorSPI sensor2 = MagneticSensorSPI(14, 14, 0x3FFF);


int lastPrintTime = 0;


void setup() {
  Serial.begin(115200);             // use monitoring with serial
  SimpleFOCDebug::enable(&Serial);  // enable more verbose output for debugging
  motor1.useMonitoring(Serial);
  motor2.useMonitoring(Serial);



  sensor1.init();
  motor1.linkSensor(&sensor1);
  driver1.voltage_power_supply = V_SUPPLY;
  driver1.init();

  motor1.linkDriver(&driver1);
  motor1.controller = MotionControlType::angle;
  motor1.foc_modulation = FOCModulationType::SpaceVectorPWM;
  motor1.PID_velocity.P = 0.2;  // controller configuration based on the control type
  motor1.PID_velocity.I = 20;
  motor1.PID_velocity.D = 0.5;
  motor1.LPF_velocity.Tf = 0.01;  // velocity low pass filtering time constant
  motor1.P_angle.P = 20;          // angle loop controller //I am not sure what this is or does
  motor1.P_angle.I = 1;
  motor1.P_angle.D = 1;

  motor1.velocity_limit = 10;  // angle loop velocity limit
  motor1.voltage_limit = 6;   // default voltage_power_supply

  motor1.init();
  motor1.initFOC();

  motor1.target = motor1_target;  //initial motor position


  //Serial.println("Motor 1 ready");
  _delay(1000);


  sensor2.init();
  motor2.linkSensor(&sensor2);
  driver2.voltage_power_supply = V_SUPPLY;
  driver2.init();

  motor2.linkDriver(&driver2);
  motor2.controller = MotionControlType::angle;
  motor2.foc_modulation = FOCModulationType::SpaceVectorPWM;
  motor2.PID_velocity.P = 0.2;  // controller configuration based on the control type
  motor2.PID_velocity.I = 20;
  motor2.PID_velocity.D = 0.5;
  motor2.LPF_velocity.Tf = 0.01;  // velocity low pass filtering time constant
  motor2.P_angle.P = 20;          // angle loop controller //I am not sure what this is or does
  motor1.P_angle.I = 1;
  motor1.P_angle.D = 1;

  motor2.velocity_limit = 10;  // angle loop velocity limit
  motor2.voltage_limit = 6;   // default voltage_power_supply

  motor2.init();
  motor2.initFOC();

  motor2.target = motor2_target;  //initial motor position


  //Serial.println("Motor 2 ready");
  _delay(1000);
}

void loop() {
  motor1.loopFOC();
  motor2.loopFOC();
  int sinpos1 = 4 * sin(.001 * millis()) + 4;
  int sinpos2 = 4 * sin(.001 * millis()) + 4;
  if ((millis() % 500) == 0) {
    motor1.move(sinpos1);
    motor2.move(sinpos2);
  }

  if (millis() - lastPrintTime > 2000) {  // Print every 2000ms
    Serial.print("Angle: ");
    Serial.println(sensor1.getAngle());
    Serial.print("Angle: ");
    Serial.println(sensor2.getAngle());
    lastPrintTime = millis();
  }
}
