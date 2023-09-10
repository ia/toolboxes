
#include <string.h>

#include <openssl/sha.h>
#include <openssl/hmac.h>
#include <openssl/evp.h>
#include <openssl/bio.h>
#include <openssl/buffer.h>

char *unbase64(unsigned char *input, int length);

int main(int argc, char **argv)
{
	char *input = strcat(strcat(argv[1], "\n"), "\0");
	char *output = unbase64((unsigned char *)input, strlen(input));
	printf("Unbase64: %s", output);
	free(output);
	
	return 0;
}

char *unbase64(unsigned char *input, int length)
{
	printf("input : %s", input);
	BIO *b64, *bmem;
	
	char *buffer = (char *)malloc(length);
	memset(buffer, 0, length);
	
	b64 = BIO_new(BIO_f_base64());
	bmem = BIO_new_mem_buf(input, length);
	bmem = BIO_push(b64, bmem);
	
	BIO_read(bmem, buffer, length);
	
	BIO_free_all(bmem);
	
	return buffer;
}
