
#include <stdio.h>
#include <string.h>

#include <openssl/buffer.h>
#include <openssl/evp.h>
#include <openssl/bio.h>

int ssl_bio_base64_encrypt_buffer(char *plaintext);
int ssl_bio_base64_decrypt_buffer(char *ciphertext);

int ssl_bio_base64_encrypt_file();
int ssl_bio_base64_decrypt_file();

