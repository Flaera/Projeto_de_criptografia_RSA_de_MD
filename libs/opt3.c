#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include "opt3.h"
#include "math_mod.h"
#define LLI long long int
#define DEBUG1 if(0)
#define LEN_VEC 1000


char IntToChar(int letter){
    if(letter>=97 && letter<=122)
    {
        letter -= 32; //Se for minuscula, deixo maiuscula
    }
    if(letter == 28) {letter = ' ';}
    // else {return letter-95;} Old way to [65:91], from greats for lowers
    return letter;
}


int InputMessage(int message[]){
    printf("Enter the message to be decrypted:\n");
    int acc = 0;
    int n = 1;
    char c = 'a';
    while (c != '\n')
    {
        scanf("%d%c", &n, &c);
        message[acc] = n;
        DEBUG1{printf("acc: %d, n: %d\n", acc, n);}
        acc+=1;
    }
    // getchar(); //get the break line
    DEBUG1{
        printf("Message: ");
        for (int i=0; i<acc;++i)
        {printf("%d ", message[i]);}
        printf("\n");
    }
    return acc;
}


int InputKeys(LLI keys[2]){
    
    int chave1, chave2;
    
    FILE *private;
    // public = freopen("keys/public_key.txt", "r", public);
    private = fopen("/home/flaera/Projeto_de_criptografia_RSA_de_MD/keys/private_key.txt",
     "r"); //depois retirar path completa para adaptar ao windows
    
    fscanf(private, "%d\n%d", &chave1, &chave2);
    
    // DEBUG1{printf("Passou!! Chaves: %d %d\n", chave1, chave2);}
    fclose(private);

    printf("Enter with the private key pair generated before: ");
    scanf("%lld %lld", &keys[0], &keys[1]);
    getchar();
    if(keys[0] == chave1 && keys[1] == chave2){
        printf("Correct keys, going to decrypt\n");
        return 1;
    } else{
        printf("Incorrect keys, check the public file in paste keys directory.\n");
        printf("Going back to menu.\n");
        return 0;
    }
}


void Decrypt(){
    FILE *message_decrypted;
    int message[10000];
    int messageDecrypt[10000];
    LLI keys[2];
    int len = InputMessage(message);
    
    int state_input_keys = InputKeys(keys);
    
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
    
    DEBUG1{printf("key0-d: %lld, key1-n: %lld\n", keys[0], keys[1]);}
    message_decrypted = fopen("messageDecrypt.txt", "w");
    for(int i=0; i<len; i++){
        int fast_exp_return = FastExpMod(message[i], keys[0], keys[1]);
        // DEBUG1{printf("fast exp mod return: %d\n", fast_exp_return);}
        messageDecrypt[i] = IntToChar(fast_exp_return);
        fprintf(message_decrypted, "%c", messageDecrypt[i]);
    }
    int status_encrypt = fclose(message_decrypted);
    printf("Message decrypted with sucessfully.\n");
    printf("File saved. messageDecrypted.txt: file_closed: %d.\n", status_encrypt);

    //SHOWING THE STRING RESULT/DECRYPTED:
    printf("Message decrypted: ");
    int acc = 0;
    while (acc<len)
    {
        printf("%c", messageDecrypt[acc]);
        acc+=1;
    }
    printf("\n");
    // printf("Going back to main menu. Loading...\n");
}


// int main(){
//    Decrypt();
//    return 0;
// }