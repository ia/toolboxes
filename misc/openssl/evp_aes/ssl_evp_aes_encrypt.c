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
	
	unsigned int salt[] = {1, 2, 3};
	
	/*
	int s;
	unsigned int salt[8];
	unsigned char salt_buffer[8];
	RAND_bytes(salt_buffer, 8);
	printf("salt text: ");
	for (s = 0; s < 8; s++) {
		salt[s] = salt_buffer[s];
		printf("%c", salt[s]);
	}
	printf("\n");
	printf("salt  hex:");
	for (s = 0; s < 8; s++) {
		printf(" %.2hhX", salt[s]);
	}
	printf("\n");
	*/
	
	unsigned char *password;
	int password_len;
	
	password = (unsigned char *)argv[2];
	password_len = strlen(argv[2]);
	
	int i, nrounds = 1;
	//unsigned char key[32], iv[32];
	unsigned char key[EVP_MAX_KEY_LENGTH], iv[EVP_MAX_IV_LENGTH];
	
	i = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), NULL, password, password_len, nrounds, key, iv);
	//i = EVP_BytesToKey(EVP_aes_256_cbc(), EVP_sha1(), (unsigned char *)&salt, password, password_len, nrounds, key, iv);
	if (i != 32) {
		printf("Key size is %d bits - should be 256 bits\n", i);
		return -1;
	}
	
	printf("key :");
	for (i = 0; key[i]; i++) {
		printf(" %.2hhX", key[i]);
	}
	printf("\n");
	
	printf("iv  :");
	for (i = 0; iv[i]; i++) {
		printf(" %.2hhX", iv[i]);
	}
	printf("\n");
	//OPENSSL_cleanse(argv[1],strlen(argv[1]));
	EVP_CIPHER_CTX ctx;
	EVP_CIPHER_CTX_init(&ctx);
	EVP_EncryptInit_ex(&ctx, EVP_aes_256_cbc(), NULL, key, iv);
	
	char *plaintext = argv[1];
	int plaintext_len = strlen(plaintext) + 1;
	
	int c_len = plaintext_len + AES_BLOCK_SIZE, f_len = 0;
	unsigned char *ciphertext = malloc(c_len);
	
	EVP_EncryptInit_ex(&ctx, NULL, NULL, NULL, NULL);
	EVP_EncryptUpdate(&ctx, ciphertext, &c_len, (unsigned char *)plaintext, plaintext_len);
	EVP_EncryptFinal_ex(&ctx, ciphertext+c_len, &f_len);
	
	plaintext_len = c_len + f_len;
	
	printf("cipher text: %s\n", ciphertext);
	printf("cipher hex :");
	for (i = 0; ciphertext[i]; i++) {
		printf(" %.2hhX", ciphertext[i]);
	}
	printf("\n");
	/*
	printf("sizeof(ciphertext) = %d\n", strlen(ciphertext));
	printf("sizeof(unsigned char) = %d\n", sizeof(unsigned char));
	*/
	EVP_CIPHER_CTX_cleanup(&ctx);
	
	FILE *f;
	f = fopen("file.enc", "w");
	fwrite(ciphertext, sizeof(unsigned char), strlen((char *)ciphertext), f);
	fclose(f);
	
	return 0;
}
