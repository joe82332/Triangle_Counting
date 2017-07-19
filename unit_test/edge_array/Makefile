CXX = nvcc
CXXFLAGS += -O3 -std=c++11

RM = rm -rf

SRCS := $(wildcard *.cpp)
DEPS := $(SRCS:%.cpp=%.d)
BINS := $(SRCS:%.cpp=%)

LIBS = simple_graph_io simple_graph_io_cuda

all: $(BINS)

-include $(DEPS)

include ../Makefile.base

$(BINS): $(BASELIBS)
	$(CXX) $(CXXFLAGS) -I$(INCLUDEDIR) $@.cpp -o $@ $(LINKOPTS)

clean:
	$(RM) $(BINS)
	$(RM) $(DEPS)

test: $(DATADIR)/edge.txt $(BINS)
	@echo "edge.txt:"
	@cat $(DATADIR)/edge.txt
	cat $(DATADIR)/edge.txt | ./text2array

