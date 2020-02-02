import numpy as np
import cv2

# Size of block grid.  If this is variable, we need another way to
# determine this
grid_dimension = 6.0

def get_grid_from_file(fn):
    # Image of game board
    #fn = 'block.png'
    #fn = 'Screenshot_20190528-122609.jpg'

    # H, S, V thresholds for identifying orange blocks
    lower_orange = np.array([10, 200, 200])
    upper_orange = np.array([20, 255, 255])

    # H, S, V thresholds for identifying red block
    lower_red = np.array([0, 200, 200])
    upper_red = np.array([10, 255, 255])

    # Target resolution for the screenshot
    desired_width = 300.0

    # Any dimension smaller than this is considered a unit grid size
    grid_threshold = desired_width / grid_dimension

    # Array of grid sizes identified
    grid_sizes = []
    grid_lefts = []
    grid_tops = []

    # Character Grid
    char_grid = np.full((int(grid_dimension), int(grid_dimension)), '.', dtype=np.dtype('U'))

    # Read in file, determine size, scaling, and scale the image
    img0 = cv2.imread(fn, 1)
    height, width, depth = img0.shape
    imgScale = desired_width / width
    img1 = cv2.resize(img0, None, fx=imgScale, fy=imgScale)

    #cv2.imshow('input', img1)
    #cv2.waitKey(0)

    img1_orange = img1.copy()
    img1_red = img1.copy()
    hsv1 = cv2.cvtColor(img1, cv2.COLOR_BGR2HSV)

    # Identify a mask for orange areas
    orange = cv2.inRange(hsv1, lower_orange, upper_orange)
    #cv2.imshow('orange', orange)
    #cv2.waitKey(0)

    # Process the orange areas to get good blobs
    blurred_orange = cv2.GaussianBlur(orange, (5, 5), 0)
    orange = cv2.threshold(blurred_orange, 60, 255, cv2.THRESH_BINARY)[1]
    #cv2.imshow('orange', orange)
    #cv2.waitKey(0)

    # Find shapes in the "orange" image
    orange_contours, hierarchy = cv2.findContours(orange, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    for cnt in orange_contours:
        x, y, w, h = cv2.boundingRect(cnt)
        grid_sizes = np.append(grid_sizes, w, h)
        grid_lefts = np.append(grid_lefts, x)
        grid_tops = np.append(grid_tops, y)
        img1_orange = cv2.rectangle(img1_orange, (x, y), (x+w, y+h), (0, 255, 0), 2)
    #cv2.imshow('orange',img1_orange)
    #cv2.waitKey(0)

    # Identify a mask for the red areas (expecting only one)
    red = cv2.inRange(hsv1, lower_red, upper_red)
    #cv2.imshow('red', red)
    #cv2.waitKey(0)

    # Process the red areas to get good blobs
    blurred_red = cv2.GaussianBlur(red, (5, 5), 0)
    red = cv2.threshold(blurred_red, 60, 255, cv2.THRESH_BINARY)[1]
    #cv2.imshow('red', red)
    #cv2.waitKey(0)

    # Find shapes in the "red" image
    red_contours, hierarchy = cv2.findContours(red, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)
    for cnt in red_contours:
        x, y, w, h = cv2.boundingRect(cnt)
        if (y>10) : # The swipeing debug overlay can be at the top, just don't allow it to be picked
            grid_sizes = np.append(grid_sizes, w, h)
            grid_lefts = np.append(grid_lefts, x)
            grid_tops = np.append(grid_tops, y)
            img1_red = cv2.rectangle(img1_red, (x, y), (x+w, y+h), (0, 255, 0), 2)
    #cv2.imshow('red',img1_red)
    #cv2.waitKey(0)

    # Print out some statistics
    #print(grid_sizes)
    #print(grid_lefts)
    #print(grid_tops)
    grid_size = np.average(grid_sizes[grid_sizes<grid_threshold])
    grid_left = np.min(grid_lefts)
    grid_top = np.min(grid_tops)
    #print("grid size = ", grid_size)
    #print("grid left = ", grid_left)
    #print("grid top = ", grid_top)

    # Go through all of the orange blocks and output debug info, plus add to the character grid
    block_number = 0
    for cnt in orange_contours:
        x, y, w, h = cv2.boundingRect(cnt)
        grid_x = int((x - grid_left) / grid_size);
        grid_y = int((y - grid_top) / grid_size);
        #print(y, x, grid_y, grid_x, h, w, int(h / grid_size + 0.5), int(w / grid_size + 0.5))
        for i in range(int(h / grid_size + 0.5)):
            for j in range(int(w / grid_size + 0.5)):
                #print(chr(ord('A') + block_number), i, j)
                char_grid[grid_y + i][grid_x + j] = chr(ord('a') + block_number)
        block_number = block_number + 1

    # Go through all of the red blocks and output debug info, plus add to the character grid
    for cnt in red_contours:
        x, y, w, h = cv2.boundingRect(cnt)
        grid_x = int((x - grid_left) / grid_size);
        grid_y = int((y - grid_top) / grid_size);
        #print(y, x, grid_y, grid_x, h, w, int(h / grid_size + 0.5), int(w / grid_size + 0.5))
        for i in range(int(h / grid_size + 0.5)):
            for j in range(int(w / grid_size + 0.5)):
                #print(chr(ord('A') + block_number), i, j)
                char_grid[grid_y + i][grid_x + j] = chr(ord('a') + block_number)
        block_number = block_number + 1

    cv2.destroyAllWindows()
    return char_grid, grid_left / imgScale, grid_top / imgScale, grid_size / imgScale

def print_grid(char_grid):
    # Print out the character representation of the blocks
    for i in range(int(grid_dimension)):
        line = ''
        for j in range(int(grid_dimension)):
            line = line + char_grid[i][j]
        print(line)

def save_grid(char_grid, fn):
    file = open(fn, "w") 
    # Save the character representation of the blocks to a file
    for i in range(int(grid_dimension)):
        line = ''
        for j in range(int(grid_dimension)):
            file.write(char_grid[i][j])
        file.write("\n")
    file.close() 