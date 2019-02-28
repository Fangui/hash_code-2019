#!/usr/bin/env python3
from src.main import parse
from pprint import pprint
import sys
files = ["a_example.txt", "b_lovely_landscapes.txt", "c_memorable_moments.txt", "d_pet_pictures.txt", "e_shiny_selfies.txt"]
fi = files[2]

fi = sys.argv[1]

def next_same_tag(dataset, obj):
    for num, entry in enumerate(dataset,0):
        if obj.tags.intersection(entry.tags) and obj.v != "V":
            dataset.remove(entry)
            return entry
    return None



dataset = parse(fi)
out = []
cur = dataset[0]
dataset.remove(cur)
out += "0"
while len(dataset) > 0:
    cur = next_same_tag(dataset, cur)
    if cur is None:
        cur = dataset[0]
        dataset.remove(cur)
    out.append(cur.pos)

with open("lol.out", "w") as f:
    f.write(str(len(out)))
    f.write("\n")
    for line in out:
        f.write(str(line))
        f.write("\n")
