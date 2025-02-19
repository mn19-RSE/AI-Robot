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

  Serial.println("Type a message and press Enter to send over CAN:");
}

void loop() {
  if (Serial.available()) {
    String input = Serial.readStringUntil('\n'); // Read full input until newline
    input.trim(); // Remove unwanted spaces/newline
    
    if (input.length() > 0) {
      Serial.print("Sending: ");
      Serial.println(input);
      
      sendStringOverCAN(input);
    }
  }
}

// Function to send a string in CAN frames (splitting if longer than 8 bytes)
void sendStringOverCAN(String text) {
  int textLength = text.length();
  int bytesSent = 0;

  while (bytesSent < textLength) {
    CANMessage msg;
    msg.id = 0x200; // Unique ID for text messages
    msg.len = min(8, textLength - bytesSent); // Max 8 bytes per frame

    for (int i = 0; i < msg.len; i++) {
      msg.data[i] = text[bytesSent + i]; // Copy part of string into CAN data
    }

    ACAN_T4::can1.tryToSend(msg);
    bytesSent += msg.len;

    delay(10); // Small delay to prevent CAN overload
  }
}
