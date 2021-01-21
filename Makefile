
CXX       := g++
CXX_FLAGS := -std=c++17 -ggdb

BIN     := ./bin
SRC     := ./src
INCLUDE := ./inc

LIBRARIES   :=
EXECUTABLE  := main.exe


all: $(BIN)/$(EXECUTABLE)

run: ./$(BIN)/$(EXECUTABLE)

$(BIN)/$(EXECUTABLE): $(SRC)/*.cpp
	$(CXX) $(CXX_FLAGS) -I"$(INCLUDE)" $^ -o $@ $(LIBRARIES)

clean:
	rm -f $(BIN)/*
