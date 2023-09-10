#!/usr/bin/make -f

all: encrypt decrypt test

encrypt: ssl_bio_base64_encrypt.c
	$(CC) -Wall -lcrypto -lssl ssl_bio_base64_encrypt.c -o encrypt

decrypt: ssl_bio_base64_decrypt.c
	$(CC) -Wall -lcrypto -lssl ssl_bio_base64_decrypt.c -o decrypt

test:
	./encrypt a
	./decrypt YQo=

clean:
	-rm -rf encrypt decrypt
	-rm -rf file.enc

.PHONY: all test clean
