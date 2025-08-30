# Untitled - By: mtala - Fri Aug 29 2025

from machine import UART
import sensor
import time

uart = UART(1, 9600)
# uart.init(9600) # Baudios

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time=2000)

clock = time.clock()

while True:
    clock.tick()
    img = sensor.snapshot()
    # print(clock.fps())
    data = bytes("Hola\n", 'utf-8')
    uart.write(data)
    # print(data)
