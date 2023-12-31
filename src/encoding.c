#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdio.h>

char *vigenereEncryptModular(const char plainText[], const char keyword[])
{
  int i, j;
  int plainTextLength = strlen(plainText);
  int keywordLength = strlen(keyword);

  char *cipherText = (char *)malloc((plainTextLength + 1) * sizeof(char)); // Allocate memory for cipherText
  if (cipherText == NULL)
  {
    fprintf(stderr, "Memory allocation failed.\n");
    return NULL;
  }

  for (i = 0, j = 0; i < plainTextLength; i++, j++)
  {
    if (j == keywordLength)
      j = 0;

    // Convert plainText and keyword characters to uppercase
    char plainChar = toupper(plainText[i]);
    char keyChar = toupper(keyword[j]);

    // Encrypt alphabetic characters only
    if (isalpha(plainChar))
    {
      int encryptedChar = (plainChar + keyChar - 2 * 'A') % 26 + 'A';
      cipherText[i] = encryptedChar;
    }
    else
    {
      cipherText[i] = plainChar; // Preserve non-alphabetic characters
      j--;                       // Do not increment j for non-alphabetic characters
    }
  }
  cipherText[plainTextLength] = '\0'; // Null-terminate the cipherText string

  return cipherText;
}

char *vigenereEncryptBitwise(const char plainText[], const char keyword[])
{
  int plainTextLength = strlen(plainText);
  int keywordLength = strlen(keyword);

  char *cipherText = (char *)malloc((plainTextLength + 1) * sizeof(char));
  if (cipherText == NULL)
  {
    fprintf(stderr, "Memory allocation failed.\n");
    return NULL;
  }

  for (int i = 0, j = 0; i < plainTextLength; i++, j++)
  {
    if (j == keywordLength)
      j = 0;

    char plainChar = plainText[i];
    char keyChar = keyword[j];

    if (isalpha(plainChar))
    {
      // Convert both characters to uppercase
      plainChar = toupper(plainChar);
      keyChar = toupper(keyChar);

      // Apply XOR bitwise operation with 'A' to normalize the range
      char encryptedChar = ((plainChar - 'A') ^ (keyChar - 'A')) + 'A';

      cipherText[i] = encryptedChar;
    }
    else
    {
      cipherText[i] = plainChar;
      j--;
    }
  }
  cipherText[plainTextLength] = '\0';

  return cipherText;
}