
#include <stdio.h>

#include <openssl/rsa.h>
#include <openssl/pem.h>
#include <openssl/err.h>

#define SECFILE "sec.pem"
#define PUBFILE "pub.pem"

int main(int argc, char *argv[])
{
	RSA *key;
	FILE *fp;
	int keylen = 0;
	if (argc != 2) {
		fprintf(stderr, "Error: too many/few arguments.\nUsage: %s <numbits>\n", argv[0]);
		return 1;
	}
	
	keylen = atoi(argv[1]);
	if ((key = RSA_generate_key(keylen, 3, NULL, NULL)) == NULL) {
		fprintf(stderr, "%s\n", ERR_error_string(ERR_get_error(), NULL));
		return 1;
	}
	
	if (RSA_check_key(key) < 1)
	{
		fprintf(stderr, "Error: Problems while generating RSA Key.\nRetry.\n");
		return 1;
	}
	
	fp = fopen(SECFILE,"w");
	if (PEM_write_RSAPrivateKey(fp, key, NULL, NULL, 0, 0, NULL) == 0)
	{
		fprintf(stderr, "Error: problems while writing RSA Private Key.\n");
		return 1;
	}
	fclose(fp);
	
	fp = fopen(PUBFILE, "w");
	if (PEM_write_RSAPublicKey(fp, key) == 0) {
		fprintf(stderr, "Error: problems while writing RSA Public Key.\n");
		return 1;
	}
	fclose(fp);
	RSA_free(key);
	printf("RSA key generated.\nLenght (bits) = %d\n", keylen);
	return 0;
}

