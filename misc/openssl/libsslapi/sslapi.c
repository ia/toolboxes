
#include "sslapi.h"

#define NAME "sslapi"

int usage(void)
{
	printf("Usage: %s evp_aes|bio_base64|rsa_pem\n", NAME);
	return 0;
}

int main(int argc, const char *argv[])
{
	if (argc != 2) {
		return usage();
	}

	if (!strcmp(argv[1], "evp_aes")) {
		ssl_evp_aes_encrypt_buffer("abc\n", "a", 0);
		char *cipher = "";
		ssl_evp_aes_decrypt_buffer("password", cipher, 0);
	} else if (!strcmp(argv[1], "bio_base64")) {
		ssl_bio_base64_encrypt_buffer("a\n");
		ssl_bio_base64_decrypt_buffer("YQo=\n");
	} else if (!strcmp(argv[1], "rsa_pem")) {
		ssl_rsa_pem_keygen(2048);
		ssl_rsa_pem_encrypt_file("file.txt", "pub.pem", "file.bin");
		ssl_rsa_pem_decrypt_file("file.bin", "sec.pem", "file_.txt");
	}
	
	return 0;
}

