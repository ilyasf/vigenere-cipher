#ifndef ENCODING_H
#define ENCODING_H

// Function to encrypt the plainText using the Vigenère cipher algorithm modular approach
char *vigenereEncryptModular(const char plainText[], const char keyword[]);
// Function to encrypt the plainText using the Vigenère cipher algorithm bitwise approach
char *vigenereEncryptBitwise(const char plainText[], const char keyword[]);

#endif /* ENCODING_H */