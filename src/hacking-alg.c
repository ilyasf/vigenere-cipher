#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

/* first try to get length of the key
  let p[i] (0<=i<=255 byte xOR key length max could be 255.) be the frequency of
  bite i in plaintext (English text)(it's adaptable to other languahes only need to have frequency table for the lng)
    - I.e., p[i] = 0 for i < 32 or i>127 (not english ascll)
    - I.e., p[97] = frequency of 'a'
    - The distribution is far from uniform

  if the key length is N, then every Nth character of the plaintext is encrypted using the same 'shift'
    - if we take every Nth character and calcualte frequencies, we should get p[i]'s in permuted order.
    - if we take every Mth character (M not a multiple of N) and calculate fequencies, we should get something close to uniform.

  * Determining key length:
  for some candidate distribution then we can calculate -> q[0], ..., q[255] => sum(q[i] * q[i]), where q[i] observe frequency of bite i in
  selection of cyph attach character
    - if close to uniform sum(q[i] * q[i]) ~ 256 * ((1 / 256) * (1 / 256)) = 1 / 256
    - if a permuatation of p[i], then sum(q[i] * q[i]) ~ sum(p[i] * p[i])
        + could compute sum(p[i] * p[i]) (but somewhat difficult)
        + key point here it will be much larger than 1/256

  try all possibilities for the key length, compute sum(q[i] * q[i]) and look for maximum value.

  * Determining the Ith byte of the key (assume we found previously key length N)
  look at every Nth character of the cipherText, starting with the Ith character
    - call the Ith cipherText stream (each character from the given encoded text, if we shift accordingly to N it have to be encoded by using same char from key,
    like if we are taking N = 3, and starting from char 1 -> then first 4th, 4th etc have to be encoded by using same key[0]), so we will call them ith stream.

  when guess B  is correct:
    -- all bites in the plaintext stream will be between 32 and 127 (eng ascll chars)
    -- frequency of lowercase letters should be close to frequency table
      + tabulate q[a],.., q[z]
      + should find sum(q[i] * p[i]) ~ sum(p[i] * p[i]) ~ 0.065
      + in practice, take B that maximizes this value

  Complexity: determining key length ~256 * L (L -> max possible key length), determining all bytes of the key 256 * 256 * L, so taht means O(n) - linear!!!
  Note: brute force for same is 256^n!

  for short plain text it's not working very accurate (frequency table will be not so close, so better for small text to get several outcomes and have look or use dictionary to check)
*/

#define ASCII_RANGE 128
#define MIN_PRINTABLE 32
#define MAX_PRINTABLE 127

void calculateCharacterFrequencies(const char *text, int textLength, int stepSize, double *frequencies)
{
  for (int i = 0; i < textLength; i += stepSize)
  {
    char ch = text[i];
    if (ch >= MIN_PRINTABLE && ch <= MAX_PRINTABLE)
      frequencies[ch]++;
  }
}

int findKeyLength(const char *cipherText, int cipherTextLength, int minKeyLength, int maxKeyLength)
{
  double maxSumSquared = 0;
  int bestKeyLength = -1;

  for (int keyLength = minKeyLength; keyLength <= maxKeyLength; keyLength++)
  {
    double *frequencies = (double *)calloc(ASCII_RANGE, sizeof(double));
    if (frequencies == NULL)
    {
      fprintf(stderr, "Memory allocation failed.\n");
      return -1;
    }

    calculateCharacterFrequencies(cipherText, cipherTextLength, keyLength, frequencies);

    double sumSquared = 0;
    for (int i = MIN_PRINTABLE; i <= MAX_PRINTABLE; i++)
      sumSquared += frequencies[i] * frequencies[i];

    if (sumSquared > maxSumSquared)
    {
      maxSumSquared = sumSquared;
      bestKeyLength = keyLength;
    }

    free(frequencies);
  }

  return bestKeyLength;
}

void guessKey(const char *cipherText, int cipherTextLength, int keyLength, char *key)
{
  for (int i = 0; i < keyLength; i++)
  {
    double maxSumSquared = 0;
    char bestGuess = '\0';

    for (char guess = MIN_PRINTABLE; guess <= MAX_PRINTABLE; guess++)
    {
      double *frequencies = (double *)calloc(ASCII_RANGE, sizeof(double));
      if (frequencies == NULL)
      {
        fprintf(stderr, "Memory allocation failed.\n");
        return;
      }

      calculateCharacterFrequencies(cipherText + i, cipherTextLength - i, keyLength, frequencies);

      double sumSquared = 0;
      for (int j = MIN_PRINTABLE; j <= MAX_PRINTABLE; j++)
        sumSquared += frequencies[j] * frequencies[j];

      if (sumSquared > maxSumSquared)
      {
        maxSumSquared = sumSquared;
        bestGuess = guess;
      }

      free(frequencies);
    }

    key[i] = bestGuess;
  }
}

char *hackVigenereEncrypt(const char cipherText[], const int maxKeyLength, const int minKeyLength)
{
  int cipherTextLength = strlen(cipherText);

  int keyLength = findKeyLength(cipherText, cipherTextLength, minKeyLength, maxKeyLength);

  if (keyLength > 0)
  {
    char *key = (char *)malloc((keyLength + 1) * sizeof(char));
    if (key == NULL)
    {
      fprintf(stderr, "Memory allocation failed.\n");
      return NULL;
    }

    key[keyLength] = '\0';
    guessKey(cipherText, cipherTextLength, keyLength, key);

    return key;
  }
  else
  {
    printf("Failed to determine the key length.\n");
  }

  return NULL;
}