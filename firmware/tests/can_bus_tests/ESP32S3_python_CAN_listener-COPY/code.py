import time
import board
import canio

# Create CAN interface
can = canio.CAN(tx=board.D6, rx=board.D7, baudrate=500000)

# Listen to ALL CAN IDs (no filter)
listener = can.listen(timeout=1.0)

print("CAN listener started...")

while True:
    message = listener.receive()
    if message is None:
        continue

    # Print raw CAN frame
    print("ID:", hex(message.id), "LEN:", len(message.data), "DATA:", message.data)

    time.sleep(0.001)