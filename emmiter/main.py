# Untitled - By: mtala - Tue Aug 5 2025

from pyb import UART
import sensor
import pyb
import time

sensor.reset()
sensor.set_pixformat(sensor.RGB565)
sensor.set_framesize(sensor.QVGA)
sensor.skip_frames(time=2000)

clock = time.clock()

uart = UART(1, 115200)

led = pyb.LED(1)
ball_led = pyb.LED(2)

BALL_THRESH = [(8, 100, 15, 127, 14, 127)] # [(12, 81, 9, 71, 3, 125)]
COURT_THRESH = [(1, 100, -87, 127, -45, 31)]
IMG_W, IMG_H = sensor.width(), sensor.height()
LEFT_THRESH = IMG_W/2 - IMG_W * 0.05
RIGHT_THRESH = IMG_W/2 + IMG_W * 0.05

def get_ball_blob(img, threshold, court_blob):
    blobs = img.find_blobs(threshold, area_threshold = 200, pixels_threshold = 200, merge = False)
    if blobs:
        for blob in blobs:
            ball = blob
            if ball.roundness() < 0.6 or ball.pixels() < 100: continue #REVISE
            if not is_blob_inside_blob(court_blob, ball): continue
            # print("Found blob with roundness: ", ball.roundness(), "pixels: ", ball.pixels())
            # print("------------------")
            return ball
    return None

def get_court_blob(img, threshold):
    blobs = img.find_blobs(threshold, area_threshold = 700, pixels_threshold = 700, merge = True)
    if blobs:
        last_biggest_blob = 0
        blob_idx = 0
        for blob in blobs:
            if int(blob.pixels()) > last_biggest_blob:
                last_biggest_blob = int(blob.pixels())
                # last_biggest_blob = blob
            blob_idx += 1
            continue
        return blobs[blob_idx - 1]
    return None

def is_blob_inside_blob(parent_blob, son_blob):
    if son_blob == None or parent_blob == None: return False
    son_centre = (son_blob.cx(), son_blob.cy())
    parent_centre = (parent_blob.cx(), parent_blob.cy())
    parent_w, parent_h = parent_blob.w(), parent_blob.h()
    if son_centre[0] < (parent_centre[0] - parent_w / 2): return False
    if son_centre[1] < (parent_centre[1] - parent_h / 2): return False
    if son_centre[0] > (parent_centre[0] + parent_w / 2): return False
    if son_centre[1] > (parent_centre[1] + parent_h / 2): return False
    return True

def get_blob_centre(img, blob):
    if blob == None: return
    # blob = blob[0]
    centre = (blob.cx(), blob.cy())
    return centre

def get_blob_offset(centre, left_offset, right_offset):
    if centre < left_offset:
        offset = centre - left_offset
    elif centre > right_offset:
        offset = centre - right_offset
    else:
        offset = 0
    return offset

def send_data(data):
    data_str = str(data) + "\n"
    uart.write(data_str)

def find_court(img, thresh):
    court_blob = get_court_blob(img, thresh)
    court_centre = get_blob_centre(img, court_blob)
    if court_centre != None:
        return court_blob
    return -1

def find_ball(img, thresh, court_blob):
    ball_blob = get_ball_blob(img, thresh, court_blob)
    ball_centre = get_blob_centre(img, ball_blob)
    if ball_centre != None:
        return ball_centre, ball_blob.area()
    return -1, -1

led.toggle()
time.sleep(1)
led.toggle()
time.sleep(1)
while True:
    img = sensor.snapshot()
    court_blob = find_court(img, COURT_THRESH)
    if court_blob != -1:
        ball_centre, ball_area = find_ball(img, BALL_THRESH, court_blob)
        if ball_centre != -1 and ball_area != -1:
            offset = get_blob_offset(ball_centre[0], LEFT_THRESH, RIGHT_THRESH)
            # print("Image centre: ", IMG_W/2, "Ball blob X centre: ", ball_centre[0], "Ball centre offset: ", offset)
            data = str(offset * -1) + "," + str(img.width()) + "," + str(ball_area)
            send_data(data)
            ball_led.toggle()
            # print("----------------------------------")
        else:
            data = str(-1000) + "," + str(img.width()) + "," + str(0)
            send_data(data) # Sends a value that means no ball detected
