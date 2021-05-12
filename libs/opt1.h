#ifndef OPT1_H_INCLUDED
#define OPT1_H_INCLUDED

#define LLI long long int
#define ULLI unsigned long long int


void GeneratingKeys(LLI e, LLI n, LLI phi_euler);
/*
It generating the private key and public key.
*/


int RulesKeysGenerating();
/*
It generating keys with help of function before applying
anyones rules in process.
*/


#endif //OPT1_H_INCLUDED