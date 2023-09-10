
#include "ssl_bio_base64.h"

int ssl_bio_base64_encrypt_buffer(char *plaintext)
{
	int plaintext_len;
	char *ciphertext;
	
	BIO *b64;
	BIO *bmem;
	BUF_MEM *bptr;
	
	plaintext_len = strlen(plaintext);
	
	b64 = BIO_new(BIO_f_base64());
	bmem = BIO_new(BIO_s_mem());
	b64 = BIO_push(b64, bmem);
	BIO_write(b64, (unsigned char *) plaintext, plaintext_len);
	BIO_flush(b64);
	BIO_get_mem_ptr(b64, &bptr);
	
	ciphertext = (char *) malloc(bptr->length);
	memcpy(ciphertext, bptr->data, bptr->length-1);
	ciphertext[bptr->length-1] = 0;
	
	//BIO_free_all(b64);
	BIO_free_all(bmem);
	
	printf("Base64: %s\n", ciphertext);
	
	return 0;
}

int ssl_bio_base64_decrypt_buffer(char *ciphertext)
{
	int ciphertext_len;
	char *plaintext;
	BIO *b64;
	BIO *bmem;
	
	ciphertext_len = strlen(ciphertext);
	plaintext = (char *) malloc(ciphertext_len);
	memset(plaintext, 0, ciphertext_len);
	
	b64 = BIO_new(BIO_f_base64());
	bmem = BIO_new_mem_buf((unsigned char *) ciphertext, ciphertext_len);
	bmem = BIO_push(b64, bmem);
	BIO_read(bmem, plaintext, ciphertext_len);
	
	//BIO_free(b64);
	BIO_free_all(bmem);
	
	printf("Plain : %s\n", plaintext);
	
	return 0;
}
