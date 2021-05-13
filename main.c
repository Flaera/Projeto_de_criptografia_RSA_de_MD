#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include "libs/opt1.h"
#include "libs/opt2.h"
#include "libs/opt3.h"
#include "libs/praticace.h"
#include "libs/math_mod.h"
#define DEBUG1 if(1) //to inputs
#define DEBUG2 if(1) //to process and outputs
#define TIME_WAIT 8


void clearAll(){
    system("clear||cls");
}


void ShowResult(char at_user[])
{
    char bars = '#';
    int delta = 15;
    int len = strlen(at_user);
    for (int i=0; i<len+delta; ++i)
    {printf("%c", bars);}

    printf("\n");
    {printf("\t%s\n", at_user);}

    for (int i=0; i<len+delta; ++i)
    {printf("%c", bars);}
    printf("\n");
    return;
}



void menu(){
    int option = 0;

    while(option!=4){
        printf("ALGORITHM RSA\n");
        printf("*------Menu------*\n\n");
        printf("1 - To generate the public and private key.\n");
        printf("2 - To encode.\n");
        printf("3 - To decode.\n");
        printf("4 - To exit\n\n");
        printf("Choice one option: ");
        scanf("%d", &option);
        getchar();
        
        printf("Chosen option: %d. Loading\n", option);
        printf("."); sleep(1);
        printf("."); sleep(1);
        printf("."); sleep(1);
        printf("\n");
        clearAll();

        if(option == 1){
            printf("Choiced option 1.\n");
            RulesKeysGenerating();
            ShowResult("Keys generation terminated");
            printf("Going back to menu.\nLoading");
            printf("."); sleep(1);
            printf("."); sleep(1);
            printf("."); sleep(TIME_WAIT);
            printf("\n");
            clearAll();
        } else if(option == 2){
            encrypt();
            ShowResult("Encryptation terminated");
            printf("Going back to menu.\nLoading");
            printf("."); sleep(1);
            printf("."); sleep(1);
            printf("."); sleep(TIME_WAIT);
            printf("\n");
            clearAll();
        } else if(option == 3){
            Decrypt();
            ShowResult("Decryptation terminated");
            printf("Going back to menu.\nLoading");
            printf("."); sleep(1);
            printf("."); sleep(1);
            printf("."); sleep(TIME_WAIT);
            printf("\n");
            clearAll();
        } else if(option == 4){
            printf("Leaving, bye");
            printf("."); sleep(1);
            printf("."); sleep(1);
            printf("."); sleep(1);
            printf("\n");
            clearAll();
            return;
        }
    }
}

int main(){
    menu();
    return 0;
}
