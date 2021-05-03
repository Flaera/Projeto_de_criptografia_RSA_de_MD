#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "libs/opt1.h"
#include "libs/praticace.h"
#include "libs/math_mod.h"
#define DEBUG1 if(1) //to inputs
#define DEBUG2 if(1) //to process and outputs


void clearAll(){
    system("clear||cls");
}

void menu(){
    int option = 0;

    while(option!=4){
        printf("*------Menu------*\n\n");
        printf("1 - To generate the public and private key.\n");
        printf("2 - To encode.\n");
        printf("3 - To decode.\n");
        printf("4 - To exit\n\n");
        printf("Choice one option: ");
        scanf("%d", &option);
        
        printf("Chosen option: %d", option);
        printf("."); sleep(1);
        printf("."); sleep(1);
        printf("."); sleep(1);
        clearAll();

        if(option == 1){
            printf("Choiced option 1.\n");
            RulesKeysGenerating();
            printf("############################################\n");
            printf("\tKeys generation terminated\n");
            printf("############################################\n");
            printf("Going back to menu");
            printf("."); sleep(1);
            printf("."); sleep(1);
            printf("."); sleep(1);
            clearAll();
        } else if(option == 2){
            clearAll();
        } else if(option == 3){
            clearAll();
        } else if(option == 4){
            printf("Leaving, bye");
            printf("."); sleep(1);
            printf("."); sleep(1);
            printf("."); sleep(1);
            clearAll();
            return;
        }
    }
}

int main(){
    menu();
    return 0;
}
