# Untitled - By: mtala - Fri Aug 29 2025

# from machine import UART
# import ustruct
import sensor
import time
import pyb

# uart = UART(1, 9600)
# uart.init(9600) # Baudios

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time=2000)

clock = time.clock()
led = pyb.LED(2)
uart = pyb.UART(1, 9600)

while True:
    # clock.tick()
    led.toggle()

    img = sensor.snapshot()
    # # print(clock.fps())
    # data = ustruct.pack('i', -2)
    # data = bytes('-2\n')
    offset = -1.7698
    data = str(offset) + '\n'
    # print(data)
    uart.write(data)
    time.sleep(1)
    # print(data)
