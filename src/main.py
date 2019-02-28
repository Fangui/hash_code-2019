#!/usr/bin/env python3
import sys

class Photo(object):
    def __init__(self, v, nbtags, tags):
        self.v = v
        self.nbtags = nbtags
        self.tags = tags

    def __str__(self):
        return str(self.v) + str(self.nbtags) + str(self.tags)

    def __repr__(self):
        return str(self)

def parse(filename):
    raw = []
    with open(filename) as f:
            size = f.readline()
            for data in f:
                photo = Photo(data.split()[0], data.split()[1], set(data.split()[2:]))
                if (photo.v == 'H'):
                    raw.append(photo)
    return size, raw


def dump(res):
        print(len(res))
        for data in res:
                print(data)
        return;

if __name__ == "__main__":
    res = []

    size = 0

    filename = sys.argv[1]
    (size, raw) = parse(filename)
    s_size = size[0]


    for i in range(0, len(res)):
            res.append(i)
    dump(res)
