#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include "opt2.h"
#include "math_mod.h"
#define LLI long long int
#define DEBUG1 if(0)
#define LEN_VEC 1000


int charToInt(char letter){
    if(letter>=97 && letter<=122)
    {
        letter -= 32; //Se for minuscula, deixo maiuscula
    }
    if(letter == 32) {letter = 28;}
    // else {return letter-95;} Old way to [65:91], from greats for lowers
    return letter;
}


void messageToInt(char *message, int intValues[]){
    for(int i=0; i<strlen(message); i++) intValues[i] = charToInt(message[i]);
    //for(int i=0; i<strlen(message); i++) printf("%d ", intValues[i]);
}


void inputMessage(char *message){
    printf("Enter the message to be encrypted:\n");
    scanf("%[^\n]s", message);
    getchar();
    DEBUG1{printf("Message: -%s-\n", message);}
    // scanf("%[^\n]", message);
}


int inputKeys(LLI keys[2]){
    
    int chave1, chave2;
    
    FILE *public;
    // public = freopen("keys/public_key.txt", "r", public);
    public = fopen("/home/flaera/Projeto_de_criptografia_RSA_de_MD/keys/public_key.txt",
     "r"); //depois retirar path completa para adaptar ao windows
    
    fscanf(public, "%d\n%d", &chave1, &chave2);
    
    // DEBUG1{printf("Passou!! Chaves: %d %d\n", chave1, chave2);}
    fclose(public);

    printf("Enter with the public key pair generated before: ");
    scanf("%lld %lld", &keys[0], &keys[1]);
    getchar();
    if(keys[0] == chave1 && keys[1] == chave2){
        printf("Correct keys, going to encrypt\n");
        return 1;
    } else{
        printf("Incorrect keys, check the public file in paste keys directory.\n");
        printf("Going back to menu.\n");
        return 0;
    }
}


void encrypt(){
    FILE *messageCrypt;
    char message[10000];
    int messageEncrypt[10000];
    LLI keys[2];
    inputMessage(message);
    
    int state_input_keys = inputKeys(keys);
    
    if(state_input_keys == 0){
        printf("."); sleep(1);
        printf("."); sleep(1);
        printf("."); sleep(1);
        printf("\n");
        return;
    }
    
    printf("."); sleep(1);
    printf("."); sleep(1);
    printf("."); sleep(1);
    printf("\n");
    int intValues[strlen(message)];
    messageToInt(message, intValues);
    
    DEBUG1{printf("key0: %lld, key1: %lld\n", keys[0], keys[1]);}
    messageCrypt = fopen("messageCrypt.txt", "w");
    int len_str = strlen(message);
    for(int i=0; i<len_str; i++){
        // DEBUG1{printf("int value: %d\n", intValues[i]);}
        int fast_exp_return = FastExpMod(intValues[i], keys[0], keys[1]);
        // DEBUG1{printf("fast exp mod return: %d\n", fast_exp_return);}
        messageEncrypt[i] = fast_exp_return;
        fprintf(messageCrypt, "%d ", messageEncrypt[i]);
        // DEBUG1{printf("Value encrypted: %d\n", messageEncrypt[i]);}
    }
    int status_encrypt = fclose(messageCrypt);
    printf("Message encrypted with sucessfully.\n");
    printf("File saved. messageCrypt.txt: file_closed: %d.\n", status_encrypt);

    //SHOWING THE STRING RESOLUT/ENCRYPTED:
    printf("Message encrypted: ");
    int acc = 0;
    while (acc<len_str)
    {
        printf("%d ", messageEncrypt[acc]);
        acc+=1;
    }
    printf("\n");
    // printf("Going back to main menu. Loading...\n");
}


// int main(){
//    encrypt();
//    return 0;
// }