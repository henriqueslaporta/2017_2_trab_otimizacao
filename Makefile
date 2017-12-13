CC=g++
CVERSION= -std=c++11
CFLAGS= -Wall -g
BIN_DIR=./bin
SRC_DIR=.

all: clean otmizacao

otmizacao: main.o
	$(CC) $(CFLAGS) $(CVERSION) -o $(BIN_DIR)/main $(BIN_DIR)/main.o

main.o: $(SRC_DIR)/main.cpp
	$(CC) $(CFLAGS) $(CVERSION) -c $(SRC_DIR)/main.cpp -o $(BIN_DIR)/main.o

clean:
	clear
	rm -rf $(BIN_DIR)/*.o
	rm -rf $(BIN_DIR)/main