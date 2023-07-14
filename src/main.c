#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "./encoding.h"
#include "./hacking-alg.h"

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
  char *bwCipherText = vigenereEncryptBitwise(plainText, keyword);
  printf("Ciphertext (bit): %s\n", bwCipherText);

  // char *hackedText = hackVigenereEncrypt(cipherText, 1);
  // printf("Original text might be: %s\n", hackedText);

  free(cipherText);
  // free(hackedText);
  free(bwCipherText);

  return 0;
}