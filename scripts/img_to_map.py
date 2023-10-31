from __future__ import print_function

import sys
from PIL import Image
import numpy as np
import matplotlib.pyplot as plt


class MapParams(object):
    def __init__(self):
        self.origin = []
        self.width = None
        self.height = None
        self.meters_per_cell = None
        self.file_path = "test_map.map"

    def as_string_list(self):
        data = self.origin + [self.width, self.height, self.meters_per_cell]
        return [str(ele) for ele in data]


params = MapParams()


def convert_img(img_path):
    img = np.array(Image.open(img_path).convert("L")).astype(int)
    img = 127 - img  # Convert to -128, 127 range.

    print("Take a look at the map and modify the image accordingly.")
    print("Low = free cell, high = occupied cell.")
    print("Take note of which cell you'd like to use at the origin (defaults to the center cell).")

    plt.figure()
    plt.title("Map to be saved")
    plt.imshow(img)
    plt.colorbar()
    plt.show()

    get_params(img)

    # Flip the image so the bottom left cell is the global origin.
    img = np.flip(img, axis=0)

    map_data = ' '.join(params.as_string_list()) + "\n"
    with open(params.file_path, 'w') as f:
        f.write(map_data)
        for row in img:
            f.write(' '.join([str(ele) for ele in row]))
            f.write("\n")

    print("Wrote map file to: {}".format(params.file_path))


def get_params(img):
    file_path = input("Enter the path to save the map: (default: {}) ".format(params.file_path))
    if len(file_path) < 1 or not file_path.endswith(".map"):
        file_path = params.file_path
        print("Using default path {}".format(params.file_path))
    params.file_path = file_path

    params.width, params.height = img.shape

    map_width = float(input("Enter the width of the map (meters): "))
    params.meters_per_cell = map_width / params.width

    print("Using {} meters per cell. Map size is {}x{} cells.".format(params.meters_per_cell,
                                                                      params.width,
                                                                      params.height))

    origin_cell = [params.width // 2, params.height // 2]
    cell_input = input("Enter the origin cell, comma separated: (default: [{}, {}]) ".format(*origin_cell))

    if len(cell_input) > 1:
        origin_cell = [int(ele.strip()) for ele in cell_input.split(",")]
    print ("Using origin [{}, {}]".format(*origin_cell))

    params.origin = [-params.meters_per_cell * origin_cell[0] - params.meters_per_cell / 2,
                     -params.meters_per_cell * origin_cell[1] - params.meters_per_cell / 2]


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Usage: python img_to_map.py [PATH_TO_IMG]")
        exit()

    img_path = sys.argv[1]

    convert_img(img_path)
