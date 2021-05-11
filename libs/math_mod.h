#ifndef MATH_MOD_H_INCLUDED
#define MATH_MOD_H_INCLUDED


#define LLI long long int


LLI Module(LLI b, LLI mod);
/*
It function return the module, rest or scrap
 of one number in parameter by one module.
*/


LLI BinaryConvertion(LLI n, int vec[], int len);
/*
It fill the vec parameter with numbers (zero or one) of anyone binary.
The paramenter len define the lenght of vector;
The return of this is lenght of binary, the rests spaces in vector was 
markeds with -1;
*/

LLI FastExpMod(LLI base_a, LLI power_b, LLI mod_c);
/*
It make the fast exponeation modular.
It's value of return of this function;
NOTE: It no use litle theorem of fermat.
*/

#endif // MATH_MOD_H_INCLUDED