//stm32g431_mcu.h

#pragma once

// Motor driver
constexpr uint8_t MOTOR_INA = PA14;
constexpr uint8_t MOTOR_INB = PA13;
constexpr uint8_t MOTOR_INC = PA12;
constexpr uint8_t MOTOR_EN = PB11;

// Encoder
constexpr uint8_t ENC_CS = PA4;
constexpr uint8_t ENC_MOSI = PB5;
constexpr uint8_t ENC_MISO = PB4;
constexpr uint8_t ENC_SCK = PB3;

// CAN bus
constexpr uint8_t CANRX = PB8;
constexpr uint8_t CANTX = PB9;
