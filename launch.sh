#!/bin/sh
PROG="./main.py"
PROG="./lol.py"
echo "Generating A:"
python $PROG ./a_example.txt > ./A.out
echo "Generating B:"
python $PROG ./b* > ./B.out
echo "Generating C:"
python $PROG ./c* > ./C.out
echo "Generating D:"
python $PROG ./d* > ./D.out
echo "Generating E:"
python $PROG ./e* > ./E.out

echo zipping:
zip ../code.zip ../src
