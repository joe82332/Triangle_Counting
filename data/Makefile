CXX = g++
CXXFLAGS = -Wall -O3 -std=c++11

RM = rm -rf
WGET = wget --no-use-server-timestamps

all: all_inc

large: all_inc large_inc

include datasets/dimacs10/Makefile.inc

all_inc: $(DIMACS10)

large_inc: $(DIMACS10_LARGE)

clean:
	$(RM) $(DIMACS10_BIN) $(DIMACS10) $(DIMACS10_LARGE)

clean_all: clean
	$(RM) $(shell find | grep archive$$ )
	$(RM) $(shell find | grep ori$$ )

