# simple code to send position commands via CAN bus (2.0 or FD) to a microcontroller controlling one BLDC motor using a 3-PWM driver.

import can

bus = can.Bus(interface='socketcan', channel='can0')

msg = can.Message(
    arbitration_id=0x201,
    data=(123456).to_bytes(4, 'little', signed=True),
    is_extended_id=False
)

bus.send(msg)