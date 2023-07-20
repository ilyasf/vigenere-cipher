#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "./encoding.h"
#include "./hacking-alg.h"
#include "./decoding.h"

int main(void)
{
  char plainText[100];
  char keyword[100];

  printf("Enter the plainText: ");
  fgets(plainText, sizeof(plainText), stdin);
  plainText[strcspn(plainText, "\n")] = '\0'; // Remove trailing newline

  printf("Enter the keyword: ");
  fgets(keyword, sizeof(keyword), stdin);
  keyword[strcspn(keyword, "\n")] = '\0'; // Remove trailing newline

  char *cipherText = vigenereEncryptModular(plainText, keyword);
  printf("Ciphertext (mod): %s\n", cipherText);
  // char *bwCipherText = vigenereEncryptBitwise(plainText, keyword);
  // printf("Ciphertext (btw): %s\n", bwCipherText);

  char *decodedMod = vigenereDecryptModular(cipherText, keyword);
  printf("Decrypted text (mod): %s\n", decodedMod);

  // char *decodedBtw = vigenereDecryptBitwise(bwCipherText, keyword);
  // printf("Decrypted text (btw): %s\n", decodedBtw);

  char *hackedKey = hackVigenereEncrypt(cipherText, 10, 1);
  printf("Original key might be: %s\n", hackedKey);

  free(decodedMod);
  // free(decodedBtw);
  free(cipherText);
  free(hackedKey);
  // free(bwCipherText);

  return 0;
}