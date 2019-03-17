/*
@author Samuel Lemly
@version March 2019
CS448


All code aside from the concat() function was written by Sam Lemly 
*/


#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "vigenere.h"
#include <stdio.h>


//FUNCTION PROTOTYPES
char* cipher_with_key(char* message, char* key);
char* concat(char* s1, char* s2);
char* uncipher(char* s1, char* s2);
void print_usage(void);
char* init_alphabet_array(void);
char* get_message(FILE* file);
int get_filesize(FILE* file);

int main(int argc, char* argv[]){

    char* action; 
    char* to_open;
    char* key;
    char* message;
    FILE* file;
    int length;
    char* encoded;

    if(argc == 4){
        action = argv[1];
        to_open = argv[2];
        key = argv[3];
    }
    else if(argc != 4){
        print_usage();
    }
    if(key == NULL){
        printf("No key given\n");
        print_usage();
        return -1;
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
       
        char* message =(char*)malloc(sizeof(char) * get_filesize(file));
        message = get_message(file);
        if(message == NULL){
            printf("No message.\n");
            return -1;
        }//error check
        encoded = cipher_with_key(message, key);//run cipher
        printf("%s\n", encoded);
        char* temp = "encoded_";
        char* encoded_filename = concat(temp, to_open);
        printf("\nFilename : %s \n", encoded_filename);
        FILE* coded_file = fopen(encoded_filename, "w");
        printf("Encoded length: %d \n", (int)strlen(encoded));
        fprintf(coded_file, "%s", encoded);
        fclose(coded_file);
        free(message);
        free(encoded);
    }  
    if( 0 == strcmp("r", action) || 0 == strcmp("R", action)){
        file = fopen(to_open , "r" );
        if(file != NULL){
            printf("File opened successfully\n");
        }else{
            printf("failed to open file\n"); 
            return -1;
        }
        char* message =(char*)malloc(sizeof(char) * get_filesize(file));
        message = get_message(file);
        encoded = uncipher(message, key);//run cipher
        printf("%s\n", encoded);
        char* temp = "decoded_";
        char* encoded_filename = concat(temp, to_open);
        printf("\nFilename : %s \n", encoded_filename);
        FILE* coded_file = fopen(encoded_filename, "w");
        fprintf(coded_file, "%s", encoded);
        fclose(coded_file);
        free(encoded_filename);
        free(message);
    }
    return 0;
}

char* cipher_with_key(char* message, char* key){
    printf("\nBeginning Cipher . . .\n \n");
    char* encoded = (char*)malloc(sizeof(strlen(message)));
    int k = 0;
    char new_letter;
    for(int i = 0; i < strlen(message) ; i++){
        int x;
        if(key[k] == NULL){
            k = k % strlen(key);
        }
        //combine key and message.
        if(isalpha(message[i])){   
            x = ((((int)message[i])-32 + ((int)key[k])-32) % 96) +32;
        }
        else if((int)message[i] == 10){
            x = 10;
        }
        else if((int)message[i] == 46){
            x = 46;
        }
        else
            x = (int)(message[i]);
        encoded[i] = (char)x;
        //return if message is finished. Doing this up at the top results in seg faults.
        if(message[i+1]== NULL){
            return encoded;
        }
        k++;
    }
}

char* uncipher(char* message, char* key){
    printf("\nBeginning Cipher . . .\n \n");
    char* decoded = (char*)malloc(sizeof(strlen(message)));
    int k =0;
    char new_letter;

    for(int i = 0; i < strlen(message) ; i++){
        int x;
        if(key[k] == NULL){
            k = k % strlen(key);
        }
        
        if(message[i] != 10){
            x = ((((int)message[i])-32 + 96) - ((int)key[k])) %  96;
            x = x+64;
            // if(!isalpha(x))
            //     x = message[i];
            if((int)message[i] >= 32 && (int)message[i] <= 47){
                x = message[i];
            }
        }else{
            x = 10;
        }   
        new_letter = (char)x;
        decoded[i] = new_letter;
        k++;    
        //return if message is finished. Doing this up at the top results in seg faults.
        if((int)message[i+1] == 0){
            return decoded;
        }
    }
    return NULL;
}

void print_usage(void){
    printf("Usage: ./vigenere <action(r/w)>  <source file>  <cipher key> \n");
    return;
} 

char* get_message(FILE* file){
    int i = 0;
    char* message =(char*)malloc(sizeof(char) * get_filesize(file));
    rewind(file);
    while(fscanf(file, "%c", &message[i]) != EOF){
        i++;
    }
    return message;
}

int get_filesize(FILE* file){
    char* ch;
    int filelen;
    while((ch=(char)fgetc(file)) != EOF){
        filelen ++;
    }
    return filelen;
}

char* concat(char *s1, char *s2){
    char *result = (char*)malloc(strlen(s1) + strlen(s2) + 1);
    strcpy(result, s1);
    strcat(result, s2);
    return result;
}


