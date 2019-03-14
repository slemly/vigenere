#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "vigenere.h"
#include <stdio.h>

/**
 * my idea for this is to take arguments from command line and scramble a file with a given key, 
 * then unscramble that same file with the same key if a different action argument is passed.
 * 
 * Usage is <make test>. Everything should compile now but I'm having some trouble down in the
 * cipher_with_key() function.
 * 
 * 90% of these print statements are just error checks, so remove/add at your lesiure.
 * 
*/


//FUNCTION PROTOTYPES
char* cipher_with_key(char* message, char* key);
char* concat(char* s1, char* s2);
char* uncipher(char* s1, char* s2);
void print_usage(void);



int main(int argc, char* argv[]){

    char* action; 
    char* to_open;
    char* key;
    char* message;
    FILE* file;
    int length;
    char* encoded;

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
    else if(argc != 4){
        print_usage();
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
        message = malloc (length * 2);

        
        //I'm only using fgets() here because our test file is one line.
        //I want to be able to grab an entire file and cast it to a string at some point.
        fgets(message, "%s" , file);
        if(message == NULL){//make sure message was pulled from file properly
            printf("No message.\n");
            return -1;
        }else printf("Message : %s \n", message);//error check

        encoded = cipher_with_key(message, key);//run cipher
        printf("Message: %s\n", encoded);
        char* temp = "encoded_";
        char* encoded_filename = concat(temp, to_open);
        printf(" \n \n \nFilename : %s \n", encoded_filename);
        FILE* coded_file = fopen(encoded_filename, "w");
        fprintf(coded_file, "%s", encoded);
        fclose(coded_file);
        


        //Here's where we write the encoded message to a new file.
        //FILE* source = fopen("encoded_" + to_open, "r");
        
    }  
    //free(encoded);
    //free(message); 
    if( 0 == strcmp("r", action) || 0 == strcmp("R", action)){
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
        message = malloc (length * 2);

        
        //I'm only using fgets() here because our test file is one line.
        //I want to be able to grab an entire file and cast it to a string at some point.
        fgets(message, "%s" , file);
        if(message == NULL){//make sure message was pulled from file properly
            printf("No message.\n");
            return -1;
        }else printf("Message : %s \n", message);//error check

        encoded = uncipher(message, key);//run cipher
        printf("Message: %s\n", encoded);
        char* temp = "decoded_";
        char* encoded_filename = concat(temp, to_open);
        printf(" \n \n \nFilename : %s \n", encoded_filename);
        FILE* coded_file = fopen(encoded_filename, "w");
        fprintf(coded_file, "%s", encoded);
        fclose(coded_file);
        

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
    char* encoded = (char*)malloc(sizeof(strlen(message))+1);
    int k;
    char new_letter;
    for(int i = 0; i < strlen(message) ; i++){

        /*
        There are many bugs in this section. 
        I'm having trouble going from 
        [char->ASCII->thru cipher algorithm->ASCII->char].
        */

        int x;
        k = i;
        if(key[k] == NULL){
            printf("Wrapping key . . .\n");
            k = i % strlen(key);
        }
        printf("checking message index %d \n", i);

        //combine key and message.
        x = (((int)message[i] + (int)key[k]) % 128);
        encoded[i] = (char)x;

        //return if message is finished. Doing this up at the top results in seg faults.
        if(message[i+1]== NULL){
            printf("Index %d is null. Returning.\n \n \n \n", i+1);
            return encoded;
        }
    }
}

char* uncipher(char* message, char* key){
    //curr val, +128, -key[i]
     printf("\nBeginning Cipher . . .\n \n");
    char* decoded = (char*)malloc(sizeof(strlen(message))+1);
    int k =0;
    char new_letter;
    for(int i = 0; i < strlen(message) ; i++){

        
        //There are many bugs in this section. 
        //I'm having trouble going from 
        //[char->ASCII->thru cipher algorithm->ASCII->char].
        
        int x;
        if(key[k+1] == NULL){
            printf("Wrapping key . . .\n");
            k = k % strlen(key);
        }
        printf("checking message index %d \n", i);
    
        //combine key and message.
        x = (((int)message[i] + 128) - (int)key[i]) % 128;  
        printf("index  %d  ascii  is %d \n", i, x);      
        new_letter = (char)x;
        decoded[i] = new_letter;

        //return if message is finished. Doing this up at the top results in seg faults.
        if(message[i+1] == NULL){
            printf("Index %d is null. Returning.\n \n \n \n", i+1);
            return decoded;
        }
        k++;
    }


    return NULL;
}



void print_usage(void){
    printf("Usage: ./vigenere <action(r/w)>  <source file>  <cipher key> \n");
    return;
} 

