CC=g++
# CFLAGS= 
CFLAGS= -Wall -g
BIN_DIR=./bin
SRC_DIR=.

all: otmizacao

otmizacao: main.o
	$(CC) $(CFLAGS) -o $(BIN_DIR)/main $(BIN_DIR)/main.o

main.o: $(SRC_DIR)/main.cpp
	$(CC) $(CFLAGS) -c $(SRC_DIR)/main.cpp -o $(BIN_DIR)/main.o

clean:
	clear
	rm -rf $(BIN_DIR)/*.o
	rm -rf $(BIN_DIR)/main