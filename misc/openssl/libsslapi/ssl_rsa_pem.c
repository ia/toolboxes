
#include "ssl_rsa_pem.h"

#define SECFILE "sec.pem"
#define PUBFILE "pub.pem"

#define READPUB   0
#define READSEC   1

#define HELP     'h'
#define KEYGEN   'g'
#define CIPHER   'c'
#define DECIPHER 'd'

void ssl_rsa_pem_keygen(int size)
{
	RSA *key = NULL;
	FILE *fp;
	
	if ((key = RSA_generate_key(size, 3, NULL, NULL)) == NULL) {
		fprintf(stderr, "%s\n", ERR_error_string(ERR_get_error(), NULL));
		exit(EXIT_FAILURE);
	}
	
	if (RSA_check_key(key) < 1) {
		fprintf(stderr, "Error: Problems while generating RSA Key.\nRetry.\n");
		exit(EXIT_FAILURE);
	}
	
	fp = fopen(SECFILE, "w");
	if (PEM_write_RSAPrivateKey(fp, key, NULL, NULL, 0, 0, NULL) == 0) {
		fprintf(stderr,"Error: problems while writing RSA Private Key.\n");
		exit(EXIT_FAILURE);
	}
	fclose(fp);
	
	fp = fopen(PUBFILE, "w");
	if (PEM_write_RSAPublicKey(fp, key) == 0) {
		fprintf(stderr,"Error: problems while writing RSA Public Key.\n");
		exit(EXIT_FAILURE);
	}
	fclose(fp);
	RSA_free(key);
	return;
}

int rsa_encrypt(RSA *key, unsigned char *plain, int len, unsigned char **cipher)
{
	int clen = 0;
	srand(time(NULL));
	if ((clen = RSA_public_encrypt(len, plain, *cipher, key, RSA_PKCS1_PADDING)) == -1) {
		fprintf(stderr, "%s\n", ERR_error_string(ERR_get_error(), NULL));
		exit(EXIT_FAILURE);
	} else {
		return clen;
	}
}

int ssl_rsa_pem_encrypt_buffer(char *plaintext, char *keyfile, int flags)
{
	printf("%s ->\n", __func__);
	printf("plaintext : %s\n", plaintext);
	printf("keyfile   : %s\n", keyfile);
	printf("flags     : %d\n", flags);
	printf("%s <-\n", __func__);
	return 0;
}

int ssl_rsa_pem_decrypt_buffer(char *ciphertext, char *keyfile, int flags)
{
	printf("%s ->\n", __func__);
	printf("ciphertext : %s\n", ciphertext);
	printf("keyfile    : %s\n", keyfile);
	printf("flags      : %d\n", flags);
	printf("%s <-\n", __func__);
	return 0;
}

int ssl_rsa_pem_encrypt_file(char *plainfile, char *keyfile, char *output)
{
	int size = 0, len = 0, ks = 0; //, clen = 0;
	unsigned char *cipher = NULL, *plain = NULL;
	FILE *fpkey = NULL, *fpin = NULL, *fpout = NULL;
	RSA *key = NULL;
	
	if ((fpkey = fopen(keyfile, "r")) == NULL) {
		fprintf(stderr, "Error: Public Key file doesn't exists.\n");
		return -1;
	}
	
	if ((key = PEM_read_RSAPublicKey(fpkey, NULL, NULL, NULL)) == NULL) {
		fprintf(stderr, "Error: problems while reading Public Key.\n");
		return -1;
	}
	fclose(fpkey);
	
	if (!(fpin = fopen(plainfile, "r"))) {
		fprintf(stderr, "Error: Cannot locate input file.\n");
		return -1;
	}
	
	fpout = fopen(output, "w");
	ks = RSA_size(key);
	plain = (unsigned char *) malloc(ks * sizeof(unsigned char));
	cipher = (unsigned char*) malloc(ks * sizeof(unsigned char));
	
	while (!feof(fpin)) {
		memset(plain, '\0', ks + 1);
		memset(cipher, '\0', ks + 1);
		len = fread(plain, 1, ks - 11, fpin);
		/*
		 * size = rsa_encrypt(key, plain, len, &cipher);
		 */
		
		srand(time(NULL));
		if ((size = RSA_public_encrypt(len, plain, cipher, key, RSA_PKCS1_PADDING)) == -1) {
			fprintf(stderr, "%s\n", ERR_error_string(ERR_get_error(), NULL));
			exit(EXIT_FAILURE);
		}
		
		fwrite(cipher, 1, size, fpout);
	}
	
	fclose(fpout);
	fclose(fpin);
	free(cipher);
	free(plain);
	RSA_free(key);
	printf("%s\n", __func__);
	
	return 0;
}

int ssl_rsa_pem_decrypt_file(char *cipherfile, char *keyfile, char *output)
{
	printf("%s ->\n", __func__);
	printf("cipherfile : %s\n", cipherfile);
	printf("keyfile    : %s\n", keyfile);
	printf("output     : %s\n", output);
	
	int size = 0, len = 0, ks = 0; //, clen = 0;
	unsigned char *cipher = NULL, *plain = NULL;
	FILE *fpkey = NULL, *fpin = NULL, *fpout = NULL;
	RSA *key = NULL;
	
	if ((fpkey = fopen(keyfile, "r")) == NULL) {
		fprintf(stderr, "Error: Private Key file doesn't exists.\n");
		return -1;
	}
	
	if ((key = PEM_read_RSAPrivateKey(fpkey, NULL, NULL, NULL)) == NULL) {
		fprintf(stderr, "Error: problems while reading Public Key.\n");
		return -1;
	}
	fclose(fpkey);
	
	if (!(fpin = fopen(cipherfile, "r"))) {
		fprintf(stderr, "Error: Cannot locate input file.\n");
		return -1;
	}
	
	fpout = fopen(output, "w");
	ks = RSA_size(key);
	plain = (unsigned char *) malloc(ks * sizeof(unsigned char));
	cipher = (unsigned char*) malloc(ks * sizeof(unsigned char));
	
	while (!feof(fpin)) {
		memset(plain, '\0', ks);
		memset(cipher, '\0', ks);
		//len = fread(plain, 1, ks - 11, fpin);
		if ((len = fread(cipher, 1, ks, fpin)) == 0) {
			break;
		}
		/*
		 * size = rsa_encrypt(key, plain, len, &cipher);
		 */
		
		srand(time(NULL));
		if ((size = RSA_private_decrypt(len, cipher, plain, key, RSA_PKCS1_PADDING)) == -1) {
			fprintf(stderr, "%s\n", ERR_error_string(ERR_get_error(), NULL));
			exit(EXIT_FAILURE);
		}
		
		fwrite(plain, 1, size, fpout);
	}
	
	fclose(fpout);
	fclose(fpin);
	free(cipher);
	free(plain);
	RSA_free(key);
	
	printf("%s <-\n", __func__);
	return 0;
}

