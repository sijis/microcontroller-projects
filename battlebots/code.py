import random
import time

import adafruit_dotstar
import board
import neopixel
import touchio

RED = (255, 0, 0)
YELLOW = (255, 150, 0)
GREEN = (0, 255, 0)
CYAN = (0, 255, 255)
BLUE = (0, 0, 255)
PURPLE = (180, 0, 255)
BLACK = (0, 0, 0)

onboard_led = adafruit_dotstar.DotStar(board.APA102_SCK, board.APA102_MOSI, 1)

touch_pad = board.A0
pixel_pin = board.A1
num_pixels = 100

pixels = neopixel.NeoPixel(
    pixel_pin,
    num_pixels,
    brightness=0.3,
    auto_write=False,
)
touch = touchio.TouchIn(touch_pad)


def random_color():
    red = random.choice(range(255))
    green = random.choice(range(255))
    blue = random.choice(range(255))
    return (red, green, blue)


def confetti():
    print("Start confetti.")
    for i in range(200):
        pos = random.choice(range(num_pixels))
        color = random_color()
        pixels[pos] = color
        pixels.show()
        onboard_led.fill(color)
        time.sleep(0.05)

    light_up(BLACK)
    time.sleep(3)


def light_up(color):
    onboard_led.fill(color)
    pixels.fill(color)
    pixels.show()


def start_battle_sequence():
    print("Start battle sequence.")
    for i in range(3):
        print("Beep.")
        light_up(YELLOW)
        time.sleep(1.5)
        light_up(BLACK)

    time.sleep(random.choice([2, 3, 4]))
    print("Beep!!!")
    light_up(GREEN)
    time.sleep(2)


def end_sequence(start_time):
    interval = 180
    current = time.monotonic()
    time_diff = current - start_time
    if time_diff >= interval:
        return True
    return False


light_up(BLACK)
started = False
start_time = time.monotonic()
while True:
    if (touch.value and started) or end_sequence(start_time):
        light_up(BLACK)
        started = not started

    if touch.value and not started:
        started = not started
        confetti()
        start_battle_sequence()
        start_time = time.monotonic()
