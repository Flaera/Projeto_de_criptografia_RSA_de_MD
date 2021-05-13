#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include "praticace.h"
#include "opt1.h"
#include "opt3.h"
#include "math_mod.h"
#define LLI long long int
#define DEBUG1 if(1)
#define LEN_VEC 1000
#define LEN_VEC2 10000


char IntToChar(int letter){
    if(letter>=97 && letter<=122)
    {
        letter -= 32; //Se for minuscula, deixo maiuscula
    }
    if(letter == 28) {letter = ' ';}
    // else {return letter-95;} Old way to [65:91], from greats for lowers
    return letter;
}


int ReadFileMessage(int message[]){
    FILE *encrypted_file;
    
    encrypted_file = fopen("/home/flaera/Projeto_de_criptografia_RSA_de_MD/messageCrypt.txt", "r");
    
    int acc = 0;
    int status = 1;
    while (status!=EOF)
    {
        status = fscanf(encrypted_file, "%d", &message[acc]);
        acc = acc+1;
    }
    
    DEBUG1{
        printf("message reading: -");
        for (int i=0; i<acc-1; ++i)
        {
            printf("%d ", message[i]);
        }
        printf("-\n");
        printf("len : %d\n", acc-1);
    }

    fclose(encrypted_file);
    return acc-1;
}


int ReadFileKeys(LLI keys[2]){
    
    int chave1, chave2;
    
    FILE *private;
    // public = freopen("keys/public_key.txt", "r", public);
    private = fopen("/home/flaera/Projeto_de_criptografia_RSA_de_MD/keys/private_key.txt",
     "r"); //depois retirar path completa para adaptar ao windows
    if (private==NULL)
    {
        printf("File not found. Check the private file in keys directory.\n");
        printf("Going back to menu.\n");
    }

    fscanf(private, "%d\n%d", &chave1, &chave2);
    keys[0] = chave1;
    keys[1] = chave2;
    
    fclose(private);

    return 1;
}


void Decrypt(){
    int message_encrypted[LEN_VEC2];
    FILE *file_decrypted;
    char message_decrypted[LEN_VEC2];
    LLI keys[2];

    int state_generate_keys = RulesKeysGenerating();
    int state_input_keys = ReadFileKeys(keys);
    DEBUG1{printf("key0-d: %lld, key1-n: %lld\n", keys[0], keys[1]);}
    if(state_input_keys == 0 || state_generate_keys == -1){
        printf("."); sleep(1);
        printf("."); sleep(1);
        printf("."); sleep(1);
        printf("\n");
        return;
    }
    
    int len = ReadFileMessage(message_encrypted);
    
    printf("."); sleep(1);
    printf("."); sleep(1);
    printf("."); sleep(1);
    printf("\n");
    
    file_decrypted = fopen("/home/flaera/Projeto_de_criptografia_RSA_de_MD/messageDecrypt.txt", "w");
    for(int i=0; i<len; i++){
        int fast_exp_return = FastExpMod(message_encrypted[i], keys[0], keys[1]);
        DEBUG1{printf("fast exp mod return: %d\n", fast_exp_return);}
        message_decrypted[i] = IntToChar(fast_exp_return);
        fprintf(file_decrypted, "%c", message_encrypted[i]);
    }
    int status_encrypt = fclose(file_decrypted);
    printf("Message decrypted with sucessfully.\n");
    printf("File saved. messageDecrypted.txt: file_closed: %d.\n", status_encrypt);

    //SHOWING THE STRING RESULT/DECRYPTED:
    printf("Message decrypted: ");
    int acc = 0;
    while (acc<len)
    {
        printf("%c", message_decrypted[acc]);
        acc+=1;
    }
    printf("\n");
    // printf("Going back to main menu. Loading...\n");
}


// int main(){
//    Decrypt();
//    return 0;
// }