# simple code to send position commands via CAN bus (2.0 or FD) to a microcontroller controlling one BLDC motor using a 3-PWM driver.

import can

bus = can.interface.Bus(
    channel='can0',
    interface='socketcan'
)

msg = can.Message(
    arbitration_id=0x123,
    data=[0xAB,0xCD,0xAB,0xCD],
    is_extended_id=False
)

bus.send(msg)