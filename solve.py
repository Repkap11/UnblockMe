import png
from adbutils import adb
import os
import numpy
import itertools
import matplotlib.pyplot as plt
from playgame import *
import csv
import time

d = adb.device()


def main():
    while True:
        d.shell("screencap -p /sdcard/block.png")
        d.sync.pull("/sdcard/block.png", "block.png")
        char_grid, left, top, size = get_grid_from_file("block.png")
        left += size/2
        top += size/2
        print(left, top, size)
        print_grid(char_grid)
        save_grid(char_grid, "block.txt")
        os.system("./unblock block.txt commands.txt")

        with open("commands.txt") as csv_file:
            csv_reader = csv.reader(csv_file, delimiter=',')
            line_count = 0
            for row in csv_reader:
                block = row[0]
                x = float(row[1])
                y = float(row[2])
                dir_x = float(row[3])
                dir_y = float(row[4])
                length = float(row[5])
                swipe_command(
                    left+size*x, top+size*y,
                    left+size*(x+dir_x*length), top+size*(y+dir_y*length), length)
        time.sleep(0.5)
        d.shell("input tap 440 1340") # Tap the next puzzle button
        time.sleep(1)

def swipe_command(from_x, from_y, to_x, to_y, length):
    # print(from_x, from_y, to_x, to_y)
    s = "input touchscreen swipe {} {} {} {} {}".format(
        int(from_x), int(from_y), int(to_x), int(to_y), int(80 * length))
    print(s)
    d.shell(s)


main()
