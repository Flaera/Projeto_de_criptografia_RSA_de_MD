#include <stdio.h>
#include <math.h>
#include "praticace.h"
#include "math_mod.h"
#include "opt1.h"
#define DEBUG1 if(0) //to inputs
#define DEBUG2 if(0) //to process and outputs
#define LLI long long int
#define ULLI unsigned long long int
#define LEN_VEC 1000


// Functions/methods
void GeneratingKeys(LLI e, LLI n, LLI phi_euler)
{
    FILE *file_public;
    file_public = fopen("keys/public_key.txt", "w");
    fprintf(file_public, "%llu\n%llu", e, n);
    int is_close_fpublic = fclose(file_public);
    
    printf("\n");
    printf("File saved. public_key.txt: file closed (fclose)=%d\n", is_close_fpublic);
    printf("Public key save:\n");
    printf("\te=%llu\n", e);
    printf("\tn=%llu\n", n);
    /*Generating private key:*/
    LLI d;
    LLI coefs[2];
    LLI soluctions[LEN_VEC];
    LLI type_congru = CongruSoluctions(e, 1, phi_euler, coefs, soluctions);
    DEBUG2{
        // printf("phi_euler=(p-1)*(q-1)=%lld\n", e);
        printf("phi_euler=(p-1)*(q-1)=%lld\n", phi_euler);
        printf("Type congru = %lld\n", type_congru);
    }
    d = soluctions[0];
    DEBUG2{printf("d = %llu.\n", d);}
    FILE *file_private;
    file_private = fopen("keys/private_key.txt", "w");
    fprintf(file_public, "%llu\n%llu", d, n);
    int is_close_fprivate = fclose(file_private);
    // printf("\n");
    printf("File saved. private_key.txt: file closed (fclose)=%d\n", is_close_fprivate);
    DEBUG2{
        printf("Private key save:\n");
        printf("\td=%llu\n", d);
        printf("\tn=%llu\n", n);
    }
    return;
}

/*
MAIN COMENTARY SPACE:
It's script used like base to begin to work anyone 
implementation.
For this, is only need copy and paste the content 
of this script.
*/
int RulesKeysGenerating()
{
    LLI p, q, e;
    LLI n, phi_euler;

    scanf("%lld %lld %lld", &p, &q, &e);
    phi_euler = (p-1)*(q-1);
    if (IsPrimo(p)!=1 && IsPrimo(q)!=1)
    {
        printf("Error: p and q not primes.\n");
        return -1;
    }
    else if (MDCEuclides(e, phi_euler)!=1)
    {
        printf("Error: expoent not prime with (p-1)*(q-1).\n");
        return -1;
    }
    else //generate keys
    {
        DEBUG1{
            printf("p=%llu;\n", p);
            printf("q=%llu;\n", q);
        }
        n = p*q;
        //Saving keys (public and private):
        GeneratingKeys(e, n, phi_euler);
        return 1;
    }

    return 0;
}