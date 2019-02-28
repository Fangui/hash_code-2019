CXX ?= g++
CXXFLAGS += -Wall -Wextra -std=c++17 -pedantic -O3 -fopenmp

SRC = main.cc parse.cc
OBJS = ${SRC:.cc=.o}
BIN = main

all: $(BIN)

main: ${OBJS}
	$(CXX) $(CXXFLAGS)  ${OBJS} -o $(BIN)

check: CXXFLAGS = -g3 -fopenmp
check: $(BIN)

hash:
	./$(BIN) test out1
	./$(BIN) test out2

run:
	../launch.sh

.PHONY: clean check
clean:
	${RM} ${OBJS}
	${RM} $(BIN)
