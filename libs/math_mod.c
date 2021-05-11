#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "math_mod.h"
#define DEBUG if(1)
#define ULLI unsigned long long int
#define LLI long long int
#define LEN_VEC 1000


LLI Module(LLI b, LLI mod)
{
    //b is denominator and mod the divisor
    LLI scrap = b%mod;
    if (scrap > mod) {scrap = scrap % mod;}
    while (scrap < 0)
    {
        scrap += mod;
    }
    return scrap;
}


LLI BinaryConvertion(LLI n, int vec[], int len)
{
    for (int i=0; i<len; ++i) {vec[i]=-1;}
    LLI scrap;
    int acc=0;
    while (n>=2)
    {
        scrap = Module(n, 2);
        n = n / 2;
        vec[acc] = scrap;
        acc += 1;
        // DEBUG{printf("scrap=%lld, n=%lld\n", scrap, n);}
    }
    vec[acc] = n;
    DEBUG{
        int acc1=acc;
        while(acc1!=-1)//(vec[acc1]!=-1)
        {
            printf("%d", vec[acc1]);
            acc1 -= 1;
        }
        printf("\n");
    }
    return acc;
}


LLI FastExpMod(LLI base_a, LLI exp_b, LLI mod_c)
{
    int binary_number[LEN_VEC];
    int len = BinaryConvertion(exp_b, binary_number, LEN_VEC);
    
    LLI scrap = 1;
    for (int j=0; j<=len; ++j)
    {
        if (binary_number[j]==1)
        {
            scrap = scrap*Module(base_a, mod_c);
        }
        base_a = base_a * Module(base_a, mod_c);
    }
    
    return Module(scrap, mod_c);
}


// int main()
// {
//     LLI fexpmod;
//     fexpmod = FastExpMod(64, 7, 187); //devolve 1
//     DEBUG{printf("Fast Exp Mod: %lld\n", fexpmod);}
//     return 0;
// }
