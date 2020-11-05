# author: Jiri Kristof
# file: Makefile
# FIT VUT 2020
# ISA project - DNS server

.PHONY: dns test

SRC = src
CC = gcc
SRC_FILES = src/argparse.cpp src/main.cpp src/err_handler.cpp src/func.cpp src/filter.cpp
TEST_FILES = test/unit_test.cpp

dns:
	$(CC) $(SRC_FILES) -lstdc++ -o dns

test:
	$(CC) $(SRC_FILES) $(TEST_FILES) -lstdc++ -o test
	./test
