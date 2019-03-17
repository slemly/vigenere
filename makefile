
CC = gcc -g
SRC  = vigenere.c
OBJ = vigenere.o
TARGET = vigenere
USAGE0 = 'This vigenere cipher will encode a .txt file with a key of your choosing.'
USAGE1 = "Usage: ./vigenere <action(r/w)>  <source file>  <cipher key>"
TEST = ./vigenere w secret.txt asdfghjkl
TEST1 = ./vigenere r encoded_secret.txt asdfghjkl
TESTFILES = encoded_secret.txt decoded_encoded_secret.txt
CLEAN = make clean

test: execute
	$(TEST)
test1: execute
	$(TEST1)
execute: vigenere.o vigenere.h
	$(CC) -o $(TARGET) $(OBJ)
	@echo
	@echo $(USAGE0)
	@echo 
	@echo $(USAGE1)
vigenere.o: vigenere.h
	$(CC) -c $(SRC) 
clean: 
	/bin/rm -r $(TARGET) $(OBJ) $(TESTFILES)
