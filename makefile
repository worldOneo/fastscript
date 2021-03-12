dirs = ./* runtime/* runtime/Variables/* runtime/Functions/*
OBJS	= $(foreach dirz, $(dirs), \
		$(patsubst %.cpp,%.o,$(wildcard $(dirz).cpp)) \
		)

OUT	 = fastscript
CC	 = g++
FLAGS= -g -Wall -std=c++17

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

%.o: %.cpp
	$(CC) $(FLAGS) -c -o $@ $<

clean:
	rm -f $(OBJS)  