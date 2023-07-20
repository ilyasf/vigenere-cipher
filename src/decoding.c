#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

char *vigenereDecryptModular(const char *cipherText, const char *key)
{
  int cipherTextLength = strlen(cipherText);
  int keyLength = strlen(key);

  char *plaintext = (char *)malloc((cipherTextLength + 1) * sizeof(char));
  if (plaintext == NULL)
  {
    fprintf(stderr, "Memory allocation failed.\n");
    return NULL;
  }

  for (int i = 0; i < cipherTextLength; i++)
  {
    char cipherChar = cipherText[i];
    char keyChar = key[i % keyLength];

    if (isalpha(cipherChar))
    {
      cipherChar = toupper(cipherChar);
      keyChar = toupper(keyChar);

      char decryptedChar = ((cipherChar - 'A') - (keyChar - 'A') + 26) % 26 + 'A';
      plaintext[i] = decryptedChar;
    }
    else
    {
      plaintext[i] = cipherChar;
    }
  }

  plaintext[cipherTextLength] = '\0';

  return plaintext;
}

char *vigenereDecryptBitwise(const char *cipherText, const char *key)
{
  int cipherTextLength = strlen(cipherText);
  int keyLength = strlen(key);

  char *plaintext = (char *)malloc((cipherTextLength + 1) * sizeof(char));
  if (plaintext == NULL)
  {
    fprintf(stderr, "Memory allocation failed.\n");
    return NULL;
  }

  for (int i = 0; i < cipherTextLength; i++)
  {
    char cipherChar = cipherText[i];
    char keyChar = key[i % keyLength];

    // Perform the XOR decryption
    char decryptedChar = (cipherChar - keyChar + 26) % 26 + 'A';

    plaintext[i] = decryptedChar;
  }

  plaintext[cipherTextLength] = '\0';

  return plaintext;
}