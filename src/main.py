import sys

def parse():
        filename = sys.argv[1]
        with open(filename) as f:
                size = f.readline()
                for data in f:
                        raw.append(data.split( ))
        return size, raw

res = []

s_size = 0

def dump():
        print(s_size)
        for data in res:
                print(data)
        return;



size = 0
raw = []

(size, raw) = parse()
s_size = size[0]
for i in range(0, int(size)):
        res.append(i)
dump()
