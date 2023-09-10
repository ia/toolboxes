
#include <stdio.h>
#include <string.h>

#include <openssl/evp.h>
#include <openssl/aes.h>

int ssl_evp_aes_encrypt_buffer(char *plaintext, char *password, int flags);
int ssl_evp_aes_decrypt_buffer(char *ciphertext, char *password, int flags);

int ssl_evp_aes_encrypt_file();
int ssl_evp_aes_decrypt_file();

