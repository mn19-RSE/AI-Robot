#include <ACAN_T4.h>

String receivedText = ""; // Buffer to store incoming characters

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

  Serial.println("Waiting for messages...");
}

void loop() {
  CANMessage msg;
  
  if (ACAN_T4::can1.receive(msg)) {
    if (msg.id == 0x200) { // Check if it's a string message
      for (int i = 0; i < msg.len; i++) {
        receivedText += (char)msg.data[i]; // Append character to string
      }
      
      // Print when the last packet is smaller than 8 bytes (indicating end of message)
      if (msg.len < 8) {
        Serial.print("Received Message: ");
        Serial.println(receivedText);
        receivedText = ""; // Clear buffer after printing
      }
    }
  }
}
