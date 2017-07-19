CXX = g++
CXXFLAGS += -Wall -O3 -std=c++11 -MMD

RM = rm -rf

SRCS := $(wildcard *.cpp)
DEPS := $(SRCS:%.cpp=%.d)
BINS := $(SRCS:%.cpp=%)

LIBS = simple_graph_io

all: $(BINS)

-include $(DEPS)

include ../Makefile.base

$(BINS): $(BASELIBS)
	$(CXX) $(CXXFLAGS) -I$(INCLUDEDIR) $@.cpp -o $@ $(LINKOPTS)

clean:
	$(RM) $(BINS)
	$(RM) $(DEPS)
	$(RM) edge.bin

test: $(DATADIR)/edge.txt $(BINS)
	@echo "edge.txt:"
	@cat $(DATADIR)/edge.txt
	cat $(DATADIR)/edge.txt | ./text2bin > edge.bin
	ls -l edge.bin
	cat edge.bin | ./bin2text

