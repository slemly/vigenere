/*
@version March 2019
*/
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <ctype.h>
#include "vigenere.h"
#include <stdio.h>
#include <errno.h>

//FUNCTION PROTOTYPES
char* cipher_with_key(char* message, char* key);
char* concat(char* s1, char* s2);
char* uncipher(char* s1, char* s2);
void print_usage(void);
char* init_alphabet_array(void);
char* get_message(FILE* file);
int get_filesize(FILE* file);
char* concatenate_string(char* original, char* add);
//END PROTOTYPES
char* action; 
char* to_open;
char* key;
char* message;
FILE* file;
int length;
char* encoded;

int main(int argc, char* argv[]){

    
    //null checks for bad argument values
    if(argc == 4){
        action = argv[1];
        to_open = argv[2];
        key = argv[3];
    }else{
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
       //allocate memory for message length
        const char* message =(char*)malloc(sizeof(char) * get_filesize(file)+1);
        message = get_message(file);
        if(message == NULL){
            printf("No message.\n");
            return -1;
        }//error check
        encoded = cipher_with_key(message, key);//run cipher
        printf("Encoded length: %d \n", (int)strlen(encoded));        
        char* temp = "encoded_";
        char* encoded_filename[strlen(temp)+strlen(to_open) +1];
        strcat(encoded_filename, temp);
        strcat(encoded_filename, to_open);
        printf("Filename : %s \n", encoded_filename);
        printf("encoded_filename pointer address: 0x%x\n", &encoded_filename);
        printf("Message: \n %s\n", encoded);
        errno =  0;

        if(encoded_filename == NULL){
            printf("Null filename\n");
        }
        FILE* coded_file = fopen(encoded_filename, "w");

        if(coded_file == NULL){
            printf("NULL FILE\n");
            printf("Error: %d\n",errno);
            return 0;
        }
        fprintf(coded_file, "%s", encoded);
        fclose(coded_file);

        
        
    }  
    else if( 0 == strcmp("r", action) || 0 == strcmp("R", action)){
        file = fopen(to_open , "r" );
        if(file != NULL){
            printf("File opened successfully\n");
        }else{
            printf("failed to open file\n"); 
            return -1;
        }
        char* message =(char*)malloc(sizeof(char) * get_filesize(file)+1);
        message = get_message(file);
        encoded = uncipher(message, key);//run cipher
        printf("Decoded message:\n%s\n", encoded);
        char* temp = "decoded_";
        char* encoded_filename[strlen(temp)+strlen(to_open) +1];
        strcat(encoded_filename, temp);
        strcat(encoded_filename, to_open);
        printf("Filename : %s \n", encoded_filename);
        printf("encoded_filename pointer address: 0x%x\n", &encoded_filename);
        
        printf("\nFilename : %s \n", encoded_filename);
        FILE* coded_file = fopen(encoded_filename, "w");
        printf("Decoded length: %d \n", (int)strlen(encoded));
        fprintf(coded_file, "%s", encoded);
        fclose(coded_file);
    }else{
        printf("Bad arguments given. See usage below for details.\n");
        print_usage();
        return 0;
    }
    return 0;
}

char* cipher_with_key(char* message, char* key){
    printf("\nBeginning Cipher . . .\n \n");
    char* encoded = (char*)malloc(sizeof(strlen(message))+1);
    int k = 0;
    char new_letter;
    for(int i = 0; i < strlen(message); i++){
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
        if(message[i+1]== NULL){
            free(message);
            return encoded;
        }
        k++;
    }
    return NULL;
}

char* uncipher(char* message, char* key){
    printf("\nBeginning Cipher . . .\n \n");
    char* decoded = (char*)malloc(sizeof(strlen(message))+1);
    int k =0;
    char new_letter;

    for(int i = 0; i < strlen(message) ; i++){
        int x;
        if(key[k] == (int)NULL){
            k = k % strlen(key);
        }
        if(message[i] != 10){
            x = ((((int)message[i])-32 + 96) - ((int)key[k])) %  96;
            x = x+64;
            if((int)message[i] >= 32 && (int)message[i] <= 47){
                x = message[i];
            }
        }else{
            x = 10;
        }   
        decoded[i]=(char)x;
        k++;    
        if((int)message[i+1] == NULL){
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
    FILE* temp = file;
    char* message =(char*)malloc(sizeof(char) * get_filesize(file)+1);
    rewind(file);
    while(fscanf(file, "%c", (&message[i])) !=EOF ){ // removing the '&' seg faults
        //printf("%c\n", message[i]);
        //fscanf(file, "%c", (&message[i])
        i++;
    }
    return message;
}

int get_filesize(FILE* file){
    int filelen;
    while(fgetc(file)!= EOF){
        filelen ++;
    }
    return filelen;
}
