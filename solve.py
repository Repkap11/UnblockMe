import png
from adbutils import adb
import os
import numpy
import itertools
import matplotlib.pyplot as plt

d = adb.device()
# d.shell("screencap -p /sdcard/block.png")
# d.sync.pull("/sdcard/block.png", "block.png")
read = png.Reader("block.png")


def main():

    data = read.read()
    width = data[0]
    height = data[1]

    x_start = width/12
    x_inc = width/6

    y_start = height/3
    y_inc = x_inc
    # print(data[3])
    print(data[3])
    my_map = list(map(numpy.uint16, read.asDirect()[2]))
    print(numpy.shape(my_map))
    image_2d = numpy.vstack(my_map)
    imgplot = plt.imshow(image_2d, cmap="rgba")
    plt.show()
    # os.system("gimp block.png")


main()
