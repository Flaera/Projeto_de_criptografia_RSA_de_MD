#ifndef PRATICACE_H_INCLUDED
#define PRATICACE_H_INCLUDED


// #include <stdio.h>
// #include "praticace.h"
#define ULLI unsigned long long int
#define LLI long long int


int IsPrimo (LLI number);
/*Checking if number parameter is prim or no. Therefore, return 1 or 0*/


void FatorarPrimos ( LLI number, int vec[] );
/*
Stock all factors prims ("primos em português") of the number parameter in the
 vector of second paramenter.
The final factor in vector is always -1 like \0 in strings (Marking the
 end of array)
*/


LLI NextPrimo ( LLI number );
/*
It search the next primo after number parameter.
*/


void InitVecOnes2 ( int len , LLI array [][2]);
/*
It make all values in one array 2D (array[][2]) equals at one(1).
It's currently used after of declaration of anyone array.
*/


LLI TheGreater ( LLI x , LLI y );
/*
It choice into the two parameters (x, y) than more and return It.
If tie, return x.
*/


LLI TheLower ( LLI x , LLI y );
/*
It choice into the two parameters (x, y) than less and return It.
If tie, return x.
*/


int IsAllOne ( int len , LLI array []);
/*
It check if all values in one vector (array[]) have value equal at one.
It return 1 if all values be one, if not reuturn 0.
*/


int RunDividing ( LLI a , LLI b , LLI lenght , LLI factors [][2]);
/*
It only delivery support to factoration function.
It run the successives division of the process of factoration.
Otherwise, It can be used no the function Factoration. Therefore,
to get the values of factors primos.
While It fill the values of factors in array factors in parameter.
*/


void Factoration(LLI a, LLI b, LLI factors[][2], LLI *mmc, LLI *mdc);
/*
It fill one array[][2] with values of factors primos of
factoration of a and b parameters. It too update the parameters in form pointers
with the valus of mmc and mdc, respectively.
It have be used with function of TheGreater to choice the than more value and 
to apply this value in factors[return value from TheGreater][2], the second
lenght of the lines in array is always two(2).
EXAMPLE:
    int mdc = 1;
    int mmc = 1;
    int a = 24;
    int b = 12;
    int len = TheGreater(a, b);
    int factors[len][2];
    Factoration(a, b, factors, &mmc, &mdc);
    printf("MDC: %d\n", mdc);
    printf("MMC: %d\n", mmc);
    for ( int i =0; i < len ; ++ i ) {
        printf("Factors a and b: %d, %d.\n", factors [ i ][0] , factors [ i ][1]) ;
        if (factors[i][0]==1 && factors[i][1]==1) {break;}
    }
*/


LLI MDCEuclides ( LLI n1 , LLI n2 );
/*
It return the MDC by the way of algorithim of Euclides.
*/


LLI SupportSearchSTMDC(LLI n, LLI d, LLI coef[]);
/*
It only offer the support at calcule of function SearchSTMDC that search s, t
and return the mdc.
The coeficients was in vector in third parameter, but It no setting the
 signal values of this coeficients.
*/


LLI SearchSTMDC(LLI n, LLI d, LLI coef[]);
/*
It function search s, t by recursion and return the mdc.
The coeficients was in vector in third parameter with the values.
It set the signal values in vector coef[].
It obviosly can be used to get the inverse module.
*/


int CongruSoluctions(LLI a, LLI b, LLI m, LLI coef[], LLI solu[]);
/*
It function calcule and stock the soluctions of one congruencia with values:
a, b and m, like discribe in first three parameters.
The soluctions was stock in vector, solu[] parameter, that always end with -1.
It the values of return can be 0, no soluction, 1, only one soluction
 and than more 1, with multiplies soluctions.
*/


LLI NCongruenciasTCR(int n, LLI bm[][3]);
/*
It return the soluction of system of congruencias by TCR method.
In array[n congruencias][3] of n is the number of congruencias and first colun
 is soluction of congruencia, the second colun is b value  and last
  colun (three colun) is m value.
EXAMPLE:
int main()
{
    // Below have one application of the function NCongruenciasTCR:
    int n = 3;
    LLI array[n][3];
    array[0][1] = 2;
    array[0][2] = 3;
    array[1][1] = 4;
    array[1][2] = 5;
    array[2][1] = 6;
    array[2][2] = 7;
    LLI x0 = NCongruenciasTCR(n, array);
    DEBUG{printf("The soluction of system is %lld.\n", x0);}
    return 0;
}
*/


#endif //PRATICACE_H_INCLUDED