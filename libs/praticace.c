#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "praticace.h"
#define DEBUG if(0)
#define ULLI unsigned long long int
#define LLI long long int
#define LEN_VEC 1000


int IsPrimo (LLI number)
{
    if (number<0) {number*=-1;}
    int end = sqrt ( number ) ;
    if (( number < 2) && ( number > -2) ) {return 0;}
    for ( int i =2; i <= end ; ++ i )
    {
        if (number % i ==0) {return 0;}
    }
    return 1;
}


void FatorarPrimos ( LLI number, int vec[] ) {
    int acc = 0;
    for ( LLI i =2; i <= number ; i ++) {
        if ( i !=2 && i %2 == 0) continue ;
        if ( number == 1) return ;
        
        if ( number % i == 0) {
            if ( IsPrimo ( i ) ) {
                number = number / i ;
                // printf ( " % d " , i ) ;
                vec[acc] = i;
                acc+=1;
                i = 1;
            }
        }
    }
    vec[acc] = -1;
    return;
}


LLI NextPrimo ( LLI number ) {
    if ( IsPrimo ( number +1) ==1)
    {return number +1;}
    else {return NextPrimo ( number +1);}
return 0;
}


void InitVecOnes2 ( int len , LLI array [][2]) {
    for ( int i =0; i < len ; ++ i ) {
        array [ i ][0]=1;
        array [ i ][1]=1;
        }
    return ;
}


LLI TheGreater ( LLI x , LLI y ) {
    if (x > y ) { return x ;}
    else if (x < y ) { return y ;}
    return x ;
}


LLI TheLower ( LLI x , LLI y ) {
    if (x > y ) { return y ;}
    else if (x < y ) { return x ;}
    return x ;
}


int IsAllOne ( int len , LLI array []) {
    for ( int i =0; i < len ; ++ i ) {
        if ( array [ i ]!=1) { return 0;}
    }
    return 1;
}


int RunDividing ( LLI a , LLI b , LLI lenght , LLI factors [][2]) {
    int divisor = 2;
    int have_div = 0;
    int ia = 0;
    int ib = 0;
    while ( a !=1 || b !=1) {
        if ( a % divisor ==0) {
            factors [ ia ][0] *= divisor ;
            a /= divisor ;
            have_div = 1;
            ia += 1;
        }
        if ( b % divisor ==0) {
            factors [ ib ][1] *= divisor ;
            b /= divisor ;
            have_div = 1;
            ib += 1;
        }
        if ( have_div ==0) {
            ia += 1;
            ib += 1;
            divisor = NextPrimo ( divisor ) ;
        }
        have_div = 0;
    }
    return 0;
}


void Factoration(LLI a, LLI b, LLI factors[][2], LLI *mmc, LLI *mdc)
{
    int len = TheGreater (a , b);
    InitVecOnes2 ( len , factors );
    
    RunDividing (a , b , len , factors ) ;
    *mmc = *mdc = 1;
    for ( int i =0; i < len ; ++ i ) {
        *mmc *= TheGreater ( factors [ i ][0] , factors [ i ][1]) ;
        *mdc *= TheLower ( factors [ i ][0] , factors [ i ][1]) ;
    }
    return;
}


LLI MDCEuclides ( LLI n1 , LLI n2 ) {
    if ( n1 % n2 == 0) return n2;
    else return MDCEuclides ( n2 , n1 % n2 ) ;
}


LLI SupportSearchSTMDC(LLI n, LLI d, LLI coef[])
{
    LLI mdc , q ;
    if ( d ==0) return n ;
    coef [0] = 0;
    coef [1] = 1;
    if ( n % d !=0) { q = n / d ;}
    else { q =1;}
    mdc = SupportSearchSTMDC(d , n %d , coef );

    if ( n % d !=0) {
        LLI old = coef [1];
        coef [1] = ( coef [1] * q ) + coef [0];
        coef [0] = old ;
    }
    return mdc ;
}


LLI SearchSTMDC(LLI n, LLI d, LLI coef[])
{
    LLI mdc;
    mdc = SupportSearchSTMDC (n , d , coef) ;
    if (( -1* coef [0]* n ) + ( coef [1]* d ) == mdc )
    { coef [0] = coef[0]* -1;}
    else if (( coef [0]* n ) - ( coef [1]* d ) == mdc )
    { coef [1]= coef[1]* -1;}
    // DEBUG{printf("MDC: % d = (% d ) *% d + (% d ) *% d\n", mdc, coef[0], n,
    //  coef[1] , d);}
    return mdc;
}


int CongruSoluctions(LLI a, LLI b, LLI m, LLI coef[], LLI solu[])
{
    // initiliaze the vector of soluctions with negative ones
    for (int j=0; j<LEN_VEC; ++j)
    {solu[j]=-1;}
    LLI mdc = MDCEuclides(a,m);
    // DEBUG{printf("a,m: %d, %d; MDC: %d\n", a, m, mdc);}
    // 35=11*3+2
    // 3=1*2+1
    // 2=2*1+0

    if (mdc == 1)
    {
        SearchSTMDC(a, m, coef);
        DEBUG{printf("MDC: %llu = (%llu)*%llu + (%llu)*%llu\n", mdc, coef[0], a, coef[1], m);}
        DEBUG{printf("coefs: %llu, %llu\n", coef[0], coef[1]);}
        // DEBUG2{printf("a,b,m: %d, %d, %d\n", a, b, m);}
     
        LLI x = coef[0]*b;
        DEBUG{printf("coefs: %llu, %llu\n", coef[0], coef[1]);}
        while (x<0) {x+=m;}
        if (x>m) {x=x%m;}
        solu[0] = x;
        DEBUG{printf("Solucao unica. O conjunto solucao e S={%llu}.\n", x);}

        return 1; //With only one soluction
        DEBUG{printf("AQUI, RIGHT!\n");}
    }
    else if ((mdc > 1) && (b % mdc == 0))
    {
        // printf("A congruencia tem d=%d solucoes.\n", mdc);
        LLI a1, m1, mdc1, b1;
        LLI coef2[2];
        
        a1 = a/mdc;
        b1 = b/mdc;
        m1 = m/mdc;
        DEBUG{printf("a1, m1: %llu, %llu\n", a1, m1);}

        mdc1 = SearchSTMDC(a1, m1, coef2);
        DEBUG{printf("MDC1 search: %llu\n", mdc1);}
        DEBUG{printf("coefs2: %llu, %llu\n", coef2[0], coef2[1]);}

        LLI x = b1 * coef2[0];
        while (x<0) {x=x+m1;} //adjust the x
        if (x>m) {x=x%m;} //adjust the x
        DEBUG{printf("x = %llu\n", x);}

        for (int i=0; i<mdc; ++i)
        {
            solu[i] = x+(m1*i);
        }
        return mdc; // With multiples soluctions
    }
    else
    {
        DEBUG{printf("A congruencia nao tem solucoes.\n");}
        return 0; //NO soluctions!!
    }
    DEBUG{printf("Invalid output!!\n");}
    return -3; //Invalid output
}


LLI NCongruenciasTCR(int n, LLI bm[][3])
{
    LLI great_m = 1;
    LLI x0 = 0;
    for (int i=0; i<n; ++i)
    {
        great_m *= bm[i][2]; //It loop get the M
    }
    DEBUG{printf("M: %lld\n", great_m);}
    LLI greats_mn[n];
    for (int j=0; j<n; ++j)
    {
        greats_mn[j] = great_m/bm[j][2]; //It get the M1, M2, M3,... Mn
        DEBUG{printf("Mi: %lld\n", greats_mn[j]);}
    }
    
    
    for (int k=0; k<n; k=k+1)
    {
        LLI soluctions[LEN_VEC];
        LLI coef[2];
        // DEBUG{printf("1- s=%d\n", soluctions[0]);}
        // DEBUG{printf("k: %d, n: %d\n", k, n);}
        
        CongruSoluctions(greats_mn[k], 1, bm[k][2], coef, soluctions);
        // DEBUG{printf("k: %d, n: %d\n", k, n);}
        // DEBUG{printf("return value CongruSolu: %d\n", l);}
        
        // DEBUG{printf("greats mn: %lld\n", greats_mn[k]);}
        // DEBUG{printf("soluctions[0]: %d\n", soluctions[0]);}
        // DEBUG{printf("bm[k][1]: %lld\n", bm[k][1]);}
        // DEBUG{printf("2- s=%d\n", soluctions[0]);}
        x0 += (greats_mn[k]*soluctions[0]*bm[k][1]);
    }

    while (x0<0) {x0+=great_m;}
    if (x0>great_m) {x0=x0%great_m;}

    return x0;
}


// int main()
// {
//     // Below have one application of the function NCongruenciasTCR:
//     int n = 3;
//     LLI array[n][3];
//     array[0][1] = 2;
//     array[0][2] = 3;
//     array[1][1] = 4;
//     array[1][2] = 5;
//     array[2][1] = 6;
//     array[2][2] = 7;
//     LLI x0 = NCongruenciasTCR(n, array);
//     DEBUG{printf("The soluction of system is %lld.\n", x0);}
//     return 0;
// }