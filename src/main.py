#!/usr/bin/env python3
import sys

class Photo(object):
    def __init__(self, pos, v, nbtags, tags):
        self.pos = pos
        self.v = v
        self.nbtags = nbtags
        self.tags = tags

    def __str__(self):
        return str(self.v) + str(self.nbtags) + str(self.tags)

    def __repr__(self):
        return str(self)

    def print(self):
        print(self.pos)

def parse(filename):
    raw = []
    vert = []
    with open(filename) as f:
            size = f.readline()
            i = 0
            for data in f:
                photo = Photo(i, data.split()[0], data.split()[1], set(data.split()[2:]))
                i += 1
                if (photo.v == 'H'):
                    raw.append(photo)
                else
                    vert.append(photo)
    raw.sort(key=lambda x: x.nbtags, reverse=True)
    return raw, vert


def dump(res):
        print(len(res))
        for data in res:
                print(data)
        return;

if __name__ == "__main__":
    res = []

    raw = []
    toto=[]

    filename = sys.argv[1]
    (raw, toto) = parse(filename)
    print(raw)
    for i in raw:
            res.append(i.pos)
    dump(res)
