#include <Arduino.h>
#include "driver/twai.h"

#define CAN_TX GPIO_NUM_43   // XIAO D6
#define CAN_RX GPIO_NUM_44   // XIAO D7

void setup() {
    Serial.begin(115200);
    delay(1000);
    twai_general_config_t g_config =
        TWAI_GENERAL_CONFIG_DEFAULT(CAN_TX, CAN_RX, TWAI_MODE_LISTEN_ONLY);
    twai_timing_config_t t_config =
        TWAI_TIMING_CONFIG_500KBITS();   // baud rate
    twai_filter_config_t f_config =
        TWAI_FILTER_CONFIG_ACCEPT_ALL();

    ESP_ERROR_CHECK(twai_driver_install(&g_config, &t_config, &f_config));
    ESP_ERROR_CHECK(twai_start());
    Serial.println("CAN Listener Started");
}

void loop() {
    twai_message_t msg;
    if (twai_receive(&msg, pdMS_TO_TICKS(1000)) == ESP_OK) {
        Serial.printf("%08lX [%d] ",
                      msg.identifier,
                      msg.data_length_code);
        for (int i = 0; i < msg.data_length_code; i++) {
            Serial.printf("%02X ", msg.data[i]);
        }
        Serial.println();
    }
}