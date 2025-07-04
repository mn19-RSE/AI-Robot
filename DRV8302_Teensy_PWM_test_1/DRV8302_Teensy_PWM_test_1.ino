#include <SimpleFOC.h>

#define V_SUPPLY 12
#define motor1_target 2


#define motor1_vel_limit 5
#define motor1_V_limit 12


BLDCMotor motor1 = BLDCMotor(7);                      //motor phase resistance
BLDCDriver3PWM driver1 = BLDCDriver3PWM(0, 1, 2, 3);  //driver IN1, IN2, IN3, EN pin connections to MCU


const int PWM_PIN = 23;
MagneticSensorPWM sensor1 = MagneticSensorSPI(23, 4, 904);  //PWM pin, min pulse, max pulse
void doPWM() {
  sensor.handlePWM();
}

int lastPrintTime = 0;
int i = 0;


void setup() {
  pinMode(PWM_PIN, INPUT);          //using pin 23 as another 3.3V source for the motor driver
  Serial.begin(115200);             // use monitoring with serial
  SimpleFOCDebug::enable(&Serial);  // enable more verbose output for debugging
  motor1.useMonitoring(Serial);

  sensor1.init();
  sensor1.enableInterrupt(doPWM);

  motor1.linkSensor(&sensor1);
  driver1.voltage_power_supply = V_SUPPLY;
  driver1.init();

  motor1.linkDriver(&driver1);  // 3-22-25 updating PID for DRV8302 and MAD motor
  motor1.controller = MotionControlType::angle;
  motor1.foc_modulation = FOCModulationType::SinePWM;
  motor1.PID_velocity.P = 0.1;  // controller configuration based on the control type // too high and motor goes wild
  //motor1.PID_velocity.I = 10;
  //motor1.PID_velocity.D = 0.2;
  //motor1.LPF_velocity.Tf = 0.01;  // velocity low pass filtering time constant
  //motor1.P_angle.P = 20;          // angle loop controller //I am not sure what this is or does
  //motor1.P_angle.I = 1;
  //motor1.P_angle.D = 1;

  //motor1.velocity_limit = motor1_vel_limit;  // angle loop velocity limit
  motor1.voltage_limit = motor1_V_limit;  // default voltage_power_supply
  motor1.init();
  motor1.initFOC();
  motor1.target = motor1_target;  //initial motor position

  //Serial.println("Motor 1 ready");
  _delay(500);
}


float pos1 = 20;   // previously: 6.28, 5, 2, -2, 5, 12, -3, -8, -5, 1, 10
float pos2 = -20;  // previously 3.14, 4, 1, -1, 4, 10, -2, -10, -4, 0, -10
int loopTime = 5000;

float motor_slow_speed = 90;
float motor_quick_speed = 100;

void loop() {

  while (millis() < ((1 - (motor_slow_speed / motor_quick_speed)) * loopTime)) {
    motor1.velocity_limit = motor_slow_speed;
    motor1.loopFOC();
    motor1.move(pos1);
  }
  while (millis() >= ((1 - (motor_slow_speed / motor_quick_speed)) * loopTime) && millis() < loopTime) {
    motor1.velocity_limit = motor_quick_speed;
    motor2.velocity_limit = motor_quick_speed;
    motor1.loopFOC();
    motor2.loopFOC();
    motor1.move(pos1);
    motor2.move(pos1);
  }

  while (millis() >= loopTime && millis() < ((1 + (1 - (motor_slow_speed / motor_quick_speed))) * loopTime)) {
    motor1.velocity_limit = motor_slow_speed;
    motor1.loopFOC();
    motor1.move(pos1);
  }
  while (millis() < ((1 + (1 - (motor_slow_speed / motor_quick_speed))) * loopTime) && millis() < (2 * loopTime)) {
    motor1.velocity_limit = motor_quick_speed;
    motor2.velocity_limit = motor_quick_speed;
    motor1.loopFOC();
    motor2.loopFOC();
    motor1.move(pos2);
    motor2.move(pos2);
  }

  while (millis() >= (2 * loopTime) && millis() < ((2 + (1 - (motor_slow_speed / motor_quick_speed))) * loopTime)) {
    motor1.velocity_limit = motor_slow_speed;
    motor1.loopFOC();
    motor1.move(pos1);
  }
  while (millis() >= ((2 + (1 - (motor_slow_speed / motor_quick_speed))) * loopTime) && millis() < (3 * loopTime)) {
    motor1.velocity_limit = motor_quick_speed;
    motor2.velocity_limit = motor_quick_speed;
    motor1.loopFOC();
    motor2.loopFOC();
    motor1.move(pos1);
    motor2.move(pos1);
  }

  while (millis() >= (3 * loopTime) && millis() < ((3 + (1 - (motor_slow_speed / motor_quick_speed))) * loopTime)) {
    motor1.velocity_limit = motor_slow_speed;
    motor1.loopFOC();
    motor1.move(pos1);
  }
  while (millis() >= ((3 + (1 - (motor_slow_speed / motor_quick_speed))) * loopTime) && millis() < (4 * loopTime)) {
    motor1.velocity_limit = motor_quick_speed;
    motor2.velocity_limit = motor_quick_speed;
    motor1.loopFOC();
    motor2.loopFOC();
    motor1.move(pos2);
    motor2.move(pos2);
  }

  while (millis() >= (4 * loopTime) && millis() < ((4 + (1 - (motor_slow_speed / motor_quick_speed))) * loopTime)) {
    motor1.velocity_limit = motor_slow_speed;
    motor1.loopFOC();
    motor1.move(pos1);
  }
  while (millis() >= ((4 + (1 - (motor_slow_speed / motor_quick_speed))) * loopTime) && millis() < (5 * loopTime)) {
    motor1.velocity_limit = motor_quick_speed;
    motor2.velocity_limit = motor_quick_speed;
    motor1.loopFOC();
    motor2.loopFOC();
    motor1.move(pos1);
    motor2.move(pos1);
  }

  while (millis() >= (5 * loopTime) && millis() < ((5 + (1 - (motor_slow_speed / motor_quick_speed))) * loopTime)) {
    motor1.velocity_limit = motor_slow_speed;
    motor1.loopFOC();
    motor1.move(pos1);
  }
  while (millis() >= ((5 + (1 - (motor_slow_speed / motor_quick_speed))) * loopTime) && millis() < (6 * loopTime)) {
    motor1.velocity_limit = motor_quick_speed;
    motor2.velocity_limit = motor_quick_speed;
    motor1.loopFOC();
    motor2.loopFOC();
    motor1.move(pos2);
    motor2.move(pos2);
  }

  while (millis() >= (6 * loopTime) && millis() < ((6 + (1 - (motor_slow_speed / motor_quick_speed))) * loopTime)) {
    motor1.velocity_limit = motor_slow_speed;
    motor1.loopFOC();
    motor1.move(pos1);
  }
  while (millis() >= ((6 + (1 - (motor_slow_speed / motor_quick_speed))) * loopTime) && millis() < (7 * loopTime)) {
    motor1.velocity_limit = motor_quick_speed;
    motor2.velocity_limit = motor_quick_speed;
    motor1.loopFOC();
    motor2.loopFOC();
    motor1.move(pos1);
    motor2.move(pos1);
  }

  while (millis() >= (7 * loopTime) && millis() < ((7 + (1 - (motor_slow_speed / motor_quick_speed))) * loopTime)) {
    motor1.velocity_limit = motor_slow_speed;
    motor1.loopFOC();
    motor1.move(pos1);
  }
  while (millis() >= ((7 + (1 - (motor_slow_speed / motor_quick_speed))) * loopTime) && millis() < (8 * loopTime)) {
    motor1.velocity_limit = motor_quick_speed;
    motor2.velocity_limit = motor_quick_speed;
    motor1.loopFOC();
    motor2.loopFOC();
    motor1.move(pos2);
    motor2.move(pos2);
  }

  while (millis() >= (8 * loopTime) && millis() < ((8 + (1 - (motor_slow_speed / motor_quick_speed))) * loopTime)) {
    motor1.velocity_limit = motor_slow_speed;
    motor1.loopFOC();
    motor1.move(pos1);
  }
  while (millis() >= ((8 + (1 - (motor_slow_speed / motor_quick_speed))) * loopTime) && millis() < (9 * loopTime)) {
    motor1.velocity_limit = motor_quick_speed;
    motor2.velocity_limit = motor_quick_speed;
    motor1.loopFOC();
    motor2.loopFOC();
    motor1.move(pos1);
    motor2.move(pos1);
  }

  while (millis() >= (9 * loopTime) && millis() < ((9 + (1 - (motor_slow_speed / motor_quick_speed))) * loopTime)) {
    motor1.velocity_limit = motor_slow_speed;
    motor1.loopFOC();
    motor1.move(pos1);
  }
  while (millis() >= ((9 + (1 - (motor_slow_speed / motor_quick_speed))) * loopTime) && millis() < (10 * loopTime)) {
    motor1.velocity_limit = motor_quick_speed;
    motor2.velocity_limit = motor_quick_speed;
    motor1.loopFOC();
    motor2.loopFOC();
    motor1.move(pos2);
    motor2.move(pos2);
  }

  while (millis() >= (10 * loopTime) && millis() < ((10 + (1 - (motor_slow_speed / motor_quick_speed))) * loopTime)) {
    motor1.velocity_limit = motor_slow_speed;
    motor1.loopFOC();
    motor1.move(pos1);
  }
  while (millis() >= ((10 + (1 - (motor_slow_speed / motor_quick_speed))) * loopTime) && millis() < (11 * loopTime)) {
    motor1.velocity_limit = motor_quick_speed;
    motor2.velocity_limit = motor_quick_speed;
    motor1.loopFOC();
    motor2.loopFOC();
    motor1.move(pos1);
    motor2.move(pos1);
  }

  while (millis() >= (11 * loopTime) && millis() < ((11 + (1 - (motor_slow_speed / motor_quick_speed))) * loopTime)) {
    motor1.velocity_limit = motor_slow_speed;
    motor1.loopFOC();
    motor1.move(pos1);
  }
  while (millis() >= ((11 + (1 - (motor_slow_speed / motor_quick_speed))) * loopTime) && millis() < (12 * loopTime)) {
    motor1.velocity_limit = motor_quick_speed;
    motor2.velocity_limit = motor_quick_speed;
    motor1.loopFOC();
    motor2.loopFOC();
    motor1.move(pos2);
    motor2.move(pos2);
  }

  while ((millis() >= (12 * loopTime)) && i < 1) {
    Serial.print("Motor movement loop completed!");
    //Serial.println(i);
    i++;
    digitalWrite(3, LOW);  // disables all current to motor!!
  }
}
