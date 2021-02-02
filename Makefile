
CXX       := g++
CXX_FLAGS := -std=c++17

BIN     := ./bin
SRC     := ./src
INCLUDE := ./inc

LIBRARIES   :=
EXECUTABLE  := dut.exe

SRCS := $(wildcard $(SRC)/*.cpp)
OBJS := $(SRCS:$(SRC)/%.cpp=$(BIN)/%.o)

$(BIN)/%.o: $(SRC)/%.cpp
	$(CXX) $(CXX_FLAGS) -I"$(INCLUDE)" $< -c -o $@ $(LIBRARIES)

all: $(BIN)/$(EXECUTABLE)
	

run: ./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(OBJS)
	$(CXX) $(OBJS) -o $@ $(LIBRARIES)

clean:
#	rm -rf $(BIN)/* #Figure out why this is not working