/*
Test for SimpleFOC control of multiple motors using a Teensy 4.1 
*/

#include <SimpleFOC.h>
#define V_SUPPLY 24
#define V_MOTOR 2
#define motor1_target 2
#define motor2_target 2


const int Sensor1_pin = 6;
const int Sensor2_pin = 10;
// const int Sensor3_pin = 999;  //not connected
// const int Sensor4_pin = 30;

// const int OC_ADJ = 36;  //analog driver current limit connected to all drivers

/*
MagneticSensorPWM sensor4 = MagneticSensorPWM(Sensor4_pin, 2, 937);
void doPWM() {
  sensor.handlePWM();
}
*/

MagneticSensorSPI sensor1 = MagneticSensorSPI(Sensor1_pin, 14, 0x3FFF);  //Encoder type (CS, resolution, angle register)
MagneticSensorSPI sensor2 = MagneticSensorSPI(Sensor2_pin, 14, 0x3FFF);

BLDCMotor motor1 = BLDCMotor(7);  // Motor type and coil resistance
BLDCMotor motor2 = BLDCMotor(7);

BLDCDriver3PWM driver1 = BLDCDriver3PWM(2, 3, 4, 5);  //driver IN1, IN2, IN3, EN pin connections to MCU
BLDCDriver3PWM driver2 = BLDCDriver3PWM(19, 22, 23, 18);


float target_angle = 0;
Commander command = Commander(Serial);  // instantiate the commander
void doTarget(char* cmd) {
  command.scalar(&target_angle, cmd);
}



void setup() {
  Serial.begin(115200);

  // pinMode(OC_ADJ, OUTPUT);
  //analogWrite(OC_ADJ, 200); //Teensy4.x has PWM output 1 to 255
  // digitalWrite(OC_ADJ, LOW);
  SimpleFOCDebug::enable(&Serial);  // enable more verbose output for debugging
  motor1.useMonitoring(Serial);
  motor2.useMonitoring(Serial);

  sensor1.init();
  sensor2.init();

  driver1.voltage_power_supply = V_SUPPLY;
  driver2.voltage_power_supply = V_SUPPLY;

  driver1.init();
  driver2.init();

  motor1.linkSensor(&sensor1);
  motor2.linkSensor(&sensor2);

  motor1.linkDriver(&driver1);
  motor2.linkDriver(&driver2);

  motor1.linkDriver(&driver1);
  motor2.linkDriver(&driver2);

  motor1.foc_modulation = FOCModulationType::SpaceVectorPWM;
  motor2.foc_modulation = FOCModulationType::SpaceVectorPWM;

  motor1.controller = MotionControlType::angle;
  motor2.controller = MotionControlType::angle;

  motor1.PID_velocity.P = 0.1;
  motor2.PID_velocity.P = 0.1;

  motor1.voltage_limit = V_MOTOR;
  motor2.voltage_limit = V_MOTOR;

  motor1.velocity_limit = 50;
  motor2.velocity_limit = 100;

  motor1.init();
  motor2.init();

  motor1.initFOC();
  motor2.initFOC();

  motor1.target = motor1_target;  //initial motor position
  motor2.target = motor2_target;

  command.add('T', doTarget, "target angle");  // add target command T
  _delay(1000);
}

void loop() {
  //motor1.loopFOC();
  //motor1.move(target_angle);

  motor2.loopFOC();
  motor2.move(target_angle);

  command.run();
}
