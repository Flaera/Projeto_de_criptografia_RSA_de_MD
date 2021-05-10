#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#define LLI long long int

int charToInt(char letter){
    if(letter>=65 && letter<=90) letter += 32; //Se for maiscula, deixo minuscula
    if(letter == 32) return 28;
    else return letter-95;
}

void messageToInt(char *message, int intValues[]){
    for(int i=0; i<strlen(message); i++) intValues[i] = charToInt(message[i]);
    //for(int i=0; i<strlen(message); i++) printf("%d ", intValues[i]);
}

LLI fastExp(LLI base, LLI exp){
    if(exp == 0) return 1;
    if(exp == 1) return base;

    if(exp%2 == 0) return fastExp(base*base, exp/2);
    else return base*fastExp(base*base, (exp-1)/2);
}

void inputMessage(char *message){
    printf("Enter the message to be encrypted:\n");
    scanf("%[^\n]s", message);
}

int inputKeys(int keys[2]){
    FILE *public;
    int chave1, chave2;
    public = fopen("public_key.txt", "r");
    fscanf(public, "%d %d", &chave1, &chave2);
    fclose(public);
    
    //printf("Chaves: %d %d\n", chave1, chave2);
    printf("Enter the public key pair: ");
    scanf("%d %d", &keys[0], &keys[1]);
    if(keys[0] == chave1 && keys[1] == chave2){
        printf("Correct keys, going to encrypt\n");
        return 1;
    } else{
        printf("Incorrect keys, going back to menu\n");
        return 0;
    } 
}

void encrypt(){
    FILE *messageCrypt;
    char message[10000];
    LLI messageEncrypt[10000];
    int keys[2];
    inputMessage(message);

    if(inputKeys(keys) == 0){
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

    messageCrypt = fopen("messageCrypt.txt", "w");
    for(int i=0; i<strlen(message); i++){
        messageEncrypt[i] = fastExp(intValues[i], keys[1]) % keys[0];
        fprintf(messageCrypt, "%lld\n", messageEncrypt[i]);
    }
    
    fclose(messageCrypt);
}

int main(){
   encrypt();
   return 0;
}