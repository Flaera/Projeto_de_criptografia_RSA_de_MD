#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>

#define ULLI unsigned long long int
#define LLI long long int

void clearAll(){ system("clear||cls"); }

int IsPrimo(LLI number) {
  if (number < 0) number *= -1;
  int end = sqrt(number);
  if ((number < 2)) return 0;
  for (int i = 2; i <= end; ++i) {
    if (number % i == 0) return 0;
  }
  return 1;
}

void FatorarPrimos(LLI number, int vec[]) {
  int acc = 0;
  for (LLI i = 2; i <= number; i++) {
    if (i != 2 && i % 2 == 0) continue;
    if (number == 1) return;

    if (number % i == 0) {
      if (IsPrimo(i)) {
        number = number / i;
        vec[acc] = i;
        acc += 1;
        i = 1;
      }
    }
  }
  vec[acc] = -1;
  return;
}

LLI NextPrimo(LLI number) {
  if (IsPrimo(number + 1) == 1) return number + 1;
  else return NextPrimo(number + 1);
  return 0;
}

void InitVecOnes2(int len, LLI array[][2]) {
  for (int i = 0; i < len; ++i) {
    array[i][0] = 1;
    array[i][1] = 1;
  }
  return;
}

LLI TheGreater(LLI x, LLI y) {
  if (x > y) return x;
  else if (x < y) return y;
  else return x;
}

LLI TheLower(LLI x, LLI y) {
  if (x > y) return y;
  else if (x < y) return x;  
  else return x;
}

int IsAllOne(int len, LLI array[]) {
  for (int i = 0; i < len; ++i) {
    if (array[i] != 1) return 0;
  }
  return 1;
}

int RunDividing(LLI a, LLI b, LLI lenght, LLI factors[][2]) {
  int divisor = 2;
  int have_div = 0;
  int ia = 0;
  int ib = 0;
  while (a != 1 || b != 1) {
    if (a % divisor == 0) {
      factors[ia][0] *= divisor;
      a /= divisor;
      have_div = 1;
      ia += 1;
    }
    if (b % divisor == 0) {
      factors[ib][1] *= divisor;
      b /= divisor;
      have_div = 1;
      ib += 1;
    }
    if (have_div == 0) {
      ia += 1;
      ib += 1;
      divisor = NextPrimo(divisor);
    }
    have_div = 0;
  }
  return 0;
}

void Factoration(LLI a, LLI b, LLI factors[][2], LLI * mmc, LLI * mdc) {
  int len = TheGreater(a, b);
  InitVecOnes2(len, factors);

  RunDividing(a, b, len, factors);
  * mmc = * mdc = 1;
  for (int i = 0; i < len; ++i) {
    * mmc *= TheGreater(factors[i][0], factors[i][1]);
    * mdc *= TheLower(factors[i][0], factors[i][1]);
  }
  return;
}

LLI MDCEuclides(LLI n1, LLI n2) {
  if (n1 % n2 == 0) return n2;
  else return MDCEuclides(n2, n1 % n2);
}

LLI SupportSearchSTMDC(LLI n, LLI d, LLI coef[]) {
  LLI mdc, q;
  if (d == 0) return n;
  coef[0] = 0;
  coef[1] = 1;
  if (n % d != 0) q = n / d;
  else q = 1;
  
  mdc = SupportSearchSTMDC(d, n % d, coef);
  if (n % d != 0) {
    LLI old = coef[1];
    coef[1] = (coef[1] * q) + coef[0];
    coef[0] = old;
  }
  return mdc;
}

LLI SearchSTMDC(LLI n, LLI d, LLI coef[]) {
  LLI mdc;
  mdc = SupportSearchSTMDC(n, d, coef);
  if ((-1 * coef[0] * n) + (coef[1] * d) == mdc) {
    coef[0] = coef[0] * -1;
  } else if ((coef[0] * n) - (coef[1] * d) == mdc) {
    coef[1] = coef[1] * -1;
  }

  return mdc;
}

int CongruSoluctions(LLI a, LLI b, LLI m, LLI coef[], LLI solu[]) {
  for (int j = 0; j < 10000; ++j) {
    solu[j] = -1;
  }
  LLI mdc = MDCEuclides(a, m);

  if (mdc == 1) {
    SearchSTMDC(a, m, coef);
    LLI x = coef[0] * b;

    while (x < 0) x += m;
    if (x > m) x = x % m;
    solu[0] = x;
    return 1;
  } else if ((mdc > 1) && (b % mdc == 0)) {
    LLI a1, m1, mdc1, b1;
    LLI coef2[2];

    a1 = a / mdc;
    b1 = b / mdc;
    m1 = m / mdc;
    mdc1 = SearchSTMDC(a1, m1, coef2);

    LLI x = b1 * coef2[0];
    while (x < 0) x = x + m1;
    if (x > m) x = x % m;

    for (int i = 0; i < mdc; ++i) {
      solu[i] = x + (m1 * i);
    }
    return mdc;
  } else return 0;
  return -3;
}

LLI NCongruenciasTCR(int n, LLI bm[][3]) {
  LLI great_m = 1;
  LLI x0 = 0;
  for (int i = 0; i < n; ++i) {
    great_m *= bm[i][2];
  }

  LLI greats_mn[n];
  for (int j = 0; j < n; ++j) {
    greats_mn[j] = great_m / bm[j][2];
  }

  for (int k = 0; k < n; k = k + 1) {
    LLI soluctions[10000];
    LLI coef[2];

    CongruSoluctions(greats_mn[k], 1, bm[k][2], coef, soluctions);
    x0 += (greats_mn[k] * soluctions[0] * bm[k][1]);
  }

  while (x0 < 0) {
    x0 += great_m;
  }
  if (x0 > great_m) {
    x0 = x0 % great_m;
  }

  return x0;
}

LLI Module(LLI b, LLI mod) {
  LLI scrap = b % mod;
  if (scrap > mod) {
    scrap = scrap % mod;
  }
  while (scrap < 0) {
    scrap += mod;
  }
  return scrap;
}

void ShowResult(char at_user[]) {
  char bars = '#';
  int delta = 15;
  int len = strlen(at_user);
  for (int i = 0; i < len + delta; ++i) {
    printf("%c", bars);
  }

  printf("\n"); {
    printf("\t%s\n", at_user);
  }

  for (int i = 0; i < len + delta; ++i) {
    printf("%c", bars);
  }
  printf("\n");
  return;
}

void GeneratingKeys(LLI e, LLI n, LLI phi_euler) {
  FILE * file_public;
  file_public = fopen("public_key.txt", "w");
  fprintf(file_public, "%llu\n%llu", e, n);
  int is_close_fpublic = fclose(file_public);

  printf("\n");
  printf("Public key: ");
  printf("e = %llu, n = %llu;\n", e, n);
  LLI d;
  LLI coefs[2];
  LLI soluctions[10000];
  LLI type_congru = CongruSoluctions(e, 1, phi_euler, coefs, soluctions);
  d = soluctions[0];
  FILE * file_private;
  file_private = fopen("private_key.txt", "w");
  fprintf(file_public, "%llu\n%llu", d, n);
  int is_close_fprivate = fclose(file_private);
  printf("Files saved: private_key.txt, public_key.txt\n\n");
  return;
}

int RulesKeysGenerating() {
  LLI p, q, e;
  LLI n, phi_euler;

  printf("It being:\np and q (cousins to each other)\n");
  printf("e (exponent cousin with (p-1)*(q-1))\n");
  printf("\nDigit into spaces p, q and e:\n");
  scanf("%lld %lld %lld", & p, & q, & e);
  getchar();
  phi_euler = (p - 1) * (q - 1);
  if (IsPrimo(p) != 1 && IsPrimo(q) != 1) {
    printf("Error: p and q not primes.\n");
    return -1;
  } else if (MDCEuclides(e, phi_euler) != 1) {
    printf("Error: expoent not prime with (p-1)*(q-1).\n");
    return -1;
  } else {
    //printf("p=%llu;\n", p);
    //printf("q=%llu;\n", q);
    n = p * q;

    GeneratingKeys(e, n, phi_euler);
    return 1;
  }

  return 0;
}

int charToInt(char letter) {
  if (letter == 32) return 28;
  if (letter >= 97 && letter <= 122) letter -= 95;
  else if (letter >= 65 && letter <= 90) letter -= 63;
  return letter;
}

void messageToInt(char * message, LLI intValues[]) {
  for (int i = 0; i < strlen(message); i++){
    intValues[i] = charToInt(message[i]);
  }
  printf("\n");
}

void inputMessage(char * message) {
  printf("Enter the message to be encrypted:\n");
  scanf("%[^\n]s", message);
  getchar();
}

int inputKeys(LLI keys[2]) {
  int chave1, chave2;
  FILE * public;

  public = fopen("public_key.txt", "r");
  fscanf(public, "%d\n%d", & chave1, & chave2);
  fclose(public);

  printf("\nEnter with the public key pair generated before:\n");
  scanf("%lld %lld", & keys[0], & keys[1]);
  getchar();
  if (keys[0] == chave1 && keys[1] == chave2) {
    //printf("Correct keys, going to encrypt.\n");
    return 1;
  } else {
    printf("Incorrect keys, check the public file in paste keys directory.\n");
    printf("Going back to menu.\n");
    return 0;
  }
}

LLI MEA(LLI a, LLI b, LLI c) {
  if (b == 0) return 1;
  else if (b % 2 == 0) {
    LLI d = MEA(a, b / 2, c);
    return (d * d) % c;
  } else {
    return ((a % c) * MEA(a, b - 1, c)) % c;
  }
}

void encrypt() {
  FILE * messageCrypt;
  char message[10000];
  int messageEncrypt[10000];
  LLI keys[2];
  inputMessage(message);

  int state_input_keys = inputKeys(keys);

  if (state_input_keys == 0) return;

  LLI intValues[strlen(message)];
  messageToInt(message, intValues);

  messageCrypt = fopen("messageCrypt.txt", "w");
  int len_str = strlen(message);
  for (int i = 0; i < len_str; i++){
    LLI fast_exp_return = MEA(intValues[i], keys[0], keys[1]);
    messageEncrypt[i] = fast_exp_return;
    fprintf(messageCrypt, "%d ", messageEncrypt[i]);
  }
  int status_encrypt = fclose(messageCrypt);
  //printf("File saved: messageCrypt.txt: file_closed: %d.\n", status_encrypt);
  printf("\nFile saved: messageCrypt.txt\n");

  printf("Message encrypted: ");
  int acc = 0;
  while (acc < len_str) {
    printf("%d ", messageEncrypt[acc]);
    acc += 1;
  }
  printf("\n\n");
}

char IntToChar(int letter) {
  if (letter == 28) return (char)32;
  else return (char)(63) + letter;
}

int ReadFileMessage(LLI message[]) {
  FILE * encrypted_file;
  encrypted_file = fopen("messageCrypt.txt", "r");

  int acc = 0;
  int status = 1;
  while (status != EOF) {
    status = fscanf(encrypted_file, "%lld", & message[acc]);
    acc = acc + 1;
  }

  printf("Message decrypted: - ");
  for (int i = 0; i < acc - 1; ++i) {
    printf("%lld ", message[i]);
  }
  printf(" - length: %d\n", acc - 1);
  fclose(encrypted_file);
  return acc - 1;
}

int ReadFileKeys(LLI keys[2]) {
  LLI chave1, chave2;
  FILE * private;

  private = fopen("private_key.txt","r");
  if (private == NULL) {
    printf("File not found. Check the private file in keys directory.\n");
    printf("Going back to menu.\n");
  }

  fscanf(private, "%lld\n%lld", & chave1, & chave2);
  keys[0] = chave1;
  keys[1] = chave2;
  fclose(private);

  return 1;
}

void Decrypt() {
  FILE * file_decrypted;
  LLI message_encrypted[10000];
  char message_decrypted[10000];
  LLI keys[2];

  int state_generate_keys = RulesKeysGenerating();
  int state_input_keys = ReadFileKeys(keys);

  if (state_input_keys == 0 || state_generate_keys == -1) return;
  int len = ReadFileMessage(message_encrypted);

  file_decrypted = fopen("messageDecrypt.txt", "w");
  for (int i = 0; i < len; i++) {
    LLI fast_exp_return = MEA(message_encrypted[i], keys[0], keys[1]);
    message_decrypted[i] = (char) IntToChar(fast_exp_return);
    fprintf(file_decrypted, "%c", message_encrypted[i]);
  }
  int status_encrypt = fclose(file_decrypted);
  //printf("Message translated with sucessfully.\n");
  printf("\nFile saved: messageDecrypted.txt\n");
  printf("Message decrypted:\n");
  int acc = 0;
  while (acc < len) {
    printf("%c", message_decrypted[acc]);
    acc += 1;
  }
  printf("\n\n");
}

void menu() {
  int option = 0;
  while (option != 4) {
    
    ShowResult("RSA Menu");
    printf("1 - To generate the public and private key.\n");
    printf("2 - To encode.\n");
    printf("3 - To decode.\n");
    printf("4 - To exit\n\n");
    printf("Choice one option: ");
    scanf("%d", & option);
    getchar();
    clearAll();
    if (option == 1) {
      RulesKeysGenerating();
    } else if (option == 2) {
      encrypt();
    } else if (option == 3) {
      Decrypt();
    } else if (option == 4) {
      printf("Leaving, bye\n");
      return;
    }
  }
}

int main() {
  menu();
  return 0;
}
