CXX ?= g++
CXXFLAGS += -Wall -Wextra -std=c++17 -pedantic  -fopenmp -g

SRC = main.cc parse.cc
OBJS = ${SRC:.cc=.o}
BIN = main

all: $(BIN)

main: ${OBJS}
	$(CXX) $(CXXFLAGS)  ${OBJS} -o $(BIN)

check: CXXFLAGS = -g3 -fopenmp
check: $(BIN)

hash:
	./$(BIN) ../a_example.txt out1
	./$(BIN) ../b_lovely_landscapes.txt out2

run:
	../launch.sh

.PHONY: clean check
clean:
	${RM} ${OBJS}
	${RM} $(BIN)
