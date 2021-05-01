#include <stdio.h>
#include <math.h>
#include "libs/opt1.h"
#include "libs/praticace.h"
#include "libs/math_mod.h"
#define DEBUG1 if(1) //to inputs
#define DEBUG2 if(1) //to process and outputs


int main()
{
    printf("Choice one options:\n");
    printf("1 - To generate the public and private key.\n");
    printf("2 - To encode.\n");
    printf("3 - To decode.\n");
    
    int opt;
    scanf("%d", &opt);
    
    if (opt==1)
    {
        printf("Choiced option 1.\n");
        RulesKeysGenerating();
        printf("############################################\n");
        printf("\tKeys generation terminated\n");
        printf("############################################\n");
        return 0; //Make anyone of order with the option of the user.
    }
    else if (opt==2)
    {
        return 0; //Make anyone of order with the option of the user.
    }
    else if (opt==3)
    {
        return 0; //Make anyone of order with the option of the user.
    }

    return opt;
}
