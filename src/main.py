#!/usr/bin/env python3
import sys

class Photo(object):
    def __init__(self, nb, v, nbtags, tags):
        self.nb = nb
        self.v = v
        self.nbtags = nbtags
        self.tags = tags

    def __str__(self):
        return str(self.v) + str(self.nbtags) + str(self.tags)

    def __repr__(self):
        return str(self)

    def print(self):
        print(self.nb)

def parse(filename):
    raw = []
    with open(filename) as f:
            size = f.readline()
            i = 0
            for data in f:
                photo = Photo(i, data.split()[0], data.split()[1], set(data.split()[2:]))
                i += 1
                if (photo.v == 'H'):
                    raw.append(photo)
    return raw


def dump(res):
        print(len(res))
        for data in res:
                print(data)
        return;

if __name__ == "__main__":
    res = []


    filename = sys.argv[1]
    raw = parse(filename)

    for i in raw:
            res.append(i.nb)
    dump(res)
