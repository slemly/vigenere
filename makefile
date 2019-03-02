
CC = gcc -g
SRC  = vigenere.c
OBJ = vigenere.o
TARGET = vigenere
USAGE0 = 'This vigenere cipher will encode a .txt file with a key of your choosing.'
USAGE1 = "Usage: ./vigenere <action(r/w)>  <source file>  <cipher key>"
TEST = ./vigenere w secret.txt asdf

test: execute
	$(TEST)
execute: vigenere.o vigenere.h
	$(CC) -o $(TARGET) $(OBJ)
	@echo
	@echo $(USAGE0)
	@echo 
	@echo $(USAGE1)
	@echo
vigenere.o: vigenere.h
	$(CC) -c $(SRC) 
	
clean: 
	/bin/rm -r $(TARGET) $(OBJ) 
