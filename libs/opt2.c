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
    if(letter>=65 && letter<=90) letter += 32; //Se for maiscula, deixo minuscula
    if(letter == 32) return 28;
    else return letter-95;
}

void messageToInt(char *message, int intValues[]){
    for(int i=0; i<strlen(message); i++) intValues[i] = charToInt(message[i]);
    //for(int i=0; i<strlen(message); i++) printf("%d ", intValues[i]);
}


void inputMessage(char *message){
    printf("Enter the message to be encrypted:\n");
    scanf("%[^\n]s", message);
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
    
    DEBUG1{printf("Passou!! Chaves: %d %d\n", chave1, chave2);}
    fclose(public);

    printf("Enter the public key pair: ");
    scanf("%lld %lld", &keys[0], &keys[1]);
    if(keys[0] == chave1 && keys[1] == chave2){
        printf("Correct keys, going to encrypt\n");
        return 1;
    } else{
        printf("Incorrect keys, check-up the public file in paste keys directory.\n");
        printf("Going back to menu.\n");
        return 0;
    }
}

void encrypt(){
    FILE *messageCrypt;
    char message[10000];
    LLI messageEncrypt[10000];
    LLI keys[2];
    inputMessage(message);

    int state_input_keys = inputKeys(keys);
    if(state_input_keys == 0){
        printf("."); sleep(1);
        printf("."); sleep(1);
        printf("."); sleep(1);
        return;
    }
    
    printf("."); sleep(1);
    printf("."); sleep(1);
    printf("."); sleep(1);
    int intValues[strlen(message)];
    messageToInt(message, intValues);
    
    // printf("key0: %lld, key1: %lld\n", keys[0], keys[1]);
    messageCrypt = fopen("messageCrypt.txt", "w");
    for(int i=0; i<strlen(message); i++){
        // DEBUG1{printf("int value: %d\n", intValues[i]);}
        messageEncrypt[i] = FastExpMod(intValues[i], keys[0], keys[1]);
        fprintf(messageCrypt, "%lld\n", messageEncrypt[i]);
        // DEBUG1{printf("Value encrypted: %lld\n", messageEncrypt[i]);}
    }
    
    fclose(messageCrypt);
}

int main(){
   encrypt();
   return 0;
}