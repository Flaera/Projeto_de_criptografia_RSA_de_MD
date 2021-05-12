#ifndef OPT2_H_INCLUDED
#define OPT2_H_INCLUDED


#define LLI long long int


int charToInt(char letter);
/*
Convert the value of one char to corresponse
 in integer;
*/


void messageToInt(char *message, int intValues[]);
/*
Convert all message string for values integers and
copy it to inValues parameter (type int vec[])
*/


void inputMessage(char *message);
/*
Only get from user the message at be encrypted and stock it in string message
*/


int inputKeys(LLI keys[2]);
/*
it get the keys from user and stock the keys in one vector[2].
It too check if keys be equals with the keys generates in step before.
*/


void encrypt();
/*
It run step of encryptation.
It save one archive with the message encrypted and printing message encrypted
 in console/terminal after to end all process.
*/


#endif // OPT2_H_INCLUDED