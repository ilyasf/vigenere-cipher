#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "./encoding.h"

int main(void)
{
  char plaintext[100];
  char keyword[100];

  printf("Enter the plaintext: ");
  fgets(plaintext, sizeof(plaintext), stdin);
  plaintext[strcspn(plaintext, "\n")] = '\0'; // Remove trailing newline

  printf("Enter the keyword: ");
  fgets(keyword, sizeof(keyword), stdin);
  keyword[strcspn(keyword, "\n")] = '\0'; // Remove trailing newline

  char *ciphertext = vigenereEncrypt(plaintext, keyword);
  printf("Ciphertext: %s\n", ciphertext);

  free(ciphertext); // Free the allocated memory

  return 0;
}