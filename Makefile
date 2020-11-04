# author: Jiri Kristof
# file: Makefile
# FIT VUT 2020
# ISA project - DNS server

SRC = src
CC = gcc
SRC_FILES = src/argparse.cpp src/main.cpp src/err_handler.cpp

dns:
	$(CC) $(SRC_FILES) -lstdc++ -o dns
