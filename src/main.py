#!/usr/bin/env python3
import sys

def parse(filename):
    raw = []
    with open(filename) as f:
            size = f.readline()
            for data in f:
                    raw.append(data.split( ))
    return size, raw


def dump(res, s_size):
        print(s_size)
        for data in res:
                print(data)
        return;

if __name__ == "__main__":
    res = []
    s_size = 0

    size = 0

    filename = sys.argv[1]
    (size, raw) = parse(filename)
    s_size = size[0]
    for i in range(0, int(size)):
            res.append(i)
    dump(res, s_size)
