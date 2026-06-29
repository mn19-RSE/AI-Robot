#include <ACAN_T4.h>

void setup() {
  Serial.begin(115200);
  while (!Serial) delay(10);

  ACAN_T4_Settings settings(500 * 1000);
  const uint32_t errorCode = ACAN_T4::can1.begin(settings);

  if (errorCode == 0) {
    Serial.println("CAN1 initialized successfully!");
  } else {
    Serial.print("CAN1 Error: 0x");
    Serial.println(errorCode, HEX);
  }
}

void loop() {
  CANMessage msg;

  if (ACAN_T4::can1.receive(msg)) {
    Serial.print("Received Message ID: 0x");
    Serial.println(msg.id, HEX);
    Serial.print("Data: Count = ");
    Serial.print(msg.data[0]);
    Serial.print(", Random Value = ");
    Serial.println(msg.data[1]);

    // Send acknowledgment including received data
    CANMessage ack;
    ack.id = 0x101; // Acknowledgment ID
    ack.len = 2;
    ack.data[0] = msg.data[0]; // Echo message counter
    ack.data[1] = msg.data[1]; // Echo random number

    ACAN_T4::can1.tryToSend(ack);
    Serial.println("Acknowledgment sent!");
  }
}
