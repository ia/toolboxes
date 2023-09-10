
#include "ssl_evp_aes.h"

#define DEBUG 1

int ssl_evp_aes_encrypt_buffer(char *plaintext, char *password, int flags)
{
	int i;
	int nrounds;
	int password_len;
	int plaintext_len;
	int ciphertext_len;
	int final_len;
	unsigned char *ciphertext;
	unsigned char iv[EVP_MAX_IV_LENGTH];
	unsigned char key[EVP_MAX_KEY_LENGTH];
	EVP_CIPHER_CTX ctx;
	
	nrounds = 1;
	password_len = strlen(password);
	plaintext_len = strlen(plaintext) + 1;
	ciphertext_len = plaintext_len + AES_BLOCK_SIZE;
	final_len = 0;
	
	ciphertext = malloc(ciphertext_len);
	
	EVP_BytesToKey(EVP_aes_256_cbc(), EVP_md5(), NULL, (unsigned char *) password, password_len, nrounds, key, iv);
	EVP_CIPHER_CTX_init(&ctx);
	EVP_EncryptInit_ex(&ctx, EVP_aes_256_cbc(), NULL, key, iv);
	EVP_EncryptUpdate(&ctx, ciphertext, &ciphertext_len, (unsigned char *) plaintext, plaintext_len);
	EVP_EncryptFinal_ex(&ctx, ciphertext + ciphertext_len, &final_len);
	EVP_CIPHER_CTX_cleanup(&ctx);
	
	printf("flags: %d\n", flags);
	printf("cipher text: %s\n", ciphertext);
	printf("cipher hex :");
	for (i = 0; ciphertext[i]; i++) {
		printf(" %.2hhX", ciphertext[i]);
	}
	printf("\n");
	
	FILE *f;
	f = fopen("file.enc", "w");
	fwrite(ciphertext, sizeof(unsigned char), strlen((char *)ciphertext), f);
	fclose(f);
	
	return 0;
}

int ssl_evp_aes_decrypt_buffer(char *password, char *ciphertext, int flags)
{
	printf("%s ->\n", __func__);
	printf("password   : %s\n", password);
	printf("ciphertext : %s\n", ciphertext);
	printf("flags      : %d\n", flags);
	printf("%s <-\n", __func__);
	return 0;
}

