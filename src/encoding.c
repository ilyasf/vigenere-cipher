#include <string.h>
#include <ctype.h>
#include <stdlib.h>

char *vigenereEncrypt(const char plaintext[], const char keyword[])
{
  int i, j;
  int plaintextLength = strlen(plaintext);
  int keywordLength = strlen(keyword);

  char *ciphertext = (char *)malloc((plaintextLength + 1) * sizeof(char)); // Allocate memory for ciphertext

  for (i = 0, j = 0; i < plaintextLength; i++, j++)
  {
    if (j == keywordLength)
      j = 0;

    // Convert plaintext and keyword characters to uppercase
    char plainChar = toupper(plaintext[i]);
    char keyChar = toupper(keyword[j]);

    // Encrypt alphabetic characters only
    if (isalpha(plainChar))
    {
      int encryptedChar = (plainChar + keyChar - 2 * 'A') % 26 + 'A';
      ciphertext[i] = encryptedChar;
    }
    else
    {
      ciphertext[i] = plainChar; // Preserve non-alphabetic characters
      j--;                       // Do not increment j for non-alphabetic characters
    }
  }
  ciphertext[plaintextLength] = '\0'; // Null-terminate the ciphertext string

  return ciphertext;
}
