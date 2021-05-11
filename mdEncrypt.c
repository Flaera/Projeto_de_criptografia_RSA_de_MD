#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<math.h>
#define LLI long long int

int charToInt(char letter){
    if(letter>=65 && letter<=90) letter += 32; //Se for maiscula, deixo minuscula
    if(letter == 32) return 28;
    else return letter-95;
}

void messageToInt(char *message, int intValues[]){
    for(int i=0; i<strlen(message); i++) intValues[i] = charToInt(message[i]);
    for(int i=0; i<strlen(message); i++) printf("%d ", intValues[i]);
}

void inputMessage(char *message){
    printf("Enter the message to be encrypted:\n");
    scanf("%[^\n]s", message);
}

int inputKeys(int keys[2]){
    FILE *public;
    int chave1, chave2;
    public = fopen("public_key.txt", "r");
    fscanf(public, "%d %d", &chave1, &chave2);
    fclose(public);
    
    //printf("Chaves: %d %d\n", chave1, chave2);
    printf("Enter the public key pair: ");
    scanf("%d %d", &keys[0], &keys[1]);
    if(keys[0] == chave1 && keys[1] == chave2){
        printf("Correct keys, going to encrypt\n");
        return 1;
    } else{
        printf("Incorrect keys, going back to menu\n");
        return 0;
    } 
}

LLI expoModRapidaPot2(LLI M, LLI e, LLI n){ 
	//C = M**e mod n
	LLI c;

	//printf("\nM:%ld e:%ld n:%ld\n", M, e, n);
	if (e != 2){
		LLI res = expoModRapidaPot2(M, (e/2), n);
		c = (res * res) % n;
	} else {
		c = (M * M) % n;
	}

	return c;
}

int expoentesBinariosDeInteiro(int n, int res[]){
	int counter = 0;

	for (int i = 0; i < 32; i++){
		if(n){ //n != 0
			if(n%2){ //bit i = 1
				res[counter] = (LLI) pow(2,i);
				counter++;
			}
			n = n/2;
		}
		else{
			break;
		}
	}

	return counter; //retorna quantidade de expoentes
}

//C = M**e mod n
int expoModRapida(int M, int e, int n){
	LLI c = 1;
	int lenExpBinE, expBinE[32]; //expoentes binários de e
	lenExpBinE = expoentesBinariosDeInteiro(e, expBinE);

	for (int i = 0; i < lenExpBinE; i++){
		if(expBinE[i] == 1){
			c *= M;
		} else {
			long res = expoModRapidaPot2(M, expBinE[i], n);
			c *= res;
		}
	}
	c = c % n;

	int resposta = c;
	return resposta;
}

void encrypt(){
    FILE *messageCrypt;
    char message[10000];
    LLI messageEncrypt[10000];
    int keys[2];
    inputMessage(message);

    if(inputKeys(keys) == 0){
        printf("."); sleep(1);
        printf("."); sleep(1);
        printf("."); sleep(1);
        return;
    }

    // printf("."); sleep(1);
    // printf("."); sleep(1);
    // printf("."); sleep(1);
    int intValues[strlen(message)];
    messageToInt(message, intValues);
    printf("\n*---*\n\n");

    messageCrypt = fopen("messageCrypt.txt", "w");
    printf("Chave 0: %d Chave 1: %d\n\n", keys[0], keys[1]);
    for(int i=0; i<strlen(message); i++){
        messageEncrypt[i] = expoModRapida(intValues[i], keys[0], keys[1]);
        printf("Base: %d Expoente: %d Mod: %d\n", intValues[i], keys[0], keys[1]);
        printf("Pos calc %d: %d\n", i, messageEncrypt[i]);

        fprintf(messageCrypt, "%lld\n", messageEncrypt[i]);
        printf("\n");
    }

    fclose(messageCrypt);

    printf("\n*---*\n\n");
    FILE *messageDecrypt;
    messageDecrypt = fopen("private_key.txt", "r");
    messageCrypt = fopen("messageCrypt.txt", "r");
    int keysDecrypt[2];
    int atual;

    fscanf(messageDecrypt, "%d %d", &keysDecrypt[0], &keysDecrypt[1]);
    printf("Chave 0: %d Chave 1: %d\n", keysDecrypt[0], keysDecrypt[1]);
    for(int i=0; i<strlen(message); i++){
        fscanf(messageCrypt, "%d", &atual);
        messageEncrypt[i] = expoModRapida(atual, keysDecrypt[0], keysDecrypt[1]);
        printf("dAtual: %d - Letra %d: %lld\n", atual, i, messageEncrypt[i]);
    }
}

int main(){
   encrypt();
   return 0;
}
