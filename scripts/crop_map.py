from __future__ import print_function
import os
import sys
import numpy as np

PADDING = 10
OUTPUT_MAP = "cropped_map.map"


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


def read_map(map_file):
    params = MapParams()
    params.file_path = map_file
    data = []

    with open(map_file, 'r') as f:
        header = f.readline()
        header = header.strip().split()

        params.origin = [float(ele) for ele in header[:2]]
        params.width, params.height = int(header[2]), int(header[3])
        params.meters_per_cell = float(header[4])

        for line in f.readlines():
            row = line.strip().split(' ')
            row = [int(ele) for ele in row]

            if len(row) != params.width:
                print("Warning: Row has incorrect length", len(row))
                row += [0] * (params.width - len(row))

            data.append(row)

    data = np.array(data)

    # Make sure the
    if data.shape[0] < params.height:
        print("Warning: Map has incorrect number of rows", data.shape[0])
        zeros = np.zeros((params.height - data.shape[0], params.width), dtype=int)
        data = np.concatenate([data, zeros])

    return params, data


def write_map(params, data):
    map_data = ' '.join(params.as_string_list())
    with open(OUTPUT_MAP, 'w') as f:
        f.write(map_data + '\n')
        for row in data:
            f.write(' '.join([str(ele) for ele in row]))
            f.write("\n")


def crop_map(params, data):
    h, w = data.shape

    nonzero = np.nonzero(data)
    min_row, max_row = nonzero[0].min(), nonzero[0].max()
    min_col, max_col = nonzero[1].min(), nonzero[1].max()

    size = max(max_row - min_row + 2 * PADDING + 1, max_col - min_col + 2 * PADDING + 1)
    min_row, max_row = max(min_row - PADDING, 0), min(max_row + PADDING, params.width - 1)
    min_col, max_col = max(min_col - PADDING, 0), min(max_col + PADDING, params.height - 1)
    if size % 2 != 0:
        max_row += 1
        max_col += 1
        size += 1

    size = min(size, h, w)

    if max_row - min_row < size - 1:
        max_row -= 1
        diff = size - 1 - (max_row - min_row)
        max_row += diff // 2
        min_row -= diff // 2
    if max_col - min_col < size - 1:
        max_col -= 1
        diff = size - 1 - (max_col - min_col)
        max_col += diff // 2
        min_col -= diff // 2

    data = data[min_row:max_row + 1, min_col:max_col + 1]

    params.origin[0] += min_col * params.meters_per_cell
    params.origin[1] += min_row * params.meters_per_cell
    params.width = size
    params.height = size

    return params, data


if __name__ == '__main__':
    if len(sys.argv) < 2:
        print("Please provide the path to the map. Usage:")
        print("\n\t python crop_map.py [PATH_TO_MAP]")
        exit()

    map_file = sys.argv[1]
    if not os.path.exists(map_file):
        print("Provided map file", map_file, "does not exist.")
        exit()

    print("Reading map file:", map_file)

    params, data = read_map(map_file)

    print("\nHeader:", params.origin, params.width, params.height, params.meters_per_cell)
    print("Map cell data shape:", data.shape)

    params, data = crop_map(params, data)

    print("\nCropped map to size ({}, {})".format(params.width, params.height))

    write_map(params, data)

    print("\nWrote cropped map to", OUTPUT_MAP)
