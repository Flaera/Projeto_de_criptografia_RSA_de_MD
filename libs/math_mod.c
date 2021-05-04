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
        int acc1=0;
        while(vec[acc1]!=-1)
        {
            printf("%d", vec[acc1]);
            acc1 += 1;
        }
        printf("\n");
    }
    return acc;
}


LLI FastExpMod(LLI base_a, LLI power_b, LLI mod_c)
{
    LLI scrap = 1;
    int binary_number[LEN_VEC];
    int len = BinaryConvertion(power_b, binary_number, LEN_VEC);
    
    // LLI powers[len];
    for (int i=len; i>=0; --i)
    {
        if (binary_number[i]==1)
        {
            scrap *= Module(scrap, mod_c);//(Module(pow(2, len-i), mod_c));
            DEBUG{printf("binary_n: %d, index: %d, scrap: %lld\n",
            binary_number[len-i], len-i, scrap);}
        }
        base_a *= base_a;
        // DEBUG{printf("binary: %d, power: %lld, index: %d\n",
        //  binary_number[i], powers[len-i], len-i);}
    }
    // scrap = Module(scrap, mod_c);
    return scrap;
}


int main()
{
    LLI fexpmod;
    fexpmod = FastExpMod(5, 117, 19);
    DEBUG{printf("Fast Exp Mod: %lld\n", fexpmod);}
    return 0;
}
