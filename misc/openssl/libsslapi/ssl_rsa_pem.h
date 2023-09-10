
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

void ssl_rsa_pem_keygen(int size);

int ssl_rsa_pem_encrypt_buffer(char *plaintext, char *key, int flags);
int ssl_rsa_pem_decrypt_buffer(char *ciphertext, char *key, int flags);

int ssl_rsa_pem_encrypt_file(char *plainfile, char *key, char *output);
int ssl_rsa_pem_decrypt_file(char *cipherfile, char *key, char *output);

