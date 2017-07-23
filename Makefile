CC ?= gcc
CFLAGS += -g -Wall -Wextra -ftrapv -Wshadow -Wundef -Wcast-align -Wunreachable-code
SRC = src/*.c
TEST_SRC = test/*.c


OBJ = dotenv.o
TEST_OBJ = dotenv_test.o
LIB = libdotenv.so


.PHONY: build test


default: build install

build:
	$(CC) $(CFLAGS) -c -fpic -o $(OBJ) $(SRC)
	$(CC) -shared -fpic -o $(LIB) $(OBJ)
	rm $(OBJ)

install:
	sudo mv $(LIB) /usr/lib
	sudo cp src/dotenv.h /usr/include

test: build install
	$(CC) $(CFLAGS) test/*.c -ldotenv -o $(TEST_OBJ)
	./$(TEST_OBJ)

test-valgrind: test
	valgrind --track-origins=yes --leak-check=full --show-reachable=yes ./$(TEST_OBJ)
