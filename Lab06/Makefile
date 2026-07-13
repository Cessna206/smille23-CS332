# Makefile for Lab06
# wanted a way to automatically clean the csv files. 
# this was the only way I could figure out how to do that

CC = gcc
CFLAGS = -Wall
TARGET = lab06
SRC = smille23lab06.c

$(TARGET): $(SRC)
	$(CC) $(CFLAGS) -o $(TARGET) $(SRC)

run: $(TARGET)
	./$(TARGET) listings.csv

see:
	@echo "______________SORTED BY HOST NAME FIRST 5 LINES_________________"
	@echo " "
	@head -n 5 sorted_by_host_name.csv
	@echo "______________SORTED BY PRICE FIRST 5 LINES_____________________"
	@echo " "
	@head -n 5 sorted_by_price.csv

clean:
	rm -f $(TARGET) sorted_by_host_name.csv sorted_by_price.csv

.PHONY: run clean
