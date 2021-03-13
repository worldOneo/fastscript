dirs = ./* runtime/* runtime/Variables/* runtime/Functions/* runtime/LiveFunctions/*
OBJS	= $(foreach dirz, $(dirs), \
		$(patsubst %.cpp,%.o,$(wildcard $(dirz).cpp)) \
		)

OUT	 = fastscript
CC	 = g++
FLAGS= -Wall -std=c++17

all: FLAGS+= -O3
all: build

debug: FLAGS+= -g
debug: build



build: $(OBJS)
	$(CC) $(OBJS) -o$(OUT)

%.o: %.cpp
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)  