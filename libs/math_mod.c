#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "math_mod.h"
#define DEBUG if(1)
#define ULLI unsigned long long int
#define LLI long long int
#define LEN_VEC 1000


ULLI Module(ULLI b, ULLI mod)
{
    //b is denominator and mod the divisor
    ULLI scrap = b%mod;
    if (scrap > mod) {scrap = scrap % mod;}
    while (scrap < 0)
    {
        scrap += mod;
    }
    return scrap;
}
