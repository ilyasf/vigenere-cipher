#ifndef DECODING_H
#define DECODING_H

// decryption modular approach
char *vigenereDecryptModular(const char *cipherText, const char *key);
// decryption bitwise approach
char *vigenereDecryptBitwise(const char *cipherText, const char *key);

#endif /* DECODING_H */