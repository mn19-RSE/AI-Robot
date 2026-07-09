//stm32g431_mcu.h

#pragma once
using Pin = decltype(PA4);

// Motor driver
constexpr Pin MOTOR_INA = PA14;
constexpr Pin MOTOR_INB = PA13;
constexpr Pin MOTOR_INC = PA12;
constexpr Pin MOTOR_EN = PB11;

// Encoder
constexpr Pin ENC_CS = PA4;
constexpr Pin ENC_MOSI = PB5;
constexpr Pin ENC_MISO = PB4;
constexpr Pin ENC_SCK = PB3;

// CAN bus
constexpr Pin CANRX = PB8;
constexpr Pin CANTX = PB9;
