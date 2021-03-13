dirs = ./* runtime/* runtime/Variables/* runtime/Functions/* runtime/LiveFunctions/*
OBJS	= $(foreach dirz, $(dirs), \
		$(patsubst %.cpp,%.o,$(wildcard $(dirz).cpp)) \
		)

OUT	 = fastscript
CC	 = g++
FLAGS= -Wall -std=c++17

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

release: $(OBJS)
	$(CC) $(OBJS) -o $(OUT)

%.o: %.cpp
	$(CC) $(FLAGS) -g -c -o $@ $<

clean:
	rm -f $(OBJS)  