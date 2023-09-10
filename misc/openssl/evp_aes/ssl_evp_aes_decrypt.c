#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/evp.h>
#include <openssl/aes.h>
#include <openssl/rand.h>

int usage(void)
{
	printf("Usage: msg password\n");
	return -1;
}

int main(int argc, const char *argv[])
{
	if (argc != 3) {
		return usage();
	}
	
	unsigned char ciphertext[1024];
	int c;
	for (c = 0; c < sizeof(ciphertext); c++) {
		ciphertext[c] = '\0';
	}
	
	FILE *f;
	f = fopen("file.enc", "r");
	fread(ciphertext, sizeof(unsigned char), sizeof(ciphertext), f);
	fclose(f);
	
	printf("cipher text: %s\n", ciphertext);
	printf("cipher hex :");
	for (c = 0; ciphertext[c]; c++) {
		printf(" %.2hhX", ciphertext[c]);
	}
	printf("\n");
	
	unsigned int salt[] = {1, 2, 3};
	unsigned char *password;
	int password_len;
	
	password = (unsigned char *)argv[2];
	password_len = strlen(argv[2]);
	
	int i, nrounds = 5;
	unsigned char key[EVP_MAX_KEY_LENGTH], iv[EVP_MAX_IV_LENGTH];
	//unsigned char key[32], iv[32];
	
	i = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), NULL, password, password_len, nrounds, key, iv);
	//i = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), (unsigned char *)&salt, password, password_len, nrounds, key, iv);
	if (i != 32) {
		printf("Key size is %d bits - should be 256 bits\n", i);
		return -1;
	}
	
	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);
	EVP_DecryptInit_ex(&ctx, EVP_aes_256_cbc(), NULL, key, iv);
	
	int plaintext_len = sizeof(ciphertext);
	
	int p_len = plaintext_len, f_len = 0;
	unsigned char *plaintext = malloc(p_len);
	
	EVP_DecryptInit_ex(&ctx, NULL, NULL, NULL, NULL);
	EVP_DecryptUpdate(&ctx, plaintext, &p_len, ciphertext, plaintext_len);
	EVP_DecryptFinal_ex(&ctx, plaintext+p_len, &f_len);
	
	plaintext_len = p_len + f_len;
	
	EVP_CIPHER_CTX_cleanup(&ctx);
	
	printf("plain text : %s\n", plaintext);
	
	return 0;
}
