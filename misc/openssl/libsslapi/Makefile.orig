#!/usr/bin/make -f

CFLAGS:=$(CFLAGS) -Wall -Wextra -Wl,--as-needed

all: compile library test ssl_compability

compile: ssl_bio_base64.c ssl_bio_aes.c ssl_evp_aes.c
	$(CC) $(CFLAGS) $(LDFLAGS) -fPIC -c ssl_bio_base64.c -o ssl_bio_base64.o
	$(CC) $(CFLAGS) $(LDFLAGS) -fPIC -c ssl_bio_aes.c    -o ssl_bio_aes.o
	$(CC) $(CFLAGS) $(LDFLAGS) -fPIC -c ssl_evp_aes.c    -o ssl_evp_aes.o
	$(CC) $(CFLAGS) $(LDFLAGS) -fPIC -c ssl_rsa_pem.c    -o ssl_rsa_pem.o

library: compile
	$(CC) $(CFLAGS) $(LDFLAGS) ssl_bio_base64.o ssl_bio_aes.o ssl_evp_aes.o ssl_rsa_pem.o -shared -o libsslapi.so -lcrypto

test: compile library
	$(CC) $(CFLAGS) $(LDFLAGS) sslapi.c -o sslapi -L. -lsslapi
	LD_LIBRARY_PATH=.:${LD_LIBRARY_PATH} ./sslapi

ssl_compability:
	openssl enc -d -aes-256-cbc -nosalt -in file.enc -out file.txt && cat file.txt

clean:
	-rm -rf *.o
	-rm -rf *.so
	-rm -rf sslapi
	-rm -rf file.txt file.enc file.enc.txt
	-rm -rf file_ssl.txt file.bin

.PHONY: all test clean
