import png
from adbutils import adb
import os
import numpy
import itertools
import matplotlib.pyplot as plt
from playgame import * 


def main():
    d = adb.device()
    d.shell("screencap -p /sdcard/block.png")
    d.sync.pull("/sdcard/block.png", "block.png")
    char_grid = get_grid_from_file("block.png")
    print_grid(char_grid)
    save_grid(char_grid, "block.txt")
    os.system("./unblock block.txt commands.txt")

    
main()
