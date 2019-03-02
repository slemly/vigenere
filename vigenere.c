#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include "vigenere.h"

/**
 * my idea for this is to take arguments from command line and scramble a file with a given key, 
 * then unscramble that same file with the same key if a different action argument is passed.
 * 
 * Usage is in the makefile. Everything should compile now but I'm having some trouble down in the
 * cipher_with_key() function.
 * 
 * 
 * 90% of these print statements are just error checks, so remove/add at your lesiure.
 * 
*/


//FUNCTION PROTOTYPES
char* cipher_with_key(char* message, char* key);
char* concat(char* s1, char* s2);



int main(int argc, char* argv[]){

    char* action; 
    char* to_open;
    char* key;
    char* message;
    FILE* file;
    int length;

    if(argc == 4){
        //assign args to variables. 
        // TODO: implement some functions to check if the args are right for usage.
        printf("Assigning variables\n");
        action = argv[1];
        to_open = argv[2];
        key = argv[3];
        printf("%s \n", action);
        printf("%s \n", to_open);
        printf("%s \n", key);
    }
    if( 0 == strcmp("w", action) || 0 == strcmp("W", action)){
        //Open file to read
        file = fopen(to_open , "r" );
        if(file != NULL){
            printf("File opened successfully\n");
        }else{
            printf("failed to open file\n"); 
        return -1;
        }

        //get length of file
        fseek (file, 0, SEEK_END);
        length = ftell (file);
        fseek (file, 0, SEEK_SET);
        message = malloc (length);

        
        //I'm only using fgets() here because our test file is one line.
        //I want to be able to grab an entire file and cast it to a string at some point.
        fgets(message, "%s" , file);
        if(message == NULL){//make sure message was pulled from file properly
            printf("No message.\n");
            return -1;
        }else printf("Message : %s \n", message);//error check

        char* encoded = cipher_with_key(message, key);//run cipher
        printf("Message: %s\n", encoded);
        char* temp = "encoded";
        char* encoded_filename = concat(temp, to_open);
        printf("Filename : %s \n", encoded_filename);


        //Here's where we write the encoded message to a new file.
        //FILE* source = fopen("encoded_" + to_open, "r");

    }   
    return 0;

}


//stolen from Stack Overflow
char* concat(char *s1, char *s2){
    char *result = malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}

char* cipher_with_key(char* message, char* key){
    printf("\nBeginning Cipher . . .\n \n");
    char* encoded = (char*)malloc(sizeof(strlen(message)));
    int k;
    char new_letter;
    for(int i = 0; i < strlen(message) ; i++){

        /*
        There are hella bugs in this part. 
        I'm having trouble going from 
        [char->ASCII->thru cipher algorithm->ASCII->char] and it fucks some shit up.
        */
        int x;
        k = i;
        printf("checking message index %d \n", i);
        if(isalpha(message[i]) == 0){ 
            printf("character \"%c\"  in message must be alphabetical\n", message[i]);
        }
        
        if(message[i] == NULL){
            printf("Message index is null. breaking.\n");
            break;
        }
        if(key[i] == NULL){
            printf(" Attempting to wrap key\n");
            k = i % strlen(key);
        }
        //combine key and message.
        if((int)message[i] != 32){
            x = (((int)message[i] + (int)key[k])-65 % 26);
        }
        printf("ASCII for iteration %d is %d \n", i, x);
        //here is where our issue is: converting an int to an ASCII character.
        //We could try to remain alphanumeric but could use all ASCII characters.
        new_letter = (char)x;
        printf("%c \n", message[i]);
        encoded[i] = new_letter;
        printf("encoded char : %c \n", encoded[i]);

        //return if message is finished
        if(message[i+1] == NULL){
            printf("Index %d is null. Returning.\n", i);
            return encoded;
        }
    }
    

}

