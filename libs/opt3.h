#ifndef OPT3_H_INCLUDED
#define OPT3_H_INCLUDED


#include "opt3.h"
#define LLI long long int


char IntToChar(int letter);
/*
It convert the values of char of the parameter letter to integer
*/


int InputMessage(int message[]);
/*
It get from user the integers values of message encrypeted and return
 the lenght of vector (number of values gets)
*/


int InputKeys(LLI keys[2]);
/*
It get the private keys from user.
It open the private file with the private keys and stock her in vector[2], 
parameter keys[2], if keys in file be equals at keys that the user digited.
It return if 1 if the keys be equals with the keys in file saved or
0 if keys not equals;
*/


void Decrypt();
/*
It run the process of decryptation.
It function open one file and save the message decrypted and printing the
same message after saved this file.
*/


#endif // OPT3_H_INCLUDED