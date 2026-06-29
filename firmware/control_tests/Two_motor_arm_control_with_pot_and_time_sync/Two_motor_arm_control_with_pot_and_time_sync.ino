#include <SimpleFOC.h>

// Magnetic sensors (SPI)
MagneticSensorSPI sensor1 = MagneticSensorSPI(10, 14, 0x3FFF);
MagneticSensorSPI sensor2 = MagneticSensorSPI(37, 14, 0x3FFF);

// BLDC motors & drivers
BLDCMotor motor1 = BLDCMotor(7);
BLDCDriver3PWM driver1 = BLDCDriver3PWM(5, 4, 3, 2);

BLDCMotor motor2 = BLDCMotor(7);
BLDCDriver3PWM driver2 = BLDCDriver3PWM(9, 8, 7, 6);

void setup() {
    Serial.begin(115200);
    delay(1000);  // Allow time for serial monitor to connect

    Serial.println("Starting...");

    // Initialize sensors
    sensor1.init();
    sensor2.init();
    _delay(500);

    // Check if sensors are working
    sensor1.update();
    sensor2.update();
    float angle1 = sensor1.getAngle();
    float angle2 = sensor2.getAngle();

    Serial.print("Sensor1 Angle: ");
    Serial.println(angle1);
    Serial.print("Sensor2 Angle: ");
    Serial.println(angle2);

    if (isnan(angle1) || isnan(angle2)) {
        Serial.println("Error: Sensors not reading values. Check connections!");
        while (1);
    }

    // Manually set zero electric angle to avoid twitching
    motor1.zero_electric_angle = angle1;
    motor2.zero_electric_angle = angle2;

    // Link sensors to motors
    motor1.linkSensor(&sensor1);
    motor2.linkSensor(&sensor2);

    // Driver setup
    driver1.voltage_power_supply = 10;
    driver1.init();
    motor1.linkDriver(&driver1);

    driver2.voltage_power_supply = 10;
    driver2.init();
    motor2.linkDriver(&driver2);

    // Set motion control type
    motor1.controller = MotionControlType::angle;
    motor2.controller = MotionControlType::angle;

    // PID tuning
    motor1.PID_velocity.P = 0.5f;
    motor1.PID_velocity.I = 1;
    motor1.PID_velocity.D = 0.05;
    motor1.voltage_limit = 6;
    motor1.LPF_velocity.Tf = 0.05;
    motor1.P_angle.P = 50;
    motor1.velocity_limit = 100;

    motor2.PID_velocity.P = 0.5f;
    motor2.PID_velocity.I = 1;
    motor2.PID_velocity.D = 0.05;
    motor2.voltage_limit = 6;
    motor2.LPF_velocity.Tf = 0.05;
    motor2.P_angle.P = 50;
    motor2.velocity_limit = 100;

    // Initialize motors WITHOUT automatic FOC calibration
    motor1.init();
    motor2.init();
    
    // Skip automatic calibration (prevents twitching)
    motor1.initFOC();
    motor2.initFOC();

    Serial.println("Motors ready.");
}

void loop() {
    // Generate smooth oscillation (-90° to 90° in ~3s)
    float target_angle = 90.0 * sin(millis() * 2 * PI / 3000) * _PI / 180.0;

    // Move motors
    motor1.loopFOC();
    motor2.loopFOC();
    motor1.move(target_angle);
    motor2.move(target_angle);

    // Debug output
    //Serial.print("Target: ");
    //Serial.println(target_angle);
}
