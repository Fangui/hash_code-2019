#!/bin/sh
PROG="./main.py"
PROG="./lol.py"
python $PROG ./a_example.txt > ./A.out
python $PROG ./b* > ./B.out
python $PROG ./c* > ./C.out
python $PROG ./d* > ./D.out
python $PROG ./e* > ./E.out

zip ../code.zip ../src
