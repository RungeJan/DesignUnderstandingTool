
CXX       := g++
CXX_FLAGS := -std=c++17 -ggdb

BIN     := ./bin
SRC     := ./src
INCLUDE := ./inc

LIBRARIES   :=
EXECUTABLE  := dut.exe

SRCS := $(wildcard $(SRC)/*.cpp)
OBJS := $(SRCS:$(SRC)/%.cpp=%.o)

%.o: $(SRC)/%.cpp
	$(CXX) $(CXX_FLAGS) -I"$(INCLUDE)" $< -c -o $(BIN)/$@ $(LIBRARIES)

all: $(OBJS) $(BIN)/$(EXECUTABLE)
	

run: ./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): 
#	$(OBJS)
	$(CXX)  $(OBJS:%.o=$(BIN)/%.o) -o $@ $(LIBRARIES)

clean:
	rm -f $(BIN)/*
