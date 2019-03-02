#include <stdlib.h>
#include <stdio.h>
#include <string.h>
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



char* cipher_with_key(char* message, char* key);

int main(int argc, char* argv[]){

    char* action; 
    char* to_open;
    char* key;
    char* message;
    FILE * file;

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
        int length = ftell (file);
        fseek (file, 0, SEEK_SET);
        message = malloc (length);

        
        //I'm only using fgets() here because our test file is one line.
        //I want to be able to grab an entire file and cast it to a string at some point.
        fgets(message, "%s" , file);
        printf("%s \n", message);//error check

        if(message == NULL){//make sure message was pulled from file properly
            printf("No message.\n");
            return -1;
        }else printf("Message read successfully\n");

        char* encoded = cipher_with_key(message, key);//run cipher
        printf("Message: %s\n", encoded);

    }   
    return 0;

}




char* cipher_with_key(char* message, char* key){
    printf("\nBeginning Cipher . . .\n \n");
    char* encoded;
    int k;
    for(int i = 0; i < strlen(message) ; i++){

        /*
        There are hella bugs in this part. 
        I'm having trouble going from 
        [char->ASCII->thru cipher algorithm->ASCII->char] and it fucks some shit up.
        */
        printf("iterated for loop %d times\n",i);
        if(isalpha(message[i]) == 0){
            printf("checking message index %d", i);
            printf("character \"%c\"  in message must be alphabetical\n", message[i]);
        }
        k = i;
        if(message[i] == NULL){
            printf("message index is null. breaking.\n");
            break;
        }
        if(key[i] == NULL){
            printf(" Attempting to wrap key\n");
            k = i % strlen(key);
        }
        //combine key and 
        int x = ((message[i] + key[k])-65 % 26)+65;
        printf("ASCII for iteration %d is %d", i, x);
        x = x + 0;
        printf("%c", message[i]);
        encoded[i] = x;

        //return if message is finished
        if(message[i+1] == NULL){
            printf("returning\n");
            return encoded;
        }
    }
    

}

