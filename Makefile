LD := ld
CP := cp
CXX := g++
CXXFLAGS := -std=c++17
OPT := -O3
DEBUG := -O0


INC_DIR := -I./include

SRCS := $(wildcard src/*.cpp)
OBJS := $(SRCS:.cpp=.o)
TARGET := $(SRCS:.cpp=)
BIN := $(notdir $(TARGET))

all: $(OBJS) bin
	for x in $(BIN); do \
		$(CXX) src/$$x.o -o bin/$$x; \
	done

bin:
	mkdir bin

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(OPT) $(INC_DIR) -c $< -o $@

.PHONY: clean print

print:
	@echo $(OBJS) $(SRCS) $(TARGET) $(BIN)

clean:
	rm -rf $(OBJS) $(BIN)