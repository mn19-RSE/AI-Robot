#include <ACAN_T4.h>

uint32_t messageCounter = 0; // Keeps track of sent messages

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

  randomSeed(analogRead(A0)); // Initialize random number generator
}

void loop() {
  static uint32_t lastSendTime = 0;
  if (millis() - lastSendTime >= 5000) { // Send every 5 seconds
    lastSendTime = millis();
    messageCounter++;

    CANMessage msg;
    msg.id = 0x100; // Message ID
    msg.len = 2; // Two bytes of data
    msg.data[0] = messageCounter;  // First byte: message count
    msg.data[1] = random(1, 255); // Second byte: random number

    if (ACAN_T4::can1.tryToSend(msg)) {
      Serial.print("Sent message #");
      Serial.print(messageCounter);
      Serial.print(" with random value: ");
      Serial.println(msg.data[1]);
    }
  }

  // Check for acknowledgment
  CANMessage msg;
  if (ACAN_T4::can1.receive(msg) && msg.id == 0x101) {
    Serial.println("Acknowledgment received!");
  }
}
