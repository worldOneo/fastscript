dirs = ./* runtime/* runtime/Variables/* runtime/Functions/* runtime/LiveFunctions/*
OBJS	= $(foreach dirz, $(dirs), \
		$(patsubst %.cpp,%.o,$(wildcard $(dirz).cpp)) \
		)

OUT	 = fastscript
CC	 = g++
FLAGS= -Wall -std=c++17

all: build

debug: FLAGS+= -g
debug: build



build: $(OBJS)
	$(CC) $(OBJS) -O3  -o$(OUT)

%.o: %.cpp
	$(CC) $(FLAGS) -O3 -c -o $@ $<

clean:
	rm -f $(OBJS)  